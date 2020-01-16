#include <stdint.h>
#include "structs.h"

#define numComps(stage) (sizeof(stage.stageComponents) / sizeof(stage.stageComponents[0]))

/*
Order:
SPRITES
COLLIDERS
ENTITIES
ENTITY GROUPS
STAGE COMPONENTS
STAGES
STAGE LIST
FORWARD FUNCTIONS
FUNCTIONS
*/

/*=============================================== SPRITES ===================================================*/

/* Component Sprites */

struct sparseNode flatSpr[] = {
    { 0, 25}, { 1, 25}, { 2, 25}, { 3, 25},
    { 4, 25}, { 5, 25}, { 6, 25}, { 7, 25},
    { 8, 25}, { 9, 25}, {10, 25}, {11, 25},
    {12, 25}, {13, 25}, {14, 25}, {15, 25},

    {16, 25}, {17, 25}, {18, 25}, {19, 25},
    {20, 25}, {21, 25}, {22, 25}, {23, 25},
    {24, 25}, {25, 25}, {26, 25}, {27, 25},
    {28, 25}, {29, 25}, {30, 25}, {31, 25},    
    {28, 24}, {6, 24}
};

struct sparseNode elevflatSpr[] = {

                                    { 6,11},                                                                                
                            { 5,12},                                        {11,12},                                                                                        {23,12},                                {28,12},
    { 2,13},{ 3,13},{ 4,13},{ 5,13},{ 6,13},{ 7,13},{ 8,13},{ 9,13},{10,13},{11,13},{12,13},{13,13},{14,13},{15,13},{16,13},{17,13},{18,13},{19,13},{20,13},{21,13},{22,13},{23,13},{24,13},{25,13},{26,13},{27,13},{28,13},{29,13},
    { 2,14},                                                                                                                                                                                                                {29,14},
            { 3,15},                                                                                                                                                                {24,15},                        {28,15},
                    { 4,16},                                        {10,16},                                                                                                                                {27,16},
                    { 4,17},{ 5,17},                                                                                                {18,17},                                                {25,17},{26,17},
                            { 5,18},{ 6,18},                                                                                                                                {23,18},{24,18},{25,18},
                            { 5,19},        { 7,19},                                {12,19},                                                                {21,19},        {23,19},
                                                    { 8,20},{ 9,20},                                                {16,20},{17,20},{18,20},        {20,20},        {22,20},
                                                            { 9,21},{10,21},{11,21},                {14,21},{15,21},{16,21},        {18,21},        {20,21},
                                                                    {10,22},        {12,22},        {14,22},                        {18,22},{19,22},
                                                                                            {13,23},{14,23},                                {19,23},
                                                                                            {13,24},                                        {19,24},
};

struct sparseNode dashReqSpr[] = {
    {16, 17}, {16, 18}, {16, 19}, {16, 20},
    {16, 21}, {16, 22}, {16, 23}, {16, 24},
    {16, 25},

    {16, 6}, {16, 5}, {16, 4}, {16, 3},
    {16, 2}, {16, 1}, {16, 0},

    {31, 17}, {31, 18}, {31, 19}, {31, 20},
    {31, 21}, {31, 22}, {31, 23}, {31, 24},
    {31, 25},

    {31, 6}, {31, 5}, {31, 4}, {31, 3},
    {31, 2}, {31, 1}, {31, 0},

    {16, 16}, {17, 16}, {18, 16}, {19, 16},
    {20, 16}, {21, 16}, {22, 16}, {23, 16},
    {24, 16}, {25, 16}, {26, 16}, {27, 16},
    {28, 16}, {29, 16}, {30, 16}, {31, 16}, 

    {16, 7}, {17, 7}, {18, 7}, {19, 7},
    {20, 7}, {21, 7}, {22, 7}, {23, 7},
    {24, 7}, {25, 7}, {26, 7}, {27, 7},
    {28, 7}, {29, 7}, {30, 7}, {31, 7},
};

struct sparseNode dashSpr[] = {
    {17, 17}, {17, 18}, {16, 19}, {16, 20},
    {16, 21}, {16, 22}, {16, 23}, {15, 24},
    {15, 25},


    {17, 16}, {18, 16}, {19, 16},
    {20, 16}, {21, 16}, {22, 16}, {23, 16},
    {24, 16}, {25, 16}, {26, 16}, {27, 16},
    {28, 16},  
    
    {28, 17}, {29, 18}, {29, 19}, {29, 20},
    {29, 21}, {29, 22}, {29, 23}, {29, 24},
    {29, 25},

    {30, 25}, {31, 25}, {20, 20}, {26,20},
    {25, 24}
};


struct sparseNode endSpr[] = {
    { 0, 25}, { 1, 25}, { 2, 25}, { 3, 25},
    { 4, 25}, { 5, 25}, { 6, 25}, { 7, 25},
    { 8, 25}, { 9, 25}, {10, 25}, {11, 25},
    {12, 25}, {13, 25}, {14, 25}, {15, 25},

    {16, 25}, {17, 25}, {18, 25}, {19, 25},
    {20, 25}, {21, 25}, {22, 25}, {23, 25},
    {24, 25}, {25, 25}, {26, 25}, {27, 25},
    {28, 25}, {29, 25}, {30, 25}, {31, 25},

};

struct sparseNode holeSpr[] = {
    { 0, 25}, { 1, 25}, { 2, 25}, { 3, 25},
    { 4, 25}, { 5, 25}, { 6, 25}, { 7, 25},
    { 8, 25}, { 9, 25}, {10, 25}, {10, 26},
    //{30, 26}, {30, 25}, {31, 25},
};

struct sparseNode elevSpr[] = {
    //floor before
    { 0, 25}, { 1, 25}, { 2, 25}, { 3, 25},
    { 4, 25}, { 5, 25}, { 6, 25}, { 7, 25},
    { 8, 25}, { 9, 25}, 
    
    //wall up
    { 9, 24}, {10, 23}, {10, 22}, {10, 21},
    {10, 20}, {10, 19}, {10, 18}, {10, 17},
    {10, 16}, {10, 15}, {10, 14}, {10, 13},
    {11, 12}, {11, 11},

    //floor during
    {12, 10}, {13, 10}, {14, 10},
    {15, 10}, {16, 10}, {17, 10}, {18, 10}, 
    {19, 10}, {20, 10}, {21, 10}, {22, 10}, 
    {23, 10}, {24, 10}, {25, 10}, {26, 10},
    {27, 10}, {28, 10}, {29, 10},
    
    //wall down
    {29, 11}, {30, 12}, {30, 13}, {30, 14},
    {30, 15}, {30, 16}, {30, 17}, {30, 18},
    {30, 19}, {30, 20}, {30, 21}, {30, 22},
    {30, 23}, {30, 24}, {31, 24}, 
    
    //floor after
    {31, 25},

    //texture
    {15, 20}, 
    {24, 15}, 
    {23, 22}, 
    {12, 18},
};

struct sparseNode stairSpr[] = {
    //First platform
    { 1, 22}, { 2, 22}, { 3, 22}, { 4, 22}, { 5, 22}, { 6, 22}, { 7, 22}, { 8, 22}, {9, 22}, {10, 22},
    { 1, 23},                                                                                {10, 23},
              { 2, 24}, { 3, 24},                                         { 8, 24}, { 9, 24},
                                  { 4, 25},                     { 7, 25},
                                            { 5, 26}, { 6, 26},  
    //Second platform
    {11, 19}, {12, 19}, {13, 19}, {14, 19}, {15, 19}, {16, 19}, {17, 19}, {18, 19}, {19, 19}, {20, 19},
    {11, 20},                                                                                 {20, 20},
              {12, 21}, {13, 21},                                         {18, 21}, {19, 21},
                                  {14, 22},                     {17, 22},
                                            {15, 23}, {16, 23},  
    //Third platform
    {21, 16}, {22, 16}, {23, 16}, {24, 16}, {25, 16}, {26, 16}, {27, 16}, {28, 16}, {29, 16}, {30, 16},
    {21, 17},                                                                                 {30, 17},
              {22, 18}, {23, 18},                                         {28, 18}, {29, 18},
                                  {24, 19},                     {27, 19},
                                            {25, 20}, {26, 20},  
};

/* Entity sprites */

struct sparseNode spriteCoin[] =
{                
	        {1, -4}, {2, -4}, {3, -4},
   	{0, -3},                          {4, -3},
    {0, -2},         {2, -2},         {4, -2}, 
 	{0, -1},                          {4, -1},
	        {1,  0}, {2,  0}, {3,  0}
};

struct sparseNode spriteHeart[] =
{                
    	    {1, -4},        {3, -4},
	{0, -3},        {2, -3},        {4, -3},
   	{0, -2},                        {4, -2}, 
 	        {1, -1},        {3, -1},
	                {2,  0}
};

struct sparseNode spriteSpike[] =
{                
			          		   {3, -7},
			          		   {3, -6},
			          {2, -5}, {3, -5}, {4, -5},
			          {2, -4}, {3, -4}, {4, -4},
	         {1, -3}, {2, -3}, {3, -3}, {4, -3}, {5, -3},
   			 {1, -2}, {2, -2}, {3, -2}, {4, -2}, {5, -2}, 
 	{0, -1}, {1, -1}, {2, -1}, {3, -1}, {4, -1}, {5, -1}, {6, -1},
	{0,  0}, {1,  0}, {2,  0}, {3,  0}, {4,  0}, {5,  0}, {6,  0}
};

struct sparseNode spriteInvSpike[] =
{                
	{0, -7}, {1, -7}, {2, -7}, {3, -7}, {4, -7}, {5, -7}, {6, -7},
 	{0, -6}, {1, -6}, {2, -6}, {3, -6}, {4, -6}, {5, -6}, {6, -6},
   			 {1, -5}, {2, -5}, {3, -5}, {4, -5}, {5, -5}, 
	         {1, -4}, {2, -4}, {3, -4}, {4, -4}, {5, -4},
			          {2, -3}, {3, -3}, {4, -3},
			          {2, -2}, {3, -2}, {4, -2},
			          		   {3, -1},
			          		   {3,  0},
};

struct sparseNode spriteFlag[] =
{
    {0, -11},                       //13y
    {0, -10}, {1, -10}, {2, -10},                 {5, -10}, {6, -10},  //14y        
    {0, -9},                     {3, -9}, {4, -9},                   {7, -9}, {8, -9}, {9, -9}, {10, -9},//15y
    {0, -8},                                                                  {8, -8},//16y
    {0, -7},                                                                  {8, -7}, {9, -7}, {10, -7},//17y                                       
    {0, -6},                                                         {7, -6}, 
    {0, -5}, {1, -5}, {2, -5},                    {5, -5}, {6, -5}, 
    {0, -4},                   {3, -4}, {4, -4}, 
    {0, -3},
    {0, -2},
    {0, -1},
    {0, 0}

};

/*=============================================================================================================*/

/*=============================================== COLLIDERS ===================================================*/

//Steps component
struct yColliderNode step3YCollider =
{
    16,
    21,
    30,
    0
};

struct yColliderNode step2YCollider =
{
    19,
    11,
    20,
    &step3YCollider
};

struct yColliderNode step1YCollider =
{
    22,
    0,
    10,
    &step2YCollider
};

struct xColliderNode stairXCollider =
{
    30,
    25,
    16,
    0
};

//Elev flat (platform) component
struct yColliderNode elevflatYCollider =
{
    13,
    2,
    29,
    0
};

//Flat component
struct yColliderNode flatYCollider =
{
    25,
    0,
    31,
    0
};

//Hole component
struct yColliderNode holeYCollider1 =
{
    25,
    0,
    10,
    0
};

//Elev component
struct yColliderNode elevYCollider2 =
{
    25,
    28,
    31,
    0
};

struct yColliderNode elevYCollider1 =
{
    10,
    10,
    30,
    &elevYCollider2
};

struct yColliderNode elevYCollider =
{
    25,
    0,
    12,
    &elevYCollider1
};

struct xColliderNode elevXCollider1 =
{
    30,
    24,
    10,
    0
};

struct xColliderNode elevXCollider =
{
    10,
    24,
    10,
    &elevXCollider1
};

//Dash component
struct xColliderNode dashXCollider1 =
{
    29,
    25,
    16,
    0
};

struct xColliderNode dashXCollider =
{
    16,
    25,
    16,
    &dashXCollider1
};

struct yColliderNode dashYCollider =
{
    16,
    16,
    29,
    0
};

/*============================================================================================================*/

/*=============================================== ENTITIES ===================================================*/

struct StageEntity coin = {
    Coin,
    spriteCoin,
    len(spriteCoin),
    collectible,
    0,
    0,
    5,
    5,
    1
};

struct StageEntity heart = {
    Heart,
    spriteHeart,
    len(spriteHeart),
    collectible,
    0,
    0,
    5,
    5,
    1
};

struct StageEntity endFlag = {
    EndFlag,
    spriteFlag,
    len(spriteFlag),
    ending,
    0,
    0,
    11,
    12,
    1
};

struct StageEntity spike = {
    Spike,
    spriteSpike,
    len(spriteSpike),
    obstacle,
    0,
    0,
    8,
    7,
    1
};

struct StageEntity invSpike = {
    InvSpike,
    spriteInvSpike,
    len(spriteInvSpike),
    obstacle,
    0,
    0,
    8,
    7,
    1
};

/*=================================================================================================================*/

/*=============================================== ENTITY GROUPS ===================================================*/

struct sparseNode coinGroupPos[] = 
{
    {12,15},{20,10},{28,15}
};
struct ComponentEntityGroup coinGroup = 
{
    Coin,
    3,
    coinGroupPos
};



struct sparseNode heartGroupPos[] = 
{
    {16,8}
};
struct ComponentEntityGroup heartGroup = 
{
    Heart,
    1,
    heartGroupPos
};



struct sparseNode flagGroupPos[] = 
{
    {16,25}
};
struct ComponentEntityGroup flagGroup = 
{
    EndFlag,
    1,
    flagGroupPos
};




struct sparseNode dashSpikeGroupPos[] =
{
    {8 ,26}, {15 ,26}, {22, 26}
};
struct ComponentEntityGroup dashSpikeGroup = 
{
    Spike,
    2,
    dashSpikeGroupPos
};




struct sparseNode dashInvSpikeGroupPos[] =
{
    {8 ,5}, {15 ,5}, {22,  5}
};
struct ComponentEntityGroup dashInvSpikeGroup = 
{
    InvSpike,
    3,
    dashInvSpikeGroupPos
};



struct sparseNode spikeGroupPos[] = 
{
    {16,25}
};
struct ComponentEntityGroup spikeGroup = 
{
    Spike,
    1,
    spikeGroupPos
};



struct sparseNode spikeGroupPos2[] = 
{
    {16,13}
};
struct ComponentEntityGroup spikeGroup2 = 
{
    Spike,
    1,
    spikeGroupPos2
};

/*====================================================================================================================*/

/*=============================================== STAGE COMPONENTS ===================================================*/

struct StageComponent flatComp = {
    flatSpr,            //Component Sprite
    len(flatSpr),       //Sprite size
    3,                  //xSpawn
    10,                  //ySpawn
    0,                  //xCollider
    &flatYCollider,      //yCollider
    1,                    //numEntities
    {&spikeGroup},          //entities
};

struct StageComponent elevflatComp = {
    elevflatSpr,          
    len(elevflatSpr),       
    3,                
    10,               
    0,                  
    &elevflatYCollider,    
    1,                   
    0,     
};

struct StageComponent stairComp =
{
    stairSpr,            
    len(stairSpr),    
    3,             
    10,              
    &stairXCollider, 
    &step1YCollider,   
    0,                    
    0,         
};

struct StageComponent dashComp =
{
    dashSpr,
    len(dashSpr),
    3,
    10,
    &dashXCollider,
    &dashYCollider,
    1,
    {&dashInvSpikeGroup}
};

struct StageComponent holeComp =
{
    holeSpr,            
    len(holeSpr),       
    3,                  
    24,                  
    0,                  
    &holeYCollider1,
    1,
    {&coinGroup}
};

struct StageComponent elevComp =
{
    elevSpr,           
    len(elevSpr),     
    15,               
    9,              
    &elevXCollider,     
    &elevYCollider,
    1,
    {&heartGroup}
};

struct StageComponent endComp =
{
    endSpr,          
    len(endSpr),     
    3,                
    25,                       
    0,          
    &flatYCollider,
    1,
    {&flagGroup} 
};

/*==========================================================================================================*/

/*================================================ STAGES ==================================================*/

#define ENTITIES_PER_COMP 4

struct StageEntity stageEntities1[ENTITIES_PER_COMP*8];
struct Stage stg1 =
{
    32*8,
    0,
    stageEntities1,
    0,
    8,
    {&flatComp, &flatComp, &holeComp, &flatComp,
     &holeComp, &stairComp, &elevComp, &endComp}
};

struct StageEntity stageEntities2[ENTITIES_PER_COMP*12];
struct Stage stg2 =
{
    32*12,
    0,
    stageEntities2,
    0,
    12,
    {&flatComp, &elevComp, &holeComp, &stairComp, &elevComp, 
    &flatComp, &stairComp, &elevflatComp, &elevComp, &flatComp, 
    &holeComp, &endComp}
};

struct StageEntity stageEntities3[ENTITIES_PER_COMP*12];
struct Stage stg3 =
{
    32*12,
    0,
    stageEntities3,
    0,
    12,
    {&flatComp, &flatComp, &holeComp, &holeComp, &elevComp, 
    &holeComp, &stairComp, &elevflatComp, &holeComp, &elevComp, 
    &holeComp, &endComp}
};

struct StageEntity stageEntities4[ENTITIES_PER_COMP*12];
struct Stage stg4 =
{
    32*12,
    0,
    stageEntities4,
    0,
    12,
    {&flatComp, &stairComp, &elevflatComp, &holeComp, 
    &flatComp, &holeComp,  &elevflatComp, &holeComp, 
    &elevComp, &stairComp, &dashComp, &endComp}
};

struct StageEntity stageEntities5[ENTITIES_PER_COMP*16];
struct Stage stg5 =
{
    32*16,
    0,
    stageEntities5,
    0,
    16,
    {&flatComp, &holeComp, &stairComp, &dashComp, 
    &flatComp, &stairComp,  &elevflatComp, &holeComp, 
    &holeComp, &holeComp, &holeComp, &elevflatComp, 
    &dashComp, &flatComp, &holeComp, &endComp}
};

/* ============= STAGE LIST ==============*/

int numStages = 5;
struct Stage* stageList[] = 
{
    &stg1,
    &stg2,
    &stg3,
    &stg4,
    &stg5
};

/*========================================*/

/* ======= Forward functions ========*/

struct StageEntity getEntity(enum Entities entity); //Gets  the right kind of entity object based on enum flag
struct Stage* getStage(int i); //gets a specific stage
void initStageEntities(struct Stage* s); //converts from component entities to global individual entities
int getNumStages();  //gets total number of stages
int getActiveStgComponent(struct Player* p, struct Stage* s);//get component player is on
void resetEntities(struct Stage* s); //resets all entities to be active

/* ================================= */

/*============== Functions ===========*/

//Gets specific entity object based on enum flag
struct StageEntity getEntity(enum Entities entity)
{
    switch(entity)
    {
        case Spike:
            return spike;
            break;
        case InvSpike:
            return invSpike;
            break;
        case Heart:
            return heart;
            break;
        case Coin:
            return coin;
            break;
        case EndFlag:
            return endFlag;
    }
    return spike;
}

//Converts entities to global individual entities from component reference
void initStageEntities(struct Stage* s)
{
    int i, j, k, l;

    l = 0;
    s->numSEntities = 0;

    for (i = 0; i < s->numComps; i++) //Loops through components
    {
        int compOffset = i*(s->xMax/s->numComps);
        
        for (j = 0; j < s->stageComponents[i]->numEntities; j++) //Loops through entity groups within components
        {
            struct ComponentEntityGroup* eg = s->stageComponents[i]->entityGroups[j];
            
            for (k = 0; k < eg->numCopies; k++) //Loops through entities within entity groups
            {
                s->stageEntities[l] = getEntity(eg->e);
                s->stageEntities[l].x = eg->pos[k].x + compOffset;
                s->stageEntities[l].y = eg->pos[k].y;
                s->stageEntities[l].isActive = 1;
                l++;
                s->numSEntities++;
            }
        }
    }
}

//Gets component player is on
int getActiveStgComponent(struct Player* p, struct Stage* s)
{
	int compLen = s->xMax / s->numComps;
	return p->x / compLen;
}

//Gets total number of stages
int getNumStages()
{
    return numStages;
}

//Gets ith stage
struct Stage* getStage(int i)
{
    return stageList[i % numStages];
}

//Resets entities to active
void resetEntities(struct Stage* s)
{
    int i;
    for (i = 0; i < s->numSEntities; i++)
    {
        s->stageEntities[i].isActive = 1;
    }
}