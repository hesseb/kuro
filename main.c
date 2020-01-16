#include <stdint.h>
#include <pic32mx.h>
#include "display.h"
#include "chrono.h"
#include "render.h"
#include "structs.h"
#include "entity.h"
#include "stage.h"
#include "io.h"
// Include order matters!

/*======== Definitions ========*/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_PAGES 4
#define DISPLAY_SIZE DISPLAY_WIDTH * DISPLAY_PAGES //number of bytes in display buffer

//Interval between updates of the game logic. 160 -> 60Hz, 190 -> 52Hz
#define UPDATE_INTERVAL 190 //clock measures s *10^-4, not -3 so 160 -> 16ms

//Input masks
#define SW_1  0x80
#define SW_2  0x40
#define SW_3  0x20
#define SW_4  0x10
#define BTN_1 0x8
#define BTN_2 0x4
#define BTN_3 0x2
#define BTN_4 0x1
/*==================================*/

/*======== Forward Functions ========*/
void gameLoop();                  //Where the magic happens during gameplay
void user_isr();				  //Interrupt service to measure clock time
void start(); 					  //Initializes values, starts clocks, displays and stuff like that
void inputHandler();              //Polls inputs 
void update();					  //Updates logic according to inputs
void respawn();				      //Respawns if PC fell in hole or har no more hitPoints or starting new stage
void render();					  //Renders all parts of screen during gameplay
void debug(int line, char *s);    //Displays debug message
void frameInfo(long clk);         //Displays frametime and frames per second
void revive();					  //Respawns at start of stage if out of lives, also nulls score
void showCredits();				  //Shows credits screen
void showTutorial();			  //Shows controls screen
void mainMenu();				  //Title screen, allows to start new game, see credits. Game loops back here after completed game
/*==================================*/

/*======== Globals  ========*/
char textBuffer[4*16];       //Text buffer for debug output

uint8_t displayBuffer[DISPLAY_SIZE];    //Display buffer
uint8_t creditsScreen[DISPLAY_SIZE] =
{ //byte informatin of credits screen
	//Page 0
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,120,
	//Page 0
	20,120,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 1
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 14,17,17,12,0,222,69,158,
	//Page 1
	0,223,2,223,0,31,21,17, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 2
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,60, 10,60,0,62,32,32,0,62, 42,34,0,54,8,54,0,60, 10,60,0,62,4,60,0,62, 34,28,0,62,42,34,0,62, 10,52,0,0,0,0,0,0, 0,0,0,0,0,7,5,2,
	//Page 2
	224,4,5,3,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,16, 32,30,0,156,34,156,0,62, 4,60,0,60,138,60,0,46, 42,58,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 3
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,62, 8,62,0,62,42,34,0,46, 42,58,0,46,42,58,0,62, 42,34,0,62,42,20,0,28, 34,28,0,62,10,52,0,62, 4,60,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 3
	63,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,46, 42,58,0,60,10,60,0,30, 32,30,0,60,10,60,0,46, 42,58,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
};
uint8_t mainMenuBuffer[DISPLAY_SIZE] =
{ //byte information of menu
	//Page 0
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,128,128,128,128,128,128,0, 0,0,0,0,0,0,0,254, 255,112,56,60,54,114,226,128, 0,0,128,0,0,224,242,26, 6,2,0,0,254,254,0,0,
	//Page 0
	128,0,0,254,254,2,2,6, 14,252,248,0,0,128,0,0, 248,252,4,2,2,2,6,12, 252,248,0,0,0,0,0,0, 0,0,128,128,128,128,128,128, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 1
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,31, 15,0,0,0,128,96,63,31, 0,0,0,0,0,7,15,24, 16,16,16,16,31,31,0,0,
	//Page 1
	0,0,0,31,63,0,6,14, 29,49,96,128,0,0,0,0, 7,15,28,24,16,16,16,8, 15,7,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 2
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 248,40,16,0,248,128,128,0, 240,40,240,0,152,160,120,0,
	//Page 2
	0,0,248,136,232,0,240,40, 240,0,248,16,248,0,248,168, 136,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	//Page 3
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,248,136,136,0,248, 40,208,0,248,168,136,0,248,
	//Page 3
	136,112,0,136,248,136,0,8, 248,8,0,184,168,232,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
};
uint8_t tutorialScreen[DISPLAY_SIZE] =
{ //byte information of controls/tutorial screen
	//Page 0
	0,0,0,0,0,0,0,0, 0,124,64,64,0,124,84, 68,  0,124,20,4,0,4,124,4, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,124, 20,104,0,68,124,68,0,124, 68,116,0,124,16,124,0,4, 124,4,0,0,0,0,0,0,
	//Page 0
	0,0,0,0,0,0,0,0, 0,32,64,60,0, 60,64,124,  0,124,8,124,0,124,20,8, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,124,68,56,0,120,20,120, 0,92,84,116,0,124,16,124, 0,0,0,0,0,0,0,0,
	//Page 1
	0,0,0,0,0,0,0,0, 0,1,1,1,1,1,1,1, 29,17,17,17,17,17,16,16, 16,16,16,16,16,16,16,16, 16,16,16,112,0,0,0,1, 1,1,1,1,1,1,1,1, 29,17,17,17,17,17,113,1, 1,1,0,0,0,0,0,0,
	//Page 1
	0,0,0,0,0,0,0,0, 0,0,113,17,17,17,17,17, 29,1,1,1,1,1,1,0, 0,0,0,0,0,112,16,16, 16,16,16,16,16,16,16,16, 16,17,17,17,17,17,17,17, 29,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	//Page 2
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,255,1,5, 225,241,249,249,25,249,241,225, 5,1,255,0,0,0,0,0, 255,1,5,225,241,249,89,153, 249,241,225,5,1,255,0,0,
	//Page 2
	0,0,0,255,1,5,225,241, 249,89,25,249,241,225,5,1, 255,0,0,0,0,0,255,1, 5,225,241,25,121,25,249,241, 225,5,1,255,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,	
	//Page 3
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,63,32,40, 33,35,39,39,36,39,35,33, 40,32,63,0,0,0,0,0, 63,32,40,33,35,39,38,38, 39,35,33,40,32,63,0,0,
	//Page 3
	0,0,0,63,32,40,33,35, 39,37,36,39,35,33,40,32, 63,0,0,0,0,0,63,32, 40,33,35,39,39,36,39,35, 33,40,32,63,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};

struct sparseNode heartSelector[] =         //Sprite for selector in main menu
{                
    	    {1, -4},        {3, -4},
	{0, -3},        {2, -3},        {4, -3},
   	{0, -2},                        {4, -2}, 
 	        {1, -1},        {3, -1},
	                {2,  0}
};
int selectorLen = 10;                     //Sprite length
struct sparseNode choicePos = {0,0};      //Position of selector when rendering

int gameFinished = 0;    //Flag that tells gameLoop to exit
int currStage;			 //What stage we currently are on
struct Stage* stage;     //Reference to current stage struct
struct Camera camera = { //Camera struct that determines what gets rendered
	0,              //camera xpos
	0,				//camera ypos
	48,				//left boundary to start scrolling
	80,				//right boundary to start scrolling
	DISPLAY_WIDTH,  //camera width
	DISPLAY_HEIGHT  //camera height
};

struct Player* player;  //Reference to player struct
uint8_t respawnTimer;   //Timer until respawn
//int8_t direction = 0;   //Obsolete due to player->facing, but still in use

uint8_t inputs;         //Inputs -> BTN1-4, SW1-4
uint8_t debugOn = 0;    //If debug text should be shown
uint8_t ftOrFps = 0; //0 = ft, 1 = Fps; whether frametime or framerate should be shown


/*==================================*/

/*====== MAIN ======*/
int main()
{
	start();
	while(1) mainMenu();
	return 0;
}
/*=================*/

/*====== ISR ======*/
void user_isr()
{
	if (IFS(0) & 0x10000)
 	{
    	IFS(0) &= ~0x10000;
		tickClk();
  	}
}
/*=================*/

/*================= Functions =================*/

//Initializes times, display and IO
void start()
{
	initTimers();
	displayInit();
	initIO();
}


//Displayes title screen and lets player start new game, show credits or controls
void mainMenu()
{
	int choice = 1;

	while(1)
	{
		//Input handling within menu
		inputHandler();
		if(inputs & BTN_1)	choice = 1;
		if(inputs & BTN_2)	choice = 2;
		if(inputs & BTN_3)
		{
			switch(choice)
			{
				case 1:
					showTutorial(); 
					gameLoop();       //Here the game starts
					break;
				case 2:
					showCredits();
					break;
			}
		}
		if(inputs & BTN_4) showTutorial();  //Not in the UI, but works

		//Determines where the selector appears on screen
		switch(choice)
		{
			case 1:
				choicePos.x = 40;
				choicePos.y = 23;
				break;
			case 2:
				choicePos.x = 40;
				choicePos.y = 31;
				break;
			default:
				choice = 1;
				choicePos.x = 40;
				choicePos.y = 23;
		}

		//Copies the static data over to the displayBuffer
		int i;
		for(i = 0; i < DISPLAY_SIZE; i++) displayBuffer[i] = mainMenuBuffer[i];

		//Render
		renderSelector(heartSelector, selectorLen, &choicePos, displayBuffer);
		displayUpdate(displayBuffer);
		
		//Delay to stabilize rendering to around 60fps
		delayms(15);
	}
	return;
}

void inputHandler()
{
	inputs = getInputs();            //get inputs from board
	setLEDs(inputs);                 //sets LEDs to match buttons and switches used
	debugOn = (inputs & SW_1) >> 7;  //determines if debug text should be displayed
	ftOrFps = (inputs & SW_2) >> 6;  //determines if framerate or fps should be displayed in debug
}

void showCredits() //shows credits for 6s
{
	displayUpdate(creditsScreen);
	delayds(60);
}

void showTutorial() //shows controls for 3s
{
	displayUpdate(tutorialScreen);
	delayds(30);
}


//Meat of the program, here all gameplay happens
void gameLoop(){
	
	gameFinished = 0; //flag to tell gameLoop if we should return to menu

	//Current stage info and initializing entities
	currStage = 0;
	stage = getStage(currStage);
	initStageEntities(stage);
	
	//Gets player entity and initializes some values
	player = getPlayer();
	player->damageTimeout = 60;
	player->facing = right;
	player->x = 6;
	player->lives = 2;
	player->hitPoints = 3;
	player->score = 0;
	player->dashStage = 0;

	/*Initializes clock variables needed to control game loop.
	//Basically we want the display to update as fast as possible while keeping the
	//game logic updating at a fix rate (determined by UPDATE_INTERVAL).
	//The way we do this is each cycle increment lag with the duration of the cycle
	// and only update the logic when lag > UPDATE_INTERVAL, then we subtract UPDATE INTERVAL
	// from lag.
	*/
	long startClk;
	long endClk;
	long previous = getClk();
	long lag = 0;
	long elapsed;

	while(1)
	{
		if (gameFinished) return;

		startClk = getClk();
		elapsed = startClk - previous;
		previous = startClk;
		lag += elapsed;

		inputHandler();
		
		while (lag >= UPDATE_INTERVAL)
		{
			update();
			lag -= UPDATE_INTERVAL;
		} 

		//delayms(95);
		render();
		endClk = getClk();
		frameInfo(endClk - startClk);
	}
	return;
}

//Frametime or framerate displayed as debug
void frameInfo(long clk)
{
	if (ftOrFps == 0) debug(0, itoaconv(clk/10));
	else debug(0, itoaconv(1000/(clk/10)));
}

//Display something as debug
void debug(int line, char *s)
{
	debugPrint(line, s, textBuffer);
}

//Updates all game logic in response to inputs or state changes
//Three main checks: state change as in respawning or end of stage/game
// Input change
// Camera change
void update()
{
	/*Checks if player is in the process of respawning*/
	if(player->state == respawning)
	{
		if(respawnTimer == 15){
			respawn(player, stage);
		}
		if(respawnTimer >= 30)
		{
			player->state = standing; //Only gives control to player here
			respawnTimer = 0;
		}
		respawnTimer++;
	}

	/*Checks if the stage is completed and either ends the game or loads the next stage (technically both if last stage, but you get my point)*/
	if(stage->stageCompleted)
	{
		currStage++;
		stage->stageCompleted = 0;
		
		if (currStage >= getNumStages())
		{
			currStage = 0;
			gameFinished = 1;
			showCredits();
		}
		stage = getStage(currStage);
		initStageEntities(stage);
		revive();  //revive used to reset player to beginning of new stage, score is not changed though
	}

	/* ==== PC input handling ==== */
	if((player->state == jumping) || (player->state == standing))
	{
		if(player->dashStage > 0) player->dashStage--; 
		if (player->damageTimeout <= 60) player->damageTimeout++;
		
		//When moving we mirror the sprite, so not to break collisions we also change the position of the character to
		//compensate for the sprite changing side. This in practice, neutralizes the changing position.
		if(inputs & BTN_1)
		{
			if(player->facing == right)
			{
				player->facing = left;
				player->x += player->width;
			}
			player->xVel--;
			//direction = -1;
		}
		
		if(inputs & BTN_2)
		{
			if(player->facing == left)
			{
				player->facing = right;
				player->x -= player->width;
			}
			player->xVel++;
			//direction = 1;
		}
		
		if(player->state == standing){
			if(inputs & BTN_3)
			{
				jump(player);
			}
		}

		//Dash has some cooldowns for how long it lasts and how often you can use it
		if((inputs & BTN_4) && ((player->dashStage == 0) || (player->dashStage > 28)))
		{
			int direction = 1;
			if (player->facing == left) direction = -1;
			player->xVel = direction*3;
			if(player->dashStage == 0) player->dashStage += 35;

			/*if ((inputs & SW_3) || (inputs & SW_4))   //Forced teleport routine for debug purposes
			{
				if (inputs & SW_3) player->x = 110;
				if (inputs & SW_4) player->x = 3;
				player->y = 24;
				player->yVel = 0;
				player->xVel = 0;
			}*/
		}
		updateChar(player, stage);   //After processing input, update values
	}
	/* ========================== */
	
	/* ====  Camera updating ==== */
	//Basically gives us values to transform global stage coordinates to coordinates that fit within the screen

	int sign = 1;
	if (player->facing == right) sign = 1;
	if (player->facing == left ) sign =-1;

	int playerAnchor = player->x + sign*player->width/2; //anchors player position at half width to avoid the camera jumping around when facing right or left

	if (playerAnchor < (camera.x + camera.xLeft))
	{
		camera.x = playerAnchor - camera.xLeft;
	}
	else if (playerAnchor > (camera.x + camera.xRight))
	{
		camera.x = playerAnchor - camera.xRight;
	}
	if (camera.x < 0) camera.x = 0;
	if (camera.x > (stage->xMax - DISPLAY_WIDTH)) camera.x = (stage->xMax - DISPLAY_WIDTH);
	/* ============================*/
}


void render()
{
	clearBuffer(displayBuffer); //Clears the buffer from previous frame

	/*if (ftOrFps == 0) debug(0, itoaconv(player->x));
	else debug(0, itoaconv(camera.x));*/

	if(debugOn == 1) renderText(textBuffer, displayBuffer, 1, 0); //renders debug
	renderPlayer(player, displayBuffer, &camera);                 //renders players
	renderStage(stage, player, &camera, displayBuffer);           //renders stage
	renderUI(currStage + 1, player->score, player->hitPoints, player->lives, displayBuffer); //renders UI

	displayUpdate(displayBuffer); //displays new buffer
}

//Handles what happens when you fall into a hole, have no more hitpoints
void respawn(struct Player* p, struct Stage* s)
{
	if (p->lives < 0){
		revive();
		return;
	}

	int i = getActiveStgComponent(p, s) - 1;
	if (i < 0) i = 0;
	p->x = s->stageComponents[i]->xSpawn + i*(s->xMax / s->numComps);
	p->y = s->stageComponents[i]->ySpawn;
	p->xVel = 0;
	p->yVel = 0;
}

//When you die or start a new stage
void revive()
{
	player->x = 3;
	player->y = 24;
	player->xVel = 0;
	player->yVel = 0;

	if (player->lives < 0){
		player->lives = 2;
		player->hitPoints = 3;
		player->score = 0;
	}
	resetEntities(stage);
}

