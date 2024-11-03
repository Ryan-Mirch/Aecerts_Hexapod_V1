#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

void MainMenuPage::init()
{

}

void MainMenuPage::loop(){
    /*Back Button*/
    drawButton(5, 5, "A", "<-Home");
    if(getButtonValue(A) == PRESSED)currentPage = homePage;

    u8g2.drawStr(5,30,String(getRotaryEncoderTotalSpins()).c_str());
}