int IN1 = 9;
int IN2 = 6;
int sensorPin = A0;

// ----- Referencia -----
      double Ref= 105; 
// ----------------------

float Kp=0.5;
float Ki=0.7;
float Kd=0.02;
int N=100;

double directCmd=30;
int Uunits=100;
int pwmMax=255;
long Ts=2.5;
// valores de la red (calculados durante el setup)
double a=0;
double b=0;
double c=0;
double d=0;

long previousMillis = 0;
double CmdPID=0.0;
double Cmd=0.0;
double E=0;
double Ep=0;
double Up=0;
double CmdIp=0;
double CmdDp=0;
double CmdC=0;
double CmdPIDp=0;
unsigned int pwmDuty = 0;
int sensorValue = 0;
double ang=0;

void controlPI(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Ts ) {
    previousMillis = currentMillis;
    sensorValue = analogRead(sensorPin);
    ang=((float(sensorValue)*360/1023)-130);
    double Cmd = directCmd+CmdC;  
    double CmdLim = min(max(Cmd, 0), Uunits);
    pwmDuty = int((CmdLim/Uunits)*pwmMax);
    analogWrite(IN1,pwmDuty);

    if (currentMillis >= 5000) {     
      E= (Ref - ang); // error en grados
      
      double CmdP = Kp*E;
      double CmdI =(Ki*(Ts*1e-3)*Ep)+CmdIp;
      double CmdD = Kd*N*(E-Ep)+CmdDp*(1-(N*Ts*1e-3));
     
      CmdPID= CmdP+CmdI+CmdD;
      
//      Si se quiere usar solo PID (sin red) descomentar la siguiente linea y comentar la red de adelanto
//      CmdC=CmdPID;

//      Red de adelanto
      CmdC=(a*CmdPID+b*CmdPIDp-d*Up)/c;

      CmdIp=CmdI;
      CmdDp=CmdD;
      CmdPIDp=CmdPID;
      Ep = E;
      Up = CmdC; 
    }
    Serial.print("Time[ms]:");
    Serial.print(currentMillis);
    Serial.print(", ");
//    Serial.print("ref[deg]:");
//    Serial.print(Ref);
//    Serial.print(", ");
    Serial.print("ang[deg]");
    Serial.print(ang);
    Serial.print(", ");
//    Serial.print("Error:[rad]");
//    Serial.print(E);
//    Serial.print(", ");
//    Serial.print("Error2:[deg]");
//    Serial.print(E2);
//    Serial.print(", ");
//    Serial.print("CmdPI:[%]");
//    Serial.print(CmdPI);
//    Serial.print(", ");
    Serial.print("CmdC:[%]");
    Serial.print(CmdC);
    Serial.print(", ");
//    Serial.print("Cmd:[%]");
//    Serial.print(Cmd);
//    Serial.print(", ");
//    Serial.print("CmdLim:[%]");
//    Serial.print(CmdLim);
//    Serial.print(", ");
    Serial.print("pwmDuty:[8bit]");
    Serial.println(pwmDuty);
   }
}

void setup(){
  pinMode (IN2, OUTPUT);
  Serial.begin(115200);
 
  double Ts1=1000;
  double T2=0.0130;
  double b1=55.62;
  a=(Ts1*1e-3)+2*T2*b1;
  b=(Ts1*1e-3)-2*T2*b1;
  c=(Ts1*1e-3)+2*T2;
  d=(Ts1*1e-3)-2*T2;
}

void loop(){
  digitalWrite (IN2, LOW);
  controlPI();
}
