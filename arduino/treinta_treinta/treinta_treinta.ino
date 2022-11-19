/*
Use 30% PWM for the motor.
This is used for verifying 30% PMW = 30 degrees
*/

// Puente H
int In1 = 6;
int In2 = 4;
// Encoder
float sensorPin = A0;
float sensor = 0;
// Default PWM
float PWM = 30;

void setup() {
  Serial.begin(9600);
  // Puente H
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
}

void loop() {
  // write PWM for bridge H
  digitalWrite(In2, LOW);
  analogWrite(In1, (PWM*255/100)+5);
  // read angle from encoder
  sensor = analogRead(sensorPin);
  sensor = map(sensor, 0, 1023, 0, 360);
  // print PWM and angle
  Serial.print(PWM);
  Serial.print(",");
  Serial.print(sensor);
}
