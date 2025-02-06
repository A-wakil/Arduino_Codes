#include <IRremote.h>

// Define the IR transmitter pin (connect your IR LED to this pin)
const int IR_SEND_PIN = 3;  // Usually pin 3 has PWM capability

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Start the IR sender
  IrSender.begin(IR_SEND_PIN);
  
  Serial.println("IR Transmitter is ready");
}

void loop() {
  // Send a test code (0x12 in this example) using NEC protocol
  IrSender.sendNEC(0xFF00, 0x12, 0);
  
  // Print the sent code
  Serial.println("Sent IR Code: 0x12");
  
  // Wait for 2 seconds before sending again
  delay(2000);
} 