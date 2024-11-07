#pragma once

#include <Arduino.h>

int openPopupMultiChoice(String header, String choices[], int numChoices, int hovered);
uint32_t openPopupNumber(String header, uint32_t initialValue, uint32_t minValue, uint32_t maxValue);

void drawChoice(String s, bool hovered);
void drawHeader(String s);
