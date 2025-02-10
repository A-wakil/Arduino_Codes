// ... existing code ...

#include <IRremote.hpp>
#include <Servo.h>  // Add Servo library

const int IR_RECEIVE_PIN = 7;  // Can use D7 or just 7 on Nano
const int servoPin = 10; 
const int touchPin = 2;     // Touch sensor pin
int currentPosition = 0;
int val;                    // Variable to store touch sensor reading

Servo myServo;  // Create servo object

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  myServo.attach(servoPin);  // Initialize servo
  myServo.write(currentPosition);  // Set initial position to 0 degrees
  pinMode(touchPin, INPUT);  // Set touch sensor pin as input
}

void loop() {
  val = digitalRead(touchPin);  // Read touch sensor
  
  // Check touch sensor
  if (val == 1) {
    currentPosition = (currentPosition == 0) ? 180 : 0;  // Toggle position
    myServo.write(currentPosition);
    delay(500);  // Add small delay to prevent multiple triggers
  }
  
  // Check IR remote
  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
      case 0xBF40FF00: //Keypad button "5"
        Serial.println("5");
        currentPosition = (currentPosition == 0) ? 180 : 0;  // Toggle position
        myServo.write(currentPosition);
        break;
      default:
        break;
    }

    IrReceiver.resume();
  }
}