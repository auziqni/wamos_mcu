#include <Arduino.h>

int relay1 = 13;
int relay2 = 12;
int relay3 = 14;
int relay4 = 27;

float val_temp;
void setup()
{
    Serial.begin(115200);
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);
}

void loop()
{
    digitalWrite(relay1, HIGH);
    Serial.println("idup");
    delay(1500);
    digitalWrite(relay1, LOW);
    delay(1500);

    digitalWrite(relay2, HIGH);
    delay(500);
    digitalWrite(relay2, LOW);
    delay(500);

    digitalWrite(relay3, HIGH);
    delay(500);
    digitalWrite(relay3, LOW);
    delay(500);

    digitalWrite(relay4, HIGH);
    delay(500);
    digitalWrite(relay4, LOW);
    delay(500);
}