#include "NTPLedClock.h"
#include <WiFi.h>

// This class provides the full functionality of a clock, that syncs with a NTP server but can also be set manually

TaskHandle_t NTPLedClock::_updateTaskHandle = nullptr;
TaskHandle_t NTPLedClock::_syncTaskHandle = nullptr;
NTPLedClock* NTPLedClock::_instance = nullptr;

NTPLedClock::NTPLedClock(NTPClient* pTimeClient, Timezone* pTimeZone, size_t numLeds) : _pTimeClient(pTimeClient), _pTimeZone(pTimeZone), _numLeds(numLeds), _rtc(0) {
    _instance = this;
    xTaskCreate(updateTaskWrapper, "UpdateTask", 4096, nullptr, 0, &_updateTaskHandle);
    xTaskCreate(syncTaskWrapper, "SyncTask", 4096, nullptr, 0, &_syncTaskHandle);
}

NTPLedClock::~NTPLedClock() {
    if (_updateTaskHandle != nullptr) {
        vTaskDelete(_updateTaskHandle);
    }
    if (_syncTaskHandle != nullptr) {
        vTaskDelete(_syncTaskHandle);
    }
}

void NTPLedClock::begin(const char* ntp_server, const char* timezoneString) {
    _rtc.setTime(1704067200);
    _pTimeClient->begin();
}

void NTPLedClock::addHour() {
    _rtc.setTime(_rtc.getEpoch() + 3600);
}

void NTPLedClock::subHour() {
    _rtc.setTime(_rtc.getEpoch() - 3600);
}

void NTPLedClock::addMinute() {
    _rtc.setTime(_rtc.getEpoch() + 60);
}

void NTPLedClock::subMinute() {
    _rtc.setTime(_rtc.getEpoch() - 60);
}

void NTPLedClock::syncTaskWrapper(void* pvParameters) {
    _instance->syncTask();
}

void NTPLedClock::syncTask() {

    while (true) {

        if(WiFi.status() == WL_CONNECTED) {
            _pTimeClient->update();
        }

        if (_pTimeClient->isTimeSet()) {
            unsigned long recentEpochTime = _pTimeZone->toLocal(_pTimeClient->getEpochTime());

            if (recentEpochTime != _rtc.getEpoch()) {
                _rtc.setTime(recentEpochTime);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void NTPLedClock::updateTaskWrapper(void* pvParameters) {
    _instance->updateTask();
}

void NTPLedClock::updateTask() {

    while (true) {

        unsigned long tmsNow = millis();

        uint8_t hours = _rtc.getHour();
        uint8_t minutes = _rtc.getMinute();
        uint8_t seconds = _rtc.getSecond();
        uint16_t milliSecs = _rtc.getMillis();

        if (seconds != _lastSeconds) {
            _lastSeconds = seconds;
            printTime(hours, minutes, seconds);
        }

        updateLedPositions(hours, minutes, seconds, milliSecs);

        vTaskDelay(INTERVAL_MS_LED_CLOCK_LOOP / portTICK_PERIOD_MS);
    }
}

void NTPLedClock::updateLedPositions(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliSecs) {

    _iHrLed = map(hours % 12 * 60 + minutes, 0, 12 * 60, 0, _numLeds);
    _iMinLed = map(minutes, 0, 60, 0, _numLeds);
    _iSecLed = map(seconds, 0, 60, 0, _numLeds); // although it maps from 0 to 60 it will never reach 60 as seconds won't reach it as well
    _iMilliSecLed = map(milliSecs, 0, 1000, 0, _numLeds);
}

void NTPLedClock::printTime(uint8_t hours, uint8_t minutes, uint8_t seconds) const {
    Serial.printf("%02d:%02d:%02d\n", hours, minutes, seconds);
}

CyclicInteger NTPLedClock::getHrLed() const {
    return CyclicInteger(0, _numLeds - 1, _iHrLed);
}

CyclicInteger NTPLedClock::getMinLed() const {
    return CyclicInteger(0, _numLeds - 1, _iMinLed);
}

CyclicInteger NTPLedClock::getSecLed() const {
    return CyclicInteger(0, _numLeds - 1, _iSecLed);
}

CyclicInteger NTPLedClock::getMilliSecLed() const {
    return CyclicInteger(0, _numLeds - 1, _iMilliSecLed);
}
