# Weight_machine_grocery
Code Description: Keypad Input and Weight Measurement System
This code integrates a keypad for input, a load cell sensor for weight measurement using the HX711 amplifier, and an output for calculating the total cost based on the price per kilogram entered by the user. The system prompts the user to enter the price per kilogram, measures the weight of an object placed on the scale, and then calculates and displays the total cost.

Key Components:
Keypad Input: The keypad allows the user to enter numerical values and control commands.
Load Cell with HX711: This setup measures the weight of objects placed on the scale.
Buzzer: Provides audible feedback when keys are pressed.
Pin Configuration:
Keypad: Configured with 4 rows and 4 columns.
Load Cell: Connected to digital pins 16 and 4 for data output (DOUT) and serial clock (SCK) respectively.
Buzzer: Connected to pin 32 for sound feedback.
Load Cell Power: Pin 2 is used to power the load cell.
Program Flow:
Setup:

Initializes the serial communication at 115200 baud rate.
Configures the pin modes for the load cell and buzzer.
Initializes the load cell using the HX711 library, sets the scale to zero, and prints a zero factor for calibration purposes.
Prompts the user to enter the price per kilogram.
Loop:

Continuously checks for key presses on the keypad.
When a key is pressed:
If it's a digit (0-9), it appends the digit to the input buffer and displays it.
If # is pressed, it erases the last entered digit.
If * is pressed, it finalizes the input:
Converts the input buffer to an integer representing the price per kilogram.
Measures the weight using the load cell.
Calculates the total cost based on the weight and the entered price per kilogram.
Displays the weight and total cost.
Resets the input buffer and prompts the user to enter a new price.
Functions:
buzz(int buzzCount = 1): Provides audible feedback by toggling the buzzer.
weight(): Measures and returns the weight using the load cell and HX711.



#Keypad Connections
The keypad has 4 rows and 4 columns. You need to connect each row and column to a digital pin on your microcontroller. Based on your code:

Keypad Rows:

Row 1 (R1) to Pin 18
Row 2 (R2) to Pin 19
Row 3 (R3) to Pin 21
Row 4 (R4) to Pin 22
Keypad Columns:

Column 1 (C1) to Pin 23
Column 2 (C2) to Pin 25
Column 3 (C3) to Pin 26
Column 4 (C4) to Pin 27
HX711 Load Cell Amplifier Connections
The HX711 module is used to interface with the load cell. Based on your code:

Load Cell Data Output Pin (DOUT): Connect to Pin 16
Load Cell Clock Pin (SCK): Connect to Pin 4
VCC Pin: Connect to Pin 2 (you've set this pin as output and written it HIGH in your code)
Buzzer Connection
The buzzer is connected to a digital pin on your microcontroller. Based on your code:

Buzzer Pin: Connect to Pin 32
