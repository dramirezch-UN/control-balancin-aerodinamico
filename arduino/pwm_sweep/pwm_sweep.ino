/*
Sweep PWM de 0 a 100 (cuidado, hay cierto valor de PWM cerca a 70 en donde
empezará a dar vueltas.). Los valores se imprimen en formato listo para CSV.
Esto se hace para calcular el valor K del motor.
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
  while (PWM<100) {
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
  PWM=30;
  // cuando acabe el sweep se vuelve a un PWM de 30
  digitalWrite(In2, LOW);
  analogWrite(In1, PWM*255/100);
}
