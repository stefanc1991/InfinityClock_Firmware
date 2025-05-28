#pragma once

#include <Arduino.h>
#include "CyclicInteger.h"
#include <ESP32Time.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

#define TIME_SYNC_INTERVAL 60 * 60 * 1000
#define INTERVAL_MS_LED_CLOCK_LOOP 10

class NTPLedClock {
public:
    NTPLedClock(NTPClient* pTimeClient, Timezone* pTimeZone, size_t numLeds);
    ~NTPLedClock();
    
    void begin(const char* ntp_server, const char* timezoneString);
    void addHour();
    void subHour();
    void addMinute();
    void subMinute();
    
    CyclicInteger getHrLed() const;
    CyclicInteger getMinLed() const;
    CyclicInteger getSecLed() const;
    CyclicInteger getMilliSecLed() const;

private:

    NTPClient* _pTimeClient;
    Timezone* _pTimeZone;

    ESP32Time _rtc;

    size_t _numLeds;

    int8_t _iHrLed = 0;
    int8_t _iMinLed = 0;
    int8_t _iSecLed = 0;
    int16_t _iMilliSecLed = 0;

    uint8_t _lastSeconds = 0;

    static TaskHandle_t _updateTaskHandle;
    static TaskHandle_t _syncTaskHandle;
    static NTPLedClock* _instance;

    static void syncTaskWrapper(void* pvParameters);
    void syncTask();

    static void updateTaskWrapper(void* pvParameters);
    void updateTask();

    void updateLedPositions(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliSecs);
    void printTime(uint8_t hours, uint8_t minutes, uint8_t seconds) const;
};
