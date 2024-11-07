#pragma once

#include <Arduino.h>

int openPopupMultiChoice(String header, String choices[], int numChoices, int hovered);
long int openPopupNumber(String header, long int initialValue, long int minValue, long int maxValue);
String openPopupString(String header, String initialValue, int stringLength);

void drawChoice(const String& s, bool hovered);
void drawHeader(const String& s);
