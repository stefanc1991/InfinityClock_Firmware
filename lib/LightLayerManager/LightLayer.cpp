#include "LightLayer.h"

LightLayer::LightLayer(size_t numLeds) : _leds(numLeds) {}

void LightLayer::setDefaultSpeed(float speedInFullPerSecond) {
    _defaultSpeed = speedInFullPerSecond;
}

void LightLayer::setAllLedsToBlack() {
    setAllLedsTo(CRGB::Black);
}

void LightLayer::setAllLedsTo(CRGB color) {

    for (size_t i = 0; i < _leds.size(); i++) {
        setLedTo(i, color);
    }
}

void LightLayer::setLedTo(size_t iLed, CRGB color) {
    fadeLedTo(iLed, color, 0);
}

void LightLayer::fadeAllLedsToBlack() {
    fadeAllLedsToBlack(_defaultSpeed);
}

void LightLayer::fadeAllLedsToBlack(float speedInFullPerSecond) {
    fadeAllLedsTo(CRGB::Black, speedInFullPerSecond);
}

void LightLayer::fadeAllLedsTo(CRGB color) {
    fadeAllLedsTo(color, _defaultSpeed);
}

void LightLayer::fadeAllLedsTo(CRGB color, float speedInFullPerSecond) {
    
    for (size_t i = 0; i < _leds.size(); i++) {
        fadeLedTo(i, color, speedInFullPerSecond);
    }
}

void LightLayer::fadeLedTo(size_t iLed, CRGB targetColor) {
    fadeLedTo(iLed, targetColor, _defaultSpeed);
}

void LightLayer::fadeLedTo(size_t iLed, CRGB targetColor, float speedInFullPerSecond) {

    if (iLed >= _leds.size())
        return;

    float incrementPerSecond = 255 * speedInFullPerSecond;

    _leds[iLed].targetColor = targetColor;

    uint8_t deltaR = abs(_leds[iLed].targetColor.r - _leds[iLed].currentColor.r);
    uint8_t deltaG = abs(_leds[iLed].targetColor.g - _leds[iLed].currentColor.g);
    uint8_t deltaB = abs(_leds[iLed].targetColor.b - _leds[iLed].currentColor.b);

    uint8_t maxDelta = max(deltaR, max(deltaG, deltaB));

    if (maxDelta > 0) {
        _leds[iLed].incR = (incrementPerSecond * deltaR) / maxDelta;
        _leds[iLed].incG = (incrementPerSecond * deltaG) / maxDelta;
        _leds[iLed].incB = (incrementPerSecond * deltaB) / maxDelta;
    }
}

bool LightLayer::isLedFadingComplete(size_t iLed) const {

    if (iLed < _leds.size()) {
        return (_leds[iLed].currentColor.r == _leds[iLed].targetColor.r && _leds[iLed].currentColor.g == _leds[iLed].targetColor.g && _leds[iLed].currentColor.b == _leds[iLed].targetColor.b);
    }

    return false;
}

bool LightLayer::isLedFadingComplete() const {

    for (size_t i = 0; i < _leds.size(); i++) {

        if (!isLedFadingComplete(i)) {
            return false;
        }
    }
    
    return true;
}

void LightLayer::updateLeds() {

    unsigned long tmsNow = millis();

    for (size_t i = 0; i < _leds.size(); i++) {
        updateColorComponent(_leds[i].currentColor.r, _leds[i].targetColor.r, _leds[i].incR, _leds[i].tmsLastRUpdate, tmsNow);
        updateColorComponent(_leds[i].currentColor.g, _leds[i].targetColor.g, _leds[i].incG, _leds[i].tmsLastGUpdate, tmsNow);
        updateColorComponent(_leds[i].currentColor.b, _leds[i].targetColor.b, _leds[i].incB, _leds[i].tmsLastBUpdate, tmsNow);
    }
}

void LightLayer::updateColorComponent(uint8_t& currentColor, uint8_t targetColor, float increment, unsigned long& tmsLastUpdate, unsigned long tmsNow) {

    if (currentColor == targetColor) {
        tmsLastUpdate = tmsNow;
        return;
    }

    if (increment == 0) {
        currentColor = targetColor;
        return;
    }                                                                                        
    
    uint8_t change = increment * ((tmsNow - tmsLastUpdate) / 1000.000f);
    
    if (change > 0) {
        tmsLastUpdate = tmsNow;
        if (currentColor < targetColor) {
            currentColor = min(currentColor + change, int(targetColor));
        }
        else if (currentColor > targetColor) {
            currentColor = max(currentColor - change, int(targetColor));
        }
    }
}

void LightLayer::addGammaCorrectedColors(CRGB* pTargetLedArray, uint8_t scale) {

    for (size_t i = 0; i < _leds.size(); i++) {
        CRGB tmpColor = _leds[i].currentColor;
        tmpColor = _scaleColor(tmpColor, scale); //TODO: scale8 still distorts gamma correction
        tmpColor = _gammeDecode(tmpColor);
        pTargetLedArray[i] += tmpColor; // Overflow protected by FastLED +=
    }
}

CRGB LightLayer::_gammeEncode(CRGB color) {

    CRGB correctedColor;
    correctedColor.r = pgm_read_byte(&gamma8Encode[color.r]);
    correctedColor.g = pgm_read_byte(&gamma8Encode[color.g]);
    correctedColor.b = pgm_read_byte(&gamma8Encode[color.b]);
    return correctedColor;
}

CRGB LightLayer::_gammeDecode(CRGB color) {

    CRGB correctedColor;
    correctedColor.r = pgm_read_byte(&gamma8Decode[color.r]);
    correctedColor.g = pgm_read_byte(&gamma8Decode[color.g]);
    correctedColor.b = pgm_read_byte(&gamma8Decode[color.b]);
    return correctedColor;
}

CRGB LightLayer::_scaleColor(CRGB color, uint8_t scale) {

    CRGB correctedColor;
    correctedColor.r = scale8_video(color.r, scale);
    correctedColor.g = scale8_video(color.g, scale);
    correctedColor.b = scale8_video(color.b, scale);
    return correctedColor;
}
