#include "C8051F330.h"

void PCA_Init()
{
    PCA0MD &= ~0x40;
    PCA0MD = 0x00;
}

void Timer_Init()
{
    TMOD = 0x20;
    TH1 = 0xFF;
}

void UART_Init()
{
    SCON0 = 0x10;
}

void Port_IO_Init()
{
    P0MDOUT = 0x10;
    XBR0 = 0x01;
    XBR1 = 0x40;
}

void Oscillator_Init()
{
    OSCICN = 0x83;
}

void Init_Device(void)
{
    PCA_Init();
    Timer_Init();
    UART_Init();
    Port_IO_Init();
    Oscillator_Init();
}
