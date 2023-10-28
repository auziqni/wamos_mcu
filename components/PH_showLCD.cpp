#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 merupakan adress dari iic lcd, cari nilai pake scanner

const int tdsPin = 15;

// 720 247
// 2883 8093

const int analogPin = 2; // Pin analog ke sensor pH
float pHValue = 0.0;

void setup()
{
    // Inisialisasi Serial Monitor
    Serial.begin(115200);
    lcd.init();      // initialize the lcd
    lcd.backlight(); // menghidupkan backlight
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    delay(3500);
    lcd.clear();

    // Tampilkan pesan untuk memulai kalibrasi
    Serial.println("Mulai kalibrasi TDS...");
    // Serial.println("Celupkan sensor TDS ke dalam larutan referensi TDS terendah.");
    // while (Serial.available() == 0)
    // {    //     // Menunggu hingga ada data yang masuk
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

    // Serial.print("nilai tds");
    // Serial.println(calculateTDS(analogRead(tdsPin)));
    // Serial.print("nilai slope");
    // Serial.println(slope);
    // Serial.print("nilai intercept");
    // Serial.println(intercept);
    // delay(5000);
}

void loop()
{
    int rawADC = analogRead(analogPin);      // Baca tegangan analog dari sensor pH
    float voltage = (rawADC / 4095.0) * 3.3; // Konversi nilai ADC ke tegangan (0-3.3V)

    pHValue = (voltage / 5) * 14;

    //   Serial.print("raw: ");
    //   Serial.print(rawADC);
    //   Serial.print("volt: ");
    //   Serial.print(voltage);
    Serial.print("  pH Value: ");
    Serial.println(pHValue, 2); // Mencetak nilai pH dengan dua desimal

    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PH");
    lcd.setCursor(9, 1);
    lcd.print(pHValue);
    delay(3000);
}
