#include "LightLayerManager.h"
#include <FastLED.h>

// Manages the individual light layers and provides functions to calculate the total colors of each LED

TaskHandle_t LightLayerManager::_loopTaskHandle = nullptr;
LightLayerManager* LightLayerManager::_instance = nullptr;

LightLayerManager::LightLayerManager(size_t numLeds) : _numLeds(numLeds) {
    _instance = this;
    xTaskCreate(loopTaskWrapper, "LoopTask", 4096, nullptr, 1, &_loopTaskHandle);
}

LightLayer* LightLayerManager::addLayer() {
    LightLayer* pNewLayer = new LightLayer(_numLeds);
    _pLayers.push_back(pNewLayer);
    return pNewLayer;
}

void LightLayerManager::fadeAllToBlack() {
    for (auto& pLayer : _pLayers) {
        pLayer->fadeAllLedsToBlack();
    }
}

void LightLayerManager::getTotalLedColors(struct CRGB* pTargetLedArray) {
    fill_solid(pTargetLedArray, _numLeds, CRGB::Black);
    for (auto& pLayer : _pLayers) {
        pLayer->addGammaCorrectedColors(pTargetLedArray, _brightness);
    }
}

void LightLayerManager::setBrightness(byte brightness) {
    _brightness = brightness;
}

bool LightLayerManager::isColorTransitionComplete() const {
    for (auto& pLayer : _pLayers) {
        if (!pLayer->isLedFadingComplete()) {
            return false;
        }
    }
    return true;
}

void LightLayerManager::loopTaskWrapper(void* parameter) {
    _instance->loopTask();
}


void LightLayerManager::loopTask() {

    while (true) {

        for (auto& pLayer : _pLayers) {
            pLayer->updateLeds();
        }

        vTaskDelay(INTERVAL_MS_LIGHT_MANAGER_LOOP / portTICK_PERIOD_MS);
    }
}
