#include <IRremote.h>

const int RECV_PIN = 12;  // Define the IR receiver pin

IRrecv irrecv(RECV_PIN);  // Create an IR receiver object
decode_results results;   // Create an object to hold the decoding results

void setup(){
  Serial.begin(9600);     // Initialize serial communication
  irrecv.enableIRIn();    // Enable the IR receiver
  irrecv.blink13(true);   // Enable blinking on pin 13 when IR signal is received
}

void loop(){
  unsigned long value;

  if (irrecv.decode(&results)){  // Check if an IR signal is received
    value = results.value;       // Get the value of the received IR signal
    Serial.println("Pressed Button Code");
    Serial.println(value);        // Print the received IR code
    Serial.println("**************************************");

    irrecv.resume();             // Receive the next IR signal
    delay(200);                  // Delay to avoid processing the same signal multiple times
  }
}
