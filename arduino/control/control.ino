/*
Codigo del control
*/

// pins
// Puente H
int outputPwmPin = 6;
int In2 = 4;
// Encoder
float sensorPin = A0;

// Execution Time Control
long previousMillis = 0;  // For main loop function
long Ts = 10; // Sample time in ms

// control system variables

// ----- Reference -----
double Ref = 80;
// ---------------------

double directCmd = 30.0;
double E[5] = {0, 0, 0, 0, 0};
double U[5]= {0, 0, 0, 0, 0};

double Uunits = 100;

double sensorValue = 0;
double ang = 0;
double CmdPI=0;
unsigned int pwmDuty = 0;
double pwmMax = 255;

void control(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Ts) {
    previousMillis = currentMillis;
    sensorValue = analogRead(sensorPin);
    ang=(float(sensorValue)*360/1023)-130;
    double Cmd = directCmd+CmdPI;
    double CmdLim = min(max(Cmd,0),100);
    pwmDuty = int((CmdLim/Uunits)*pwmMax);
    analogWrite(outputPwmPin, pwmDuty);

    E[4] = E[3];
    E[3] = E[2];
    E[2] = E[1];
    E[1] = E[0];
    E[0] = Ref - ang;

    U[4] = U[3];
    U[3] = U[2];
    U[2] = U[1];
    U[1] = U[0];
    U[0] = 1.291*E[0] - 3.595*E[1] + 3.133*E[2] - 0.633*E[3] - 0.1954*E[4] - (- 2.477*U[1] + 1.95*U[2] - 0.3935*U[3] - 0.07914*U[4]);
    //U[0] = 10.79*E[0] - 30.22*E[1] + 26.49*E[2] - 5.401*E[3] - 1.659*E[4] - (- 2.477*U[1] + 1.95*U[2] - 0.3935*U[3] - 0.07914*U[4]);


    CmdPI = U[0];

    Serial.print("E:");
    Serial.print(E[0]);
    Serial.print(", ");
    Serial.print("U:");
    Serial.print(CmdPI);
    Serial.print(", ");
    Serial.print("PWM:");
    Serial.print(CmdLim);
    Serial.print(", ");
    Serial.print("Ref:");
    Serial.print(Ref);
    Serial.print(", ");
    Serial.print("ang:");
    Serial.println(ang);
  }
}

void setup() {
  Serial.begin(2000000);
  // Puente H
  pinMode(outputPwmPin, OUTPUT);
  pinMode(In2, OUTPUT);
  analogWrite(outputPwmPin, pwmDuty);
}

void loop() {
  digitalWrite(In2, LOW);
  control();
}
