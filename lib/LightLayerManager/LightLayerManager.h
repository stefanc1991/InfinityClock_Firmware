#pragma once

#include <Arduino.h>
#include <vector>

#include "LightLayer.h"

#define INTERVAL_MS_LIGHT_MANAGER_LOOP 2

class LightLayerManager {
public:
    LightLayerManager(size_t numLeds);

    LightLayer* addLayer();
    void fadeAllToBlack();
    void getTotalLedColors(CRGB* pTargetLedArray);
    void setBrightness(byte brightness);
    bool isColorTransitionComplete() const;
    static void loopTaskWrapper(void* parameter);
    void loopTask();

private:
    static TaskHandle_t _loopTaskHandle;
    static LightLayerManager* _instance;

    std::vector<LightLayer*> _pLayers;
    size_t _numLeds;
    byte _brightness = 255;
};
