#include <Arduino.h>

const int tdsPin = 15;

// 720 247
// 2883 8093

float lowvalue_calibration = 247;
float highvalue_calibration = 8093;
float low_read = 720;
float high_read = 2883;

float slope, intercept;

float calculateTDS(float tdsReading)
{
    // Menggunakan persamaan linear untuk menghitung TDS
    slope = (highvalue_calibration - lowvalue_calibration) / (high_read - low_read);
    intercept = highvalue_calibration - (slope * high_read);
    float tdsValue = (slope * tdsReading) + intercept;
    if (tdsValue < 0)
    {
        return 0;
    }
    else
    {
        return tdsValue;
    }
}

void setup()
{
    // Inisialisasi Serial Monitor
    Serial.begin(115200);

    // Tampilkan pesan untuk memulai kalibrasi
    Serial.println("Mulai kalibrasi TDS...");
    // Serial.println("Celupkan sensor TDS ke dalam larutan referensi TDS terendah.");
    // while (Serial.available() == 0)
    // {
    //     // Menunggu hingga ada data yang masuk
    //     float tdsReading = analogRead(tdsPin);
    //     Serial.println(tdsReading);
    // }

    // String inputString = Serial.readStringUntil('\n');
    // lowvalue_calibration = inputString.toInt();
    // low_read = analogRead(tdsPin);
    // // Serial.print("Anda memasukkan: ");
    // // Serial.println(lowvalue_calibration);

    // Serial.println("Celupkan sensor TDS ke dalam larutan referensi TDS tertinggi.");
    // while (Serial.available() == 0)
    // {
    //     // Menunggu hingga ada data yang masuk
    //     float tdsReading = analogRead(tdsPin);
    //     Serial.println(tdsReading);
    // }

    // String inputString2 = Serial.readStringUntil('\n');
    // highvalue_calibration = inputString2.toInt();
    // high_read = analogRead(tdsPin);
    // // Serial.print("Anda memasukkan: ");
    // // Serial.println(highvalue_calibration);

    Serial.print("nilai tds");
    Serial.println(calculateTDS(analogRead(tdsPin)));
    Serial.print("nilai slope");
    Serial.println(slope);
    Serial.print("nilai intercept");
    Serial.println(intercept);
    delay(5000);
}

void loop()
{
    float tdsReading = analogRead(tdsPin);
    Serial.print(tdsReading);
    Serial.print("  ");
    Serial.println(calculateTDS(tdsReading));
    delay(1000);
}
