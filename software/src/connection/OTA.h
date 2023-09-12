#pragma once

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "./credentials.h" // ssid and password

namespace OTA
{
    long unsigned int lastUpdate = 0;
    int updateInterval = 1000; // 1 second

    IPAddress setupOTA()
    {
        ArduinoOTA.setHostname("OSKD");

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        WiFi.waitForConnectResult(2000);

        ArduinoOTA.begin();

        return WiFi.localIP();
    }

    void update()
    {
        // Prevent rollover
        if (millis() - lastUpdate < 0)
            lastUpdate = millis();

        if (millis() - lastUpdate < updateInterval)
            return;

        if (WiFi.status() != WL_CONNECTED)
            return;

        ArduinoOTA.handle();
        lastUpdate = millis();
    }
}
