#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>

// Base class
class Page
{
public:
    virtual void init() = 0;
    virtual void draw() = 0;    
    virtual ~Page() = default;
};

// Derived class: HomePage
class HomePage : public Page
{
public:
    String loopTime;
    void draw() override;
    void init() override;
};

// Derived class: DemoControlsPage
class DemoControlsPage : public Page
{
public:
    String string11;
    void draw() override;
    void init() override;
};

#endif // PAGES_H