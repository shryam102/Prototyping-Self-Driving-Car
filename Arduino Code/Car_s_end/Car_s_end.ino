#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
long duration;
double ki = 0;
double kd = 0;
int kp = 5;
double elapsedTime;
double lastError = 0;
double input, setPoint;
int output;
int Error;
double cumError, rateError;
Servo steer;

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
#define D0 5
#define D1 6

unsigned long lastreceiveTime = 0;
unsigned long previousTime = 0;

int forward = 0;
int backward = 0;
int left  = 0;
int right = 0;

int angle = 90;

const int right_lim = 170;
const int left_lim = 10;


RF24 radio(9, 10); // CE, CSN
const byte   addresses [][6] = {"00001", "00002"};


struct Type1
{
  int F;
  int B;
  int R;
  int L;
  int A;
};
Type1 Data1;


struct Type2
{
  double yaw_angle;
};
Type2 Data2;

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  steer.attach(3);
  Wire.begin();
  byte status = mpu.begin();
  while (status != 0) { }
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  delay(1000);
  mpu.calcOffsets();
  steer.write(90);
}

void loop()
{
  delay(5);
  mpu.update();
  Data2.yaw_angle = mpu.getAngleZ();
  radio.stopListening();
  radio.write(&Data2, sizeof(Type2));
  delay(5);
  radio.startListening();
  unsigned long currentTime = millis();
  unsigned long Time = millis();
  if (currentTime - lastreceiveTime > 1000)
  {
    resetData();
    //    Serial.println("Not receiving Data!");
  }
  if (radio.available())
  {
    radio.read(&Data1, sizeof(Type1));
    lastreceiveTime = millis();
  }

  float x = computeError(Data2.yaw_angle);
  if(x>=90)
    x = 90;
  else if(x<=-90)
    x =-90;
  angle  = (x)*(Data1.A) + right_lim * (Data1.R) + left_lim * (Data1.L) + 90 * (!Data1.R && !Data1.L);
  steer.write(angle);

  Serial.print("out : ");
  Serial.print(x);
  //Serial.print(Data2.yaw_angle);
  Serial.print(Data1.F);
  Serial.print("    B: ");
  Serial.print(Data1.B);
  Serial.print("        L: ");
  Serial.print(Data1.L);
  Serial.print("            R: ");
  Serial.print(Data1.R);
  Serial.print("                        A: ");
  Serial.print(Data1.A);
  Serial.print("            Angle: ");
}
int computeError(double inp) {                              // PD Controller
  int Setpoint = 0 ;
  int currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
  Error = inp - Setpoint;
  cumError += Error * elapsedTime;
  if (cumError > 100)
    cumError = int(cumError) % 100;
  rateError = (Error - lastError) / elapsedTime;
  previousTime = currentTime;
  lastError = Error;
  int out = kp * Error + ki * cumError + kd * rateError;

  if (abs(out) < 5) {
    return 0;
  }

  return out;

}
void resetData() {
  Data1.F = 0;
  Data1.B = 0;
  Data1.R = 0;
  Data1.L = 0;
  Data1.A = 0;
