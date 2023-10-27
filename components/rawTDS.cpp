#include <Arduino.h>

int tds_pin = 15;

float val_tds;
void setup()
{
    Serial.begin(115200);
    pinMode(tds_pin, INPUT);
}

void loop()
{
    float raw_val_tds = analogRead(tds_pin);

    val_tds = raw_val_tds / 4095 * 100;

    Serial.print("tds raw= ");
    Serial.print(raw_val_tds);
    Serial.print(", tds= ");
    Serial.println(val_tds);

    Serial.println("");

    delay(1000);
}