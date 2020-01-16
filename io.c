#include <stdint.h>
#include <pic32mx.h>

/*
PORTX has value
TRISX determines if I or O
TRIS = 1 -> Input
TRIS = 0 -> Output

LEDs (LDX)
Pin# 26-33 (8-1)
PIC32 Signal RE0-7

Btns (BTNX)
Pin# 4, 34, 36, 37 (1-4)
PIC32 Signal RF1, RD5-7

Switches (SWX)
Pin# 2, 7, 8, 35 (1-4)
PIC32 Signal RD8-11 

Pot (A0)
Pin# 14
PIC32 Signal RB2
*/

//Initializes IO as IO
void initIO()
{
    TRISECLR = 0xFF;  //LEDs 1-8
    PORTE    = 0x0;
    TRISDSET = 0xF00; //Switches 1-4
    TRISFSET = 0x2;   //BTN 1
    TRISDSET = 0xE0;  //BTNs 2-4
    //TRISBSET = 0x4;
}

//Gets switches
uint8_t getSWs()
{
    uint8_t sw = PORTD >> 8;
    sw &= 0xf;
    return sw;
}

//Gets buttons
uint8_t getBTNs()
{
    uint8_t btn1 = PORTF >> 1;
    btn1 &= 0x1;
    uint8_t btns = PORTD >> 4;
    btns &= 0xE;
    btns |= btn1;
    return btns;
}

//returns switches and buttons
uint8_t getInputs()
{
    return (getSWs() << 4) | getBTNs();
}

//Sets LEDs
void setLEDs(uint8_t leds)
{
    PORTE = leds;
}