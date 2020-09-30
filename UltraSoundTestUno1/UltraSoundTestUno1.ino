
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 8
#define DIO 7

int cont = 0;
TM1637Display display(CLK, DIO);

uint8_t data[] = { 0b00001000, 0b00001000, 0b00001000, 0b00001000 };

// defines pins numbers
const int trigPin = 4;
const int echoPin = 2;

// defines variables
long duration;
double distance;

double speedOfSound;

int ThermistorPin = 0;
double Vo;
double R = 9750.0;
double logRt, Rt, T;

double A = 0.00112249961138183, B = 0.000235825993816084, C = 7.60671890460281E-08;

int teller = 10;

//int pluss = 0;
//int minus = 0;
//double rate = 0.0;

void setup() {
  Serial.begin(9600); // Starts the serial communication

  display.setBrightness(0xF);
  display.setSegments(data);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
void loop() {
  if(teller >= 10)
  {
    Vo = analogRead(A0);
    Rt = R * (1023.0 / Vo - 1.0);
    logRt = log(Rt);
    T = 1.0 / (A + B*logRt + C*logRt*logRt*logRt);
    T = T - 273.15;

    speedOfSound = findSpeedOfSound(T);

    teller = 0;
  }
  else
  {
    teller++;
  }
  
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * speedOfSound / 2.0;

  display.showNumberDec(distance,false);

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C"); 
  Serial.println();
  
  Serial.print("Avstand: ");
  Serial.println(distance);

//  if(distance > 2000)
//  {
//    pluss++;
//  }
//  else
//  {
//    minus++;
//  }
//
//  rate = (double)pluss / ((double)minus + (double)pluss) * 100.0;
//
//  Serial.print("Riktig: ");
//  Serial.println(pluss);
//  Serial.print("Galt: ");
//  Serial.println(minus);
//  Serial.print("Rate: ");
//  Serial.println(rate);

  delay(50);
}

double findSpeedOfSound(double temperatureC)
{
  double c0 = 331.4;
  double alfa = 1.0 / 273.15;

  double c = c0 * sqrt(1 + alfa * temperatureC);

  double mm_per_microsek = c * 1.0E-3;
  
  return mm_per_microsek;
}

