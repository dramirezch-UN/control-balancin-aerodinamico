/*
Sweep PWM from 0 to the value where the arm goes over 90 and print the angle for
each value of PWM. Values are printed in a CSV-ready PWM,angle format.
This is used for calculating the value K of the motor.
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
  // get data
  PWM=0;
  while (PWM<60) {
    analogWrite(In1, PWM*255/100);
    Serial.print(PWM);
    Serial.print(",");
    sensor = analogRead(sensorPin);
    sensor = map(sensor, 0, 1023, 0, 360);
    Serial.println(sensor-130);
    delay(1000);
    PWM+=1;
  }  
}

void loop() {
  // after getting the data, it goes back to the default PWM value of 30
  digitalWrite(In2, LOW);
  analogWrite(In1, 30*255/100);
}
