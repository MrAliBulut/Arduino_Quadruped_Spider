#include <Servo.h>

Servo legServos[8];  // Array to hold servo objects

void setup() {
  Serial.begin(9600);

  // Attach each servo to a pin (assuming servos are connected to pins 2 to 9)
  for (int i = 2; i < 10; ++i) {
    legServos[i - 2].attach(i);
  }
}

void loop() {
  if (Serial.available() > 0) {
    // Read the selected servo number from serial input
    int selectedServo = Serial.parseInt();

    if (selectedServo >= 2 && selectedServo <= 9) {
      Serial.print("Enter position for Servo ");
      Serial.print(selectedServo);
      Serial.print(" (0-180): ");

      // Clear any remaining characters in the serial input buffer
      while (Serial.available() > 0) {
        Serial.read();
      }

      // Wait for user input for the servo position
      while (Serial.available() == 0) {
        // Wait for input
      }

      // Read the servo position from serial input
      int servoPosition = Serial.parseInt();

      if (servoPosition >= 0 && servoPosition <= 180) {
        // Set the servo position
        legServos[selectedServo - 2].write(servoPosition);
        Serial.print("Servo ");
        Serial.print(selectedServo);
        Serial.print(" position set to: ");
        Serial.println(servoPosition);
      } else {
        Serial.println("Invalid servo position. Should be between 0 and 180.");
      }
    } else {
      Serial.println("Invalid servo number. Should be between 2 and 9.");
    }

    // Clear the input buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
