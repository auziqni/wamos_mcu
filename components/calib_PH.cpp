#include <Arduino.h>

const int analogPin = 2; // Pin analog ke sensor pH
float pHValue = 0.0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int rawADC = analogRead(analogPin);      // Baca tegangan analog dari sensor pH
  float voltage = (rawADC / 4095.0) * 3.3; // Konversi nilai ADC ke tegangan (0-3.3V)

  pHValue = (voltage / 5) * 14;

  Serial.print("raw: ");
  Serial.print(rawADC);
  Serial.print("volt: ");
  Serial.print(voltage);
  Serial.print("  pH Value: ");
  Serial.println(pHValue, 2); // Mencetak nilai pH dengan dua desimal

  delay(1000); // Menunggu 1 detik sebelum membaca ulang
}
