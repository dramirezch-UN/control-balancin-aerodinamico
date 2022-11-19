/*
Lee el angulo que da el encoder. (PWM=0.)
*/

// Puente H
int In1 = 6;
int In2 = 4;
// Encoder
float sensorPin = A0;
float sensor = 0;
// Default PWM
float PWM = 0;

void setup() {
  Serial.begin(9600);
  // Puente H
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
}

void loop() {
  analogWrite(In1, 0);
  Serial.print(",");
  sensor = analogRead(sensorPin);
  sensor = map(sensor, 0, 1023, 0, 360);
  Serial.println(sensor-130);
}
