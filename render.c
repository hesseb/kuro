#include <stdint.h>
#include "structs.h"
#include "stage.h"

/*Defines*/
#define ITOA_BUFSIZ (24)
/*=======================*/

/*======== Globals ====== */
//Basically fonts and a few sprites

const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
//8 V
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
//16 V
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
//24 V	
    0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
//32 V	
    0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
//40 V	
    0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
//48 V	
    0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
//56 V	
    0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
//64 V	
    0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
//72 V	
    0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
//80 V	
    0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
//88 V	
    0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
//96 V	
    0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
    0, 0, 80, 152, 152, 112, 0, 0,
//104 V	
    0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
//112 V
    0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
    0, 56, 64, 32, 64, 56, 0, 0,
//120 V
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};

uint8_t stageLetters[] = {
	0xB8, 0xA8, 0xE8, 0x0,
    0x08, 0xF8, 0x08, 0x0,
    0xF8, 0x28, 0xF8, 0x0,
    0xF8, 0x88, 0xE8, 0x0,
    0xF8, 0xA8, 0x88, 0x0};

uint8_t ptsLetters[]   = {
	0xF8, 0x28, 0x38, 0x0,
    0x08, 0xF8, 0x08, 0x0,
    0xB8, 0xA8, 0xE8, 0x0};

uint8_t cross[] = {
	0xA0, 0x40, 0xA0};

uint8_t numbers[]  = {
	0xF8, 0x88, 0xF8, //0
	0x08, 0xF8, 0x00, //1
    0xE8, 0xA8, 0xB8, //2
    0x88, 0xA8, 0xF8, //3
	0x38, 0x20, 0xF8, //4
	0xB8, 0xA8, 0xE8, //5
	0xF8, 0xA8, 0xE8, //6
	0x08, 0xE8, 0x18, //7
	0xF8, 0xA8, 0xF8, //8
	0xB8, 0xA8, 0xF8};//9

uint8_t heartUI[] = {
	0x30, 0x48, 0x90,
	0x48, 0x30};
/* ======================= */

/* ========= Forward functions ========= */

void clearUIArea(uint8_t * displayBuffer);  //Clears the area where the UI will be rendered, not being used right now, so for instance character gets rendered there
void debugPrint(int line, char *s, char* textbuffer); //Printes a debug message
char * itoaconv(int num); //converts integers to strings
void renderEntity(struct StageEntity se, uint8_t * displayBuffer, int camX); //Renders entities such as coins, spikes, hearts
void renderPlayer(struct Player* p, uint8_t * displayBuffer, struct Camera* c);  //Renders the player
void renderSelector(struct sparseNode* selector, int selLen, struct sparseNode* choicePos, uint8_t * displayBuffer); //Renders the main menu selector
void renderStage(struct Stage* s, struct Player* p, struct Camera* c, uint8_t * displayBuffer); //Renders the whole stage (calls stagecomponent and entity)
void renderStageComponent(struct StageComponent* sComp, uint8_t * displayBuffer, int compOffset, int camX); //Renders components of the stage
void renderText(char * textBuffer, uint8_t * displayBuffer, int lines, int offset); //Renders text? Obsolete?
void renderUI(int stageNum, int score, int hearts, int lives, uint8_t * displayBuffer); //Renders the UI
void setBit(uint8_t* byte, uint8_t b); //Sets a bit in the display buffer 
int validBufferCoords(int B, int b); //Checks whether the B and b buffer coordinates are valid
int validDisplayCoords(int x, int y); //Checks whether the x and y display coordinates are valid. obsolete?

/* ======================================*/

/* ========= Functions =========== */
//Clears the area behind the UI. Not in use right now though
void clearUIArea(uint8_t * displayBuffer)
{
    int i;
    uint8_t clearUI = 0x3;        //UI only uses the bottom five bits, so the rest should remain as is
    int rowSize = 128;
    int bufferRowStart = 3*rowSize;    //Where we start writing to the buffer
    for (i = 0; i < rowSize; i++)
    {
        displayBuffer[i+bufferRowStart] &= clearUI;
    }
}

//Prepares the text buffer to display a debug message. NOT OUR FUNCTION, TAKE FROM LAB FILES.
void debugPrint(int line, char *s, char* textbuffer)
{
    int i, j;
    if(line < 0 || line >= 4) return;
    if(!s) return;

	j = 0;
    for(i = 0; i < 16; i++)
    {
        if(*s)
        {
            textbuffer[line*16 + i] = *s;
            s++;
        }
        else if (j < 2)
		{
			textbuffer[line*16 + i] = ' ';
			j++;
		}
		else break;
    }
}

//Converts int to string. NOT OUR FUNCTION. TAKEN FROM LAB FILES
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}

/*
Render functions in general follow the same procedure.
Take sprite coordinates, transform to global coordinates by adding global sprite position,
transform to camera coordinates by subtracting the cameras x position.
Transform to buffer coordinates.
Check if these are valid.
*/



//Renders entities such as coins, spikes, hearts, endflag
void renderEntity(struct StageEntity se, uint8_t * displayBuffer, int camX)
{
	int i;

	int16_t xVal;
	int8_t yVal;
	int B, b;
	
	if (se.isActive)  //Checks if the entity is active. I.e. a taken coin shouldnt show
	{
		for (i = 0; i < se.sprSize; i++)
		{
			//Transforms sprite coordinates to global coordinates and then to camera coordinates
			xVal = se.spr[i].x + se.x - camX;  
			yVal = se.spr[i].y + se.y;

			//Checks the coordinates are on the screen
			if (!validDisplayCoords(xVal, yVal)) continue;

			//Transforms screen coordinates to buffer coordinates
			B = (yVal / 8) * 128 + xVal;
			b = yVal % 8;

			//Checks the buffer coordinates are valid (to not say overflow) and sets the bit
			if (validBufferCoords(B, b)) setBit(&displayBuffer[B], b);
		}
	}
}

//Renders the player character
void renderPlayer(struct Player* p, uint8_t * displayBuffer, struct Camera* c)
{
	int16_t xVal;
	int8_t yVal;
	int B, b; 
	int i;

	int sign = 1;
	//Picks what sprite to render based on if jumping, standing, falling, dashing
	struct sparseNode* spr;
	int sprSize;

	//if dashing
	if (p->dashStage > 27) 
	{
		spr = p->sprDash;
		sprSize = p->sprDashSize;
	}
	//if falling
	else if (p->yVel > 0){
		spr = p->sprFall;
		sprSize = p->sprFallSize;
	}
	else if (p->state == jumping){
		//if mid air during jump
		if (((p->yVel <= 0) && (p->yVel >= -1)) /*|| (p->y - p->height <= 0)*/){
			spr = p->sprAir;
			sprSize = p->sprAirSize;
		}
		//if jumping up
		else{
			spr = p->sprJump;
			sprSize = p->sprJumpSize;
		}
	}
	//regular standing sprite
	else
	{
		spr = p->spr;
		sprSize = p->sprSize;
	}

	//checks if sprite should be mirrored
	if (p->facing == right) sign = 1;
	else if (p->facing == left) sign = -1;

	//checks if sprite should be displayed due to damage flashing
	if((p->damageTimeout >= 60) ||
		((p->damageTimeout >= 0) && (p->damageTimeout < 5)) ||
		((p->damageTimeout >= 10) && (p->damageTimeout < 15)) ||
		((p->damageTimeout >= 20) && (p->damageTimeout < 25)) ||
		((p->damageTimeout >= 30) && (p->damageTimeout < 35)) ||
		((p->damageTimeout >= 40) && (p->damageTimeout < 45)) ||
		((p->damageTimeout >= 50) && (p->damageTimeout < 55)))
	{
		for ( i = 0; i < sprSize; i++)
		{
			//if mirroring subtract sprite coords instead of adding
			xVal = sign*spr[i].x + p->x - c->x;
			yVal = spr[i].y + p->y;
			
			//if (yVal > p->y) continue;
			if (!validDisplayCoords(xVal, yVal)) continue;

			B = (yVal / 8) * 128 + xVal;
			b = yVal % 8;
			
			if (validBufferCoords(B, b)) setBit(&displayBuffer[B], b);
		}
	}
}

//Actually transfers the text buffer to the display buffer to display the debug message. NOT OUR FUNCTION. TAKEN FROM LAB FILES
void renderText(char * textBuffer, uint8_t * displayBuffer, int lines, int offset)
{
    int i, j, k;
    int c;
    for(i = 0; i < lines; i++)
    {
        for(j = 0; j < 16; j++)
        {
	        c = textBuffer[i*16+j];
		    
            if(c & 0x80) continue;
			
		    for(k = 0; k < 8; k++)
            {
                displayBuffer[offset + j*8 +k] = font[c*8 + k];
            }
	    }
    }
}

//Renders the selector during the main menu
void renderSelector(struct sparseNode* selector, int selLen, struct sparseNode* choicePos, uint8_t * displayBuffer)
{
	int16_t xVal;
	int8_t yVal;
	int B, b; 
	int i;

	for ( i = 0; i < selLen; i++)
	{
		xVal = selector[i].x + choicePos->x;
		yVal = selector[i].y + choicePos->y;
		
		if (!validDisplayCoords(xVal, yVal)) continue;

		B = (yVal / 8) * 128 + xVal;
		b = yVal % 8;

		if (validBufferCoords(B, b)) setBit(&displayBuffer[B], b);
	}
}

//Renders the stage during gameplay
void renderStage(struct Stage* s, struct Player* p, struct Camera* c, uint8_t * displayBuffer)
{
	int i;
	int activeComp = getActiveStgComponent(p, s); //gets what component the player is standing on

	//"renders" 3 components backwards and 3 forward
	for (i = activeComp - 3; i < activeComp + 4; i++)
	{
		if (i < 0) continue;            //checks if compNum is valid
		if (i > s->numComps) continue;

		//adds an offset for the component based on comp order to transform from comp coordinates to global
		int compOffset = i*(s->xMax/s->numComps);
		if (compOffset > c->x + c->width) continue; //if outside camera, skip
		if (compOffset + (s->xMax/s->numComps) - 1< c->x) continue;
		renderStageComponent(s->stageComponents[i], displayBuffer, compOffset, c->x); //render component
	}

	for (i = 0; i < s->numSEntities; i++)
	{
		renderEntity(s->stageEntities[i], displayBuffer, c->x); //render entities
	}
}

//Renders a stage component
void renderStageComponent(struct StageComponent* sComp, uint8_t * displayBuffer, int compOffset, int camX)
{
	int16_t xVal;
	int8_t yVal;
	int B, b;
	int i;

	for ( i = 0; i < sComp->sprSize; i++)
	{
		xVal = sComp->spr[i].x + compOffset - camX;
		yVal = sComp->spr[i].y;
		
		if (!validDisplayCoords(xVal, yVal)) continue;

		B = (yVal / 8) * 128 + xVal;
		b = yVal % 8;
		
		if (validBufferCoords(B, b)) setBit(&displayBuffer[B], b);
	}
}

//Renders all the UI components during gameplay
void renderUI(int stageNum, int score, int hearts, int lives, uint8_t * displayBuffer)
{
    //clearUIArea(displayBuffer); // if wanted clears the area behind the UI
    
    int i;
    int rowStart = 3*128+3;
	int adapt = 0;
	//Render Stage letters
    for (i = 0; i < 20; i++) displayBuffer[rowStart+i] |= stageLetters[i];

	//Render Stage number
    rowStart += 22;
	stageNum %= 100;
    if(stageNum >= 0)
    {
		int tens = 0;
		for (i = 0; i < 10; i++){
			if (stageNum >= 10)
			{
				tens++;
				stageNum -= 10;
			}
			else break;
		}
		if (tens > 0)
		{
			for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(tens)*3 + i];
			rowStart += 4;
			adapt += 4;
		}
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(stageNum)*3 + i];
    }
	

    rowStart += 25 - adapt;
	//Renders score
	score %= 100000;
    
	if(score >= 0)
    {
		int tens = 0;
		int hundreds = 0;
		int thousands = 0;
		int tensthousands = 0;
		for (i = 0; i < 10; i++){
			if (score >= 10000)
			{
				tensthousands++;
				score -= 10000;
			}
			else break;
		}
		for (i = 0; i < 10; i++){
			if (score >= 1000)
			{
				thousands++;
				score -= 1000;
			}
			else break;
		}
		for (i = 0; i < 10; i++){
			if (score >= 100)
			{
				hundreds++;
				score -= 100;
			}
			else break;
		}
		for (i = 0; i < 10; i++){
			if (score >= 10)
			{
				tens++;
				score -= 10;
			}
			else break;
		}
		
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(tensthousands)*3 + i];
		rowStart += 4;

		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(thousands)*3 + i];
		rowStart += 4;
		
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(hundreds)*3 + i];
		rowStart += 4;
		
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(tens)*3 + i];
		rowStart += 4;
		
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(score)*3 + i];
		rowStart += 4;
    }

	//renders PTS 
    for (i = 0; i < 12; i++) displayBuffer[rowStart+i] |= ptsLetters[i];
	
	rowStart += 25;

	//renders lives
	lives %= 100;
    if(lives >= 0)
    {
		int tens = 0;
		for (i = 0; i < 10; i++){
			if (lives >= 10)
			{
				tens++;
				lives -= 10;
			}
			else break;
		}
		if (tens > 0)
		{
			for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(tens)*3 + i];
			rowStart += 4;
			adapt += 4;
		}
		for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= numbers[(lives)*3 + i];
    }
	
	rowStart += 4;
	//renders lives cross
	for (i = 0; i < 3; i++) displayBuffer[rowStart+i] |= cross[i];

	rowStart+=7;

	//renders hitpoints/hearts
    switch(hearts)
    {
        case 3:
			for (i = 0; i < 5; i++) displayBuffer[rowStart+i] |= heartUI[i];
			rowStart+=8;
        case 2:
			for (i = 0; i < 5; i++) displayBuffer[rowStart+i] |= heartUI[i];
            rowStart+=8;
        case 1:
			for (i = 0; i < 5; i++) displayBuffer[rowStart+i] |= heartUI[i];
    }
}

//Sets a bit to the display buffer
void setBit(uint8_t* byte, uint8_t b)
{
	*byte |= ((uint8_t) 1 << b);
}

//Checks if the buffer coords B and b are valid
int validBufferCoords(int B, int b)
{
	if (b > 7) return 0;
	if (b < 0) return 0;
	if (B > 511) return 0;
	if (B < 0) return 0;
	return 1;
}

//Checks if the display coords x and y are valid
int validDisplayCoords(int x, int y)
{
	if (y > 31) return 0;
	if (y < 0) return 0;
	if (x > 127) return 0;
	if (x < 0) return 0;
	return 1;
}


