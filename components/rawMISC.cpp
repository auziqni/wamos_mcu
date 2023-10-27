#include <Arduino.h>

int co = 32;
int nh3 = 33;
int no2 = 25;

float val_co, val_nh3, val_no2;
void setup()
{
  Serial.begin(115200);
  pinMode(co, INPUT);
  pinMode(nh3, INPUT);
  pinMode(no2, INPUT);
}

void loop()
{
  float raw_val_co = analogRead(co);
  float raw_val_nh3 = analogRead(nh3);
  float raw_val_no2 = analogRead(no2);

  val_co = raw_val_co / 4095 * 100;
  val_nh3 = raw_val_nh3 / 4095 * 100;
  val_no2 = raw_val_no2 / 4095 * 10;
  uint16_t a = (200 / 400) * 10;

  Serial.print("co= ");
  Serial.print(raw_val_co);
  Serial.print(", nh3= ");
  Serial.print(raw_val_nh3);
  Serial.print(", no2= ");
  Serial.println(raw_val_no2);

  Serial.print("co= ");
  Serial.print(String(val_co));
  Serial.print(", nh3= ");
  Serial.print(String(val_nh3));
  Serial.print(", no2= ");
  Serial.println(String(val_no2));

  Serial.print("co= ");
  Serial.print(val_co);
  Serial.print(", nh3= ");
  Serial.print(val_nh3);
  Serial.print(", a= ");
  Serial.print(a);
  Serial.print(", no2= ");
  Serial.println(val_no2);

  Serial.println("");

  delay(1000);
}