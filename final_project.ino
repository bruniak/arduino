#include <Servo.h>

// Pins
const int trigPin = 3;
const int echoPin = 2;
const int redLED = 5;
const int greenLED = 6;
const int servoPin = 7;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0); // start closed

  Serial.begin(9600);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20) {  // object detected within 20 cm
    myServo.write(90);                 // open
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  } else {
    myServo.write(0);                  // close
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  delay(200);
}