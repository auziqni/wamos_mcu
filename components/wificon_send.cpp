#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
// #include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char *ssid = "wamos";
const char *password = "wamos123";

void Wificon()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
}

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        Wificon();
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        Wificon();
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    String jsonReqPayload = "";
    StaticJsonDocument<200> D2W;

    float air_ph = random(40, 90) / 10;
    float air_tds = random(0, 10000);
    float air_temp = random(150, 450) / 10;
    float udara_co = random(0, 1000);
    float udara_no2 = random(0, 150) / 10;
    float udara_nh3 = random(0, 200) / 100;

    D2W["no_alat"] = 1;
    D2W["air_ph"] = air_ph;
    D2W["air_tds"] = air_tds;
    D2W["air_suhu"] = air_temp;
    D2W["udara_co"] = udara_co;
    D2W["udara_no2"] = udara_no2;
    D2W["udara_ch3"] = udara_nh3;

    serializeJson(D2W, jsonReqPayload);
    Serial.println(jsonReqPayload);

    HTTPClient http;

    http.begin("https://wamos.auziqni.com/api/writedata");
    http.addHeader("Content-Type", "application/json; charset=UTF-8");
    int httpCode = http.POST(jsonReqPayload);

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
        }
        else
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    delay(1000);
}