#include <stdint.h>
#include <pic32mx.h>
#include "chrono.h"

#define bitVddCtrl 0x40
#define bitVbatCtrl 0x20
#define bitDataCmd 0x10
#define bitReset 0x200

#define displaySize 512
#define numColumns 128 //number of display columns
#define numPages 4 //number of display memory pages

/* ------------------------------------------------------------ */
/*** SPI2SendByte
** Write/Read a byte on SPI port 2
** Parameters: byteVal - byte value to write
** Return Value: Returns byte read
*/

uint8_t SPI2SendByte(uint8_t byteVal)
{
	uint8_t byteReturn;
	/* Wait for transmitter to be ready */
	while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

	/* Write the next transmit byte. */
	SPI2BUF = byteVal;
	
	/* Wait for receive byte. */
	while ((SPI2STAT & PIC32_SPISTAT_SPIRBF) == 0);	
	/* Put the received byte in the buffer. */
	byteReturn = SPI2BUF;
	return byteReturn;
}

/* ------------------------------------------------------------ */
/*** HostInit
** Perform PIC32 device initialization to prepare for use of the OLED
** display. This example is hard coded for the chipKIT Uno32 and SPI2.
*/
void hostInit()
{
	/* Initialize SPI port 2.*/
	SPI2CON = 0;
	SPI2BRG = 15; //8Mhz, with 80Mhz PB clock
	SPI2STATCLR = PIC32_SPISTAT_SPIROV;
	SPI2CONSET = PIC32_SPICON_CKP;
	SPI2CONSET = PIC32_SPICON_MSTEN;
	SPI2CONSET = PIC32_SPICON_ON;
	
	/* Make pins RF4, RF5, and RF6 be outputs.*/
	PORTFSET = bitVddCtrl|bitVbatCtrl|bitDataCmd;

	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Make the RG9 pin be an output. On the Basic I/O Shield, this pin is tied to reset.*/
	PORTGSET = bitReset;
}

/* ------------------------------------------------------------ */
/*** DspInit
** Initialize the OLED display controller and turn the display on.
*/
void dspInit()
{
	/* We're going to be sending commands, so clear the Data/Cmd bit*/
	PORTFCLR = bitDataCmd;
	
	/* Start by turning VDD on and wait a while for the power to come up.*/
	PORTFCLR = bitVddCtrl;
	delayms(1);
	
	/* Display off command*/
	SPI2SendByte(0xAE);
	
	/* Bring Reset low and then high*/
	PORTGCLR = bitReset;
	delayms(1);
	
	PORTGSET = bitReset;

	/* Send the Set Charge Pump and Set Pre-Charge Period commands*/
	SPI2SendByte(0x8D);
	SPI2SendByte(0x14);
	SPI2SendByte(0xD9);
	SPI2SendByte(0xF1);
	
	/* Turn on VCC and wait 100ms*/
	PORTFSET = bitVbatCtrl;
	delayms(100);
	
	/* Send the commands to invert the display. This puts the display origin in the upper left corner.*/
	SPI2SendByte(0xA1); //remap columns
	SPI2SendByte(0xC8); //remap the rows
	
	/* Send the commands to select sequential COM configuration. This makes the display memory non-interleaved.*/
	SPI2SendByte(0xDA); //set COM configuration command
	SPI2SendByte(0x20); //sequential COM, left/right remap enabled
	
	/* Send Display On command */
	SPI2SendByte(0xAF);
}


/* ------------------------------------------------------------ */
/*** DisplaySendPage
** Send the bytes specified in rgbTx to the slave.
** Parameters:
** numBytes - number of bytes to send/receive
** byteBuffer - pointer to the buffer to send
*/

void displaySendPage(int numBytes, uint8_t * byteBuffer)
{
	int i;
	uint8_t byteTemp;
	
	/* Write/Read the data */
	for (i = 0; i < numBytes; i++) {
		
		/* Wait for transmitter to be ready */
		while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

		/* Write the next transmit byte. */
		SPI2BUF = *byteBuffer++;
		
		/* Wait for receive byte. */
		while ((SPI2STAT & PIC32_SPISTAT_SPIRBF) == 0);
		byteTemp = SPI2BUF;
	}
}

//Initializes display
void displayInit()
{
    hostInit();
    dspInit();
    return;
}

//Displays new buffer
void displayUpdate(uint8_t * byteBuffer)
{
	int i;
	
	for (i = 0; i < numPages; i++) {
		PORTFCLR = bitDataCmd;

		/* Set the page address */
		SPI2SendByte(0x22); //Set page command
		SPI2SendByte(i); //page number
		
		/* Start at the left column */
		SPI2SendByte(0x00); //set low nybble of column
		SPI2SendByte(0x10); //set high nybble of column
		PORTFSET = bitDataCmd;
		
		/* Copy this memory page of display data. */
		displaySendPage(numColumns, byteBuffer);
		byteBuffer += numColumns;
	}
}

//Clears buffer 
void clearBuffer(uint8_t * byteBuffer)
{
	int i;
	for (i = 0; i < displaySize; i++) byteBuffer[i] = 0;
}
