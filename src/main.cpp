#include <Arduino.h>

int ph_pin = 15;

float val_ph;
void setup()
{
    Serial.begin(115200);
    pinMode(ph_pin, INPUT);
}

void loop()
{
    float raw_val_ph = analogRead(ph_pin);

    val_ph = raw_val_ph / 4095 * 14;

    Serial.print("ph raw= ");
    Serial.print(raw_val_ph);
    Serial.print(", ph= ");
    Serial.println(val_ph);

    Serial.println("");

    delay(1000);
}