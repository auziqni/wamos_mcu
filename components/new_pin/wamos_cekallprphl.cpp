#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

const char *ssid = "wamos";
const char *password = "wamos123";

LiquidCrystal_I2C lcd(0x27, 16, 2);

int co_pin = 36;
int nh3_pin = 39;
int no2_pin = 34;
// int no2_pin = 25;
// pin air
int ph_pin = 32;
int tds_pin = 35;
const int temp_pin = 33;
OneWire oneWire(temp_pin);
DallasTemperature sensors(&oneWire);

int pilot_good = 13;
int pilot_warning = 12;
int pilot_bad = 14;
int pompa = 27;

float udara_co, udara_nh3, udara_no2;
float air_ph, air_tds, air_temp;

void setup()
{
    Serial.begin(115200);
    sensors.begin();

    // int pin
    pinMode(co_pin, INPUT);
    pinMode(no2_pin, INPUT);
    pinMode(nh3_pin, INPUT);
    pinMode(ph_pin, INPUT);
    pinMode(tds_pin, INPUT_PULLDOWN);
    pinMode(temp_pin, INPUT_PULLUP);

    pinMode(pilot_good, OUTPUT);
    pinMode(pilot_warning, OUTPUT);
    pinMode(pilot_bad, OUTPUT);
    pinMode(pompa, OUTPUT);

    lcd.init();      // initialize the lcd
    lcd.backlight(); // menghidupkan backlight
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    lcd.setCursor(0, 1);
    lcd.print("Hello, wamos!");
    delay(3500);
    lcd.clear();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        lcd.setCursor(0, 0);
        lcd.print("conecting to:");
        lcd.setCursor(0, 1);
        lcd.print(ssid);
        delay(500);
        Serial.print(".");
    }

    lcd.setCursor(0, 0);
    lcd.print("berhasil");
    lcd.setCursor(0, 1);
    lcd.print("hubung wifi");
}

float calculateTDS(float tdsReading)
{
    float slope = 4.685;
    float intercept = -5684;
    // slope = (highvalue_calibration - lowvalue_calibration) / (high_read - low_read);
    // intercept = highvalue_calibration - (slope * high_read);
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

void ReadSensor()
{
    float raw_udara_co = analogRead(co_pin);
    float raw_udara_no2 = analogRead(no2_pin);
    float raw_udara_nh3 = analogRead(nh3_pin);
    float raw_air_ph = analogRead(ph_pin);
    float raw_air_tds = analogRead(tds_pin);
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    udara_co = ((4095 - raw_udara_co) / 4095) * 1000;
    udara_no2 = raw_udara_no2 / 4095 * 1;
    udara_nh3 = (raw_udara_nh3 / 4095) * 10;

    float voltage = (raw_air_ph / 4095.0) * 3.3;
    air_ph = (voltage / 5) * 14;
    // air_ph = raw_air_ph;
    // air_tds = calculateTDS(raw_air_tds);
    air_tds = raw_air_tds;
    air_temp = temperatureC;
}

void SerialWrite()
{
    Serial.print("CO= ");
    Serial.print(udara_co);
    Serial.print(", NO2= ");
    Serial.print(udara_no2);
    Serial.print(", NH3= ");
    Serial.println(udara_nh3);

    Serial.print("Ph= ");
    Serial.print(air_ph);
    Serial.print(", TDS=");
    Serial.print(air_tds);
    Serial.print(", Temp=");
    Serial.println(air_temp);

    Serial.println("");
}

void Cekrelay()
{
    digitalWrite(pilot_good, HIGH);
    delay(1500);
    digitalWrite(pilot_good, LOW);
    delay(1500);

    digitalWrite(pilot_warning, HIGH);
    delay(500);
    digitalWrite(pilot_warning, LOW);
    delay(500);

    digitalWrite(pilot_bad, HIGH);
    delay(500);
    digitalWrite(pilot_bad, LOW);
    delay(500);

    digitalWrite(pompa, HIGH);
    delay(500);
    digitalWrite(pompa, LOW);
    delay(500);
}

void loop()
{
    ReadSensor();
    SerialWrite();
    Cekrelay();
    delay(1000);
}