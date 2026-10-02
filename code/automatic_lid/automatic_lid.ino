#include <Servo.h>

Servo lidServo;

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Servo motor pin
const int servoPin = 6;

// Lid positions
const int closedAngle = 0;
const int openAngle = 90;

// Detection distance in cm
const int detectionDistance = 20;

void setup() {
  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo setup
  lidServo.attach(servoPin);
  lidServo.write(closedAngle);

  // Serial monitor
  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Receive echo
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an object is detected within 20 cm
  if (distance > 0 && distance <= detectionDistance) {

    // Open lid
    lidServo.write(openAngle);

    // Keep lid open for 3 seconds
    delay(3000);

    // Close lid
    lidServo.write(closedAngle);

    delay(1000);
  }

  delay(100);
}