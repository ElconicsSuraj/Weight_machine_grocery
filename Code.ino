#include "Keypad.h"
#include "HX711.h" 

#define LOADCELL_DOUT_PIN  16
#define LOADCELL_SCK_PIN   4
#define vcc                2

HX711 scale;
float calibration_factor =  2006; // Adjust this value according to your setup

const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {18, 19, 21, 22}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = {23, 25, 26, 27}; // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char inputBuffer[5] = ""; // Buffer to store input characters + '\0'
const int buzzerPin = 32;

void buzz(int buzzCount = 1)
{
    for (int i = 0; i < buzzCount; ++i)
    {
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(buzzerPin, OUTPUT);
    pinMode(vcc, OUTPUT);
    digitalWrite(vcc, HIGH);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale();
    scale.tare();  // Reset the scale to 0

    long zero_factor = scale.read_average(); // Get a baseline reading
    Serial.print("Zero factor: "); // This can be used to remove the need to tare the scale. Useful in permanent scale projects.
    Serial.println(zero_factor);

    Serial.println("ANTZ SYSTEM");
    Serial.println("Please Enter the price per kg:");
}

void loop()
{
    char key = keypad.getKey();
    static int price = 0;
    static bool enteringPrice = true;

    if (key != NO_KEY)
    {
        // Buzz each time a button is pressed
        buzz();

        if (key == '#')
        {
            if (enteringPrice)
            {
                // Erase the last entered digit
                if (strlen(inputBuffer) > 0)
                {
                    inputBuffer[strlen(inputBuffer) - 1] = '\0';
                    Serial.write(0x08); // Move cursor back
                    Serial.write(' ');  // Overwrite character with space
                    Serial.write(0x08); // Move cursor back again
                }
            }
        }
        else if (enteringPrice)
        {
            // Append the pressed key to the input buffer if it's a digit
            if (isdigit(key))
            {
                strncat(inputBuffer, &key, 1);
                Serial.print(key); // Print the key only if it's a digit
            }

            if (key == '*') // End of input with '*'
            {
                if (strlen(inputBuffer) > 0)
                {
                    price = atoi(inputBuffer);
                    Serial.println("\nPrice per kg: " + String(price));
                    enteringPrice = false;

                    // Now measure and display cost
                    float weightInGrams = weight(); // Get the actual weight
                    float cost = (weightInGrams / 1000.0) * price; // Weight in kg * price per kg
                    Serial.println("Weight: " + String(weightInGrams) + " g");
                    Serial.println("Total Cost: " + String(cost));
                    
                    // Reset for next input
                    inputBuffer[0] = '\0';
                    enteringPrice = true;
                    Serial.println("Please Enter the price per kg:");
                }
                else
                {
                    Serial.println("\nInvalid input. Please enter a valid price.");
                }
            }
        }
    }
}

float weight() {
    scale.set_scale(calibration_factor); // Adjust to this calibration factor
    float weight = scale.get_units(20); // Get the weight reading
    delay(10);
    return weight; // Return the weight reading
}
