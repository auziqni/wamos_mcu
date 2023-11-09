#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

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
    pinMode(tds_pin, INPUT);
    pinMode(temp_pin, INPUT);
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
    air_tds = calculateTDS(raw_air_tds);
    // air_temp = raw_val_temp / 4095 * 100;
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

void loop()
{
    ReadSensor();
    SerialWrite();
    delay(1000);
}