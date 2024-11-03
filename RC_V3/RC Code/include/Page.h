#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>

// Base class
class Page
{
public:
    virtual void init() = 0;
    virtual void loop() = 0;    
    virtual ~Page() = default;
};


// Derived class: HomePage
class HomePage : public Page
{
public:
    void loop() override;
    void init() override;
};


// Derived class: DemoControlsPage
class DemoControlsPage : public Page
{
public:
    String string11;
    void loop() override;
    void init() override;
};


// Derived class: MenuPage
class MainMenuPage : public Page
{
public:
    void loop() override;
    void init() override;
};

#endif // PAGES_H