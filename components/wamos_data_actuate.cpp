#include <Arduino.h>

// pin udara
int co_pin = 32;
int nh3_pin = 33;
int no2_pin = 25;
// pin air
int ph_pin = 2;
int tds_pin = 15;
int temp_pin = 4;

// global val
float udara_co, udara_nh3, udara_no2;
float air_ph, air_tds, air_temp;

// global condition
int kondisi_air = 1;   // 1:good, 2:warning, 3;bad
int kondisi_udara = 1; // 1:good, 2:warning, 3;bad

void setup()
{
    Serial.begin(115200);

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
    float raw_val_temp = analogRead(temp_pin);

    udara_co = ((4095 - raw_udara_co) / 4095) * 1000;
    udara_no2 = raw_udara_no2 / 4095 * 1;
    udara_nh3 = (raw_udara_nh3 / 4095) * 10;

    float voltage = (raw_air_ph / 4095.0) * 3.3;
    air_ph = (voltage / 5) * 14;
    air_tds = calculateTDS(raw_air_tds);
    // air_temp = raw_val_temp / 4095 * 100;
    air_temp = 32;
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

int cekph()
{
    float batasWarning_bawah_air_ph = 5.5, batasWarning_atas_air_ph = 8.5;
    float batasBad_bawah_air_ph = 5, batasBad_atas_air_ph = 9;

    if (air_ph < batasBad_bawah_air_ph || air_ph > batasBad_atas_air_ph)
    {
        return 3;
    }
    else if (air_ph < batasWarning_bawah_air_ph || air_ph > batasWarning_bawah_air_ph)
    {
        return 2;
    }
    else

        return 1;
}

int cektds()
{
    float batasWarning_bawah_air_tds = 20, batasWarning_atas_air_tds = 6000;
    float batasBad_bawah_air_tds = 5, batasBad_atas_air_tds = 9000;

    if (air_tds < batasBad_bawah_air_tds || air_tds > batasBad_atas_air_tds)
    {
        return 3;
    }
    else if (air_tds < batasWarning_bawah_air_tds || air_tds > batasWarning_bawah_air_tds)
    {
        return 2;
    }
    else

        return 1;
}

int cektemp()
{
    float batasWarning_bawah_air_temp = 15, batasWarning_atas_air_temp = 42;
    float batasBad_bawah_air_temp = 10, batasBad_atas_air_temp = 50;

    if (air_temp < batasBad_bawah_air_temp || air_temp > batasBad_atas_air_temp)
    {
        return 3;
    }
    else if (air_temp < batasWarning_bawah_air_temp || air_temp > batasWarning_bawah_air_temp)
    {
        return 2;
    }
    else

        return 1;
}

void Process()
{
    // batas
    float batas_udara_co = 250;
    float batas_udara_nh3 = 9;
    float batas_udara_no2 = 1;

    if (udara_co > batas_udara_co || udara_no2 > batas_udara_no2 || udara_nh3 > batas_udara_nh3)
    {
        kondisi_udara = 3;
        Serial.println(" udara berbahaya");
    }
    else
    {
        kondisi_udara = 1;
        Serial.println(" udara bagus");
    }

    // water: good
    if (cekph() == 1 && cektds() == 1 && cektemp() == 1)
    {
        kondisi_air = 1;
        Serial.println(" air bagus");
    }
    else if (cekph() == 3 || cektds() == 3 || cektemp() == 3)
    {
        kondisi_air = 3;
        Serial.println(" air berbahaya");
    }
    else
    {
        kondisi_air = 2;
        Serial.println(" air warning");
    }
}

void Actuate()
{
    // relay actuate
    switch (kondisi_air)
    {
    case 1:
        /* code */
        break;

    default:
        break;
    }
}
void loop()
{
    ReadSensor();
    SerialWrite();
    Process();
    delay(1000);
}