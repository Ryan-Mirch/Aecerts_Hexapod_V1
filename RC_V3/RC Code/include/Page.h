#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>

// Base class
class Page
{
public:
    virtual void draw() = 0;
    virtual ~Page() = default;
};

// Derived class: HomePage
class HomePage : public Page
{
public:
    String loopTime;
    void draw() override;
};

// Derived class: DemoControlsPage
class DemoControlsPage : public Page
{
public:
    String string11;
    void draw() override;
};

#endif // PAGES_H