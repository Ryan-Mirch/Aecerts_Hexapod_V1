#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>
#include "Helpers.h"

// Base class
class Page
{
public:
    virtual void init() = 0;
    virtual void loop() = 0;
    virtual ~Page() = default;
    bool rotaryEncoderButtonReady;
};

// Home Page
class HomePage : public Page
{
public:
    void loop() override;
    void init() override;

private:
    long int startTime;
    long int totalDrawTime;
    int legAnimProgress[6];
    float points = 100;
    int strideLength = 8;

    Vector3 legs[6];
    Vector2 legsCenter[6];
};

// Demo Controls Page
class DemoControlsPage : public Page
{
public:
    String string11;
    void loop() override;
    void init() override;
};

// Menu Page
class MainMenuPage : public Page
{
public:
    void loop() override;
    void init() override;

private:
    int hovered = 0;
    int numChoices = 5;
    bool backButtonReady;
};

// Controls Page
class ControlsPage : public Page
{
public:
    void loop() override;
    void init() override;
};

// Settings Page
class SettingsPage : public Page
{
public:
    void loop() override;
    void init() override;

private:
    int hovered = 0;
};

// Stats Page
class StatsPage : public Page
{
public:
    void loop() override;
    void init() override;

private:
    int hovered = 0;
};

// Gaits Page
class GaitsPage : public Page
{
public:
    void loop() override;
    void init() override;
    void resetAnimation();

private:
    int legAnimProgress[6];
    float points = 100;
    int strideLength = 9;

    Vector3 legs[6];
    Vector2 legsCenter[6];

    int hovered = 0;
    float pushFraction = 0.5;
};

// Offsets Page
class OffsetsPage : public Page
{
public:
    void loop() override;
    void init() override;

private:
    int hovered = 0;
};

#endif // PAGES_H