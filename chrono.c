#include <pic32mx.h>

long clock;

void initTimers()
{
	//PR * 10 = 1 sec,  1:256 scale, PR2 = 31250
	TMR2 = 0x0;
	PR2 = 0x7A12; //31250
	T2CON = 0b1000000001110000;

	//PR * 1000 = 1 sec,  1:64 scale
	TMR3 = 0x0;
	PR3 = 0x4E2; //1250
	T3CON = 0b1000000001100000;

	// PR * 1 000 000 = 1 sec, 1:16 scale
	TMR4 = 0x0;
	PR4 = 0x1F4;
	T4CON = 0b1000000001000000;

	//Enables interrupts
	clock = 0;
	IEC(0) |= 0x10000;
	IPC(4) |= 0x1C;
	IPC(4) |= 0x3;

	enable_interrupt();

	return;
}

void delayms(int x){
	int counter = 0;
	TMR3 = 0x0;

	while(counter < x)
	{
		if(IFS(0) & 0x1000)
		{
			IFS(0) &= ~0x1000;
			counter++;
		}
	}
	return;
}

void delayds(int x){
	int counter = 0;
	TMR2 = 0x0;

	while(counter < x)
	{
		if(IFS(0) & 0x100)
		{
			IFS(0) &= ~0x100;
			counter++;
		}
	}
	return;
}

void clearClk()
{
    clock = 0;
    return;
}

long getClk()
{
    return clock;
}

void inline tickClk()
{
    clock++;
    return;
}