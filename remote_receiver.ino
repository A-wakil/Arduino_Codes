// ... existing code ...

#include <IRremote.hpp>
#include <Servo.h>  // Add Servo library

const int IR_RECEIVE_PIN = 7;
const int servoPin = 10;  // Reusing pin 10 for servo
int currentPosition = 0;  // Add variable to track servo position

Servo myServo;  // Create servo object

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  myServo.attach(servoPin);  // Initialize servo
  myServo.write(currentPosition);  // Set initial position to 0 degrees
}

void loop(){
  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
      case 0xBF40FF00: //Keypad button "5"
        Serial.println("5");
        currentPosition = (currentPosition == 0) ? 180 : 0;  // Toggle position
        myServo.write(currentPosition);  // Move to new position
        break;
      default:
        break;
    }

    IrReceiver.resume();
  }
}