#pragma once

#include <Arduino.h>

int openPopup(String header, String choices[], int numChoices, int hovered);
void drawChoice(String s, bool hovered);
void drawHeader(String s);