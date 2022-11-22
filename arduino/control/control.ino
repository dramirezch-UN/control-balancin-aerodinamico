//Definición salidas para el motor

int IN1 = 9;    // In3 (L298N) conectada al pin 9, este es el del PWM
int IN2 = 6;    // In4 (L298N) conectada al pin 6
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
double ang=0;

long previousMillis2 = 0; // For auxiliary functions (squarewaves)
bool up = true;
int i = 0;

long previousMillis = 0;
double directCmd=0.3;
int Uunits=1;
int pwmMax=255;
unsigned int pwmDuty = 0;

//float Kp=0.015;
//float Ki=0.012;
//float Kd=0.002;

//Las epicas
/*float Kp = 0.0009;
float Ki = 0.3;
float Kd = 0.00323;*/

float Kp=0.4;
float Ki=0.65;
float Kd=0.018;
int N=100;
double Ref= 90;

//Red de adelanto
double a=2.377;
double b=-2.326;
double c=1;
double d=-0.9485;
//Red de adelanto-atraso
double a1 = 2.13;
double b1 = -4.209;
double c1 = 2.08;
double d1 = 1;
double e1 = -1.947;
double f1 = 0.9471;
//Red de atraso
double a2=0.2908;
double b2=-0.2901;
double c2=1;
double d2=-0.9993;

//double c1=1.00;
//double d1=-0.972268441486412;
double Uin=0;
double Uinp=0;
double CmdPI=0.0;
double Cmd=0.0;
long Ts=2.5;
double E2=0;
double E=0;
double Ep=0;
double Ep2=0;
double Up=0;
double Upp = 0;
double Up2=0;
double CmdIp=0;
double CmdDp=0;
double CmdC=0;    //señal Controlador con red incluida
double CmdCp=0;   //señal Controlador con red incluida
double CmdPIp=0;
double CmdPIpp=0;

void setup()
{
 //Configuración de los pines como salidas
 //pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 Serial.begin(115200);
}
void loop()
{
  //Salida para que el motor gire en un sentido
  //digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  controlPI();
  //RefChange();
}

void controlPI(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Ts ) {
    previousMillis = currentMillis;
    sensorValue = analogRead(sensorPin);
    ang=((float(sensorValue)*360/1023)-130);
    double Cmd = directCmd+CmdC;  
    double CmdLim = min(max(Cmd, 0), Uunits); // Saturated Control Output
    pwmDuty = int((CmdLim/Uunits)*pwmMax);
    analogWrite(IN1,pwmDuty);

    if (currentMillis >= 5000) {
     
      E = (Ref - ang)*PI/180;
      E2= (Ref - ang);
      //CmdPI = Kp*(E - Ep) + (Ki*Ts/2)*(E + Ep) + Up;
      //Uin=(a*E+b*Ep)*0.0001+Uinp;
      //CmdPI=(a*E+b*Ep+c*Ep2)*0.00001+a1*Up+a2*Up2;
      //CmdPI=(c*Uin+d*Uinp-d1*Up)/c1;
      double CmdP=Kp*E;
      double CmdI= (Ki*(Ts*1e-3)*Ep)+CmdIp;
      double CmdD= Kd*N*(E-Ep)+CmdDp*(1-(N*Ts*1e-3));
     
      CmdPI= CmdP+CmdI+CmdD;
      //Red de adelanto
      CmdC=(a*CmdPI+b*CmdPIp-d*Up)/c;
      //Red de adelanto atraso
      //CmdC=(a1*CmdPI+b1*CmdPIp+c1*CmdPIpp -e1*Up-f1*Upp)/d1;
      //Red de atraso
      //CmdC=(a2*CmdPI+b2*CmdPIp-d2*Up)/c2;
      //Uinp=Uin;
      //Ep2=Ep;
      //Up2=Up;
      CmdIp=CmdI;
      CmdDp=CmdD;
      CmdPIpp = CmdPIp;
      CmdPIp=CmdPI;
      Ep = E;
      Upp = Up;
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

void RefChange(){
 unsigned long currentMillis = millis();
 if (currentMillis >= 5000 && currentMillis-previousMillis2 >= 20000) {
    previousMillis2 = currentMillis; // refresh the last time you RUN
    if (up){
      Ref = 90;
      up = false;
    } else {
      Ref = 120;
      up = true;
    }
 }
}
