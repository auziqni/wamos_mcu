#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 merupakan adress dari iic lcd, cari nilai pake scanner

void setup()
{
    lcd.init();      // initialize the lcd
    lcd.backlight(); // menghidupkan backlight
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    delay(3500);
    lcd.clear();
}

void loop()
{
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("HAI KAMU!");
    lcd.setCursor(0, 1);
    lcd.print("aku ada rahasia");
    delay(2000);
    lcd.noBacklight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AKU SUKA KAMU");
    lcd.setCursor(3, 1);
    lcd.print("Muuaaah :* ");
    delay(2000);
}