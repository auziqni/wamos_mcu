#include <Arduino.h>

const int tdsPin = 35;

// 720 247
// 2883 8093

float lowvalue_calibration = 0;
float highvalue_calibration = 0;
float low_read = 0;
float high_read = 0;

float slope, intercept;

float calculateTDS(float tdsReading)
{
    // Menggunakan persamaan linear untuk menghitung TDS
    // slope = (highvalue_calibration - lowvalue_calibration) / (high_read - low_read);
    // intercept = highvalue_calibration - (slope * high_read);
    // x(kalibrator low) 73
    // y(kalibrator high) 322
    // a(pembacaa low) 93
    // a(pembacaa high) 970
    // slope = (y - x) / (b - a);
    // intercept = y - (s * b);
    slope = 0.2922;
    intercept = 45.8204;
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
}

void loop()
{
    float tdsReading = analogRead(tdsPin);
    Serial.print(tdsReading);
    Serial.print("  ");
    Serial.println(calculateTDS(tdsReading));
    delay(1000);
}
