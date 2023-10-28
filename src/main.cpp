#include <Arduino.h>

int temp_pin = 4;

float val_temp;
void setup()
{
    Serial.begin(115200);
    pinMode(temp_pin, INPUT);
}

void loop()
{
    float raw_val_temp = analogRead(temp_pin);

    val_temp = raw_val_temp / 4095 * 100;

    Serial.print("temp raw= ");
    Serial.print(raw_val_temp);
    Serial.print(", temp= ");
    Serial.println(val_temp);

    Serial.println("");

    delay(100);
}