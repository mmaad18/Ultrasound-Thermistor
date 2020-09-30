int ThermistorPin = 0;
double Vo;
double R = 9750.0;
double logRt, Rt, T;
double A = -0.00272842524397696, B = 0.000948959867025436, C = -3.36584915062789E-06;


void setup() {
Serial.begin(9600);
}

void loop() {

  Vo = analogRead(A0);
  Rt = R * (1023.0 / Vo - 1.0);
  logRt = log(Rt);
  T = 1.0 / (A + B*logRt + C*logRt*logRt*logRt);
  T = T - 273.15;

  Serial.print("Rt: "); 
  Serial.print(Rt);
  Serial.println(" Ohm"); 

  Serial.print("Vo reading: "); 
  Serial.print(Vo);
  Serial.println(" "); 

  Serial.print("Vo: "); 
  Serial.print(Vo * 5.0/1023.0);
  Serial.println(" V"); 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C"); 
  Serial.println();

  delay(500);
}

