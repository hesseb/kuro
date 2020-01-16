//#define SPRITES_H

#include <stdint.h>
#include "structs.h"
#include "stage.h"

/*Defines*/
#define NO_COLLISION -100
/*========*/

/*======== Globals ========= */

struct sparseNode sprChr[] =
{                
					 {2,-6}, {3,-6}, {4,-6}, {5,-6}, {6,-6},
	         {1,-5}, {2,-5}, {3,-5},                         {7,-5},
	 {0,-4}, {1,-4}, {2,-4},         {4,-4},         {6,-4}, 
	 {0,-3},         {2,-3},
	                 {2,-2}, {3,-2},                 {6,-2},
	         {1,-1},         {3,-1}, {4,-1}, {5,-1},         {7,-1},
	                 {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}
};

struct sparseNode sprChrDash[] =
{                
							
		{0, -7},{1,-7},				 	 
			 	
				   			    {3,-5}, {4,-5}, 
{-1,-4},		{1,-4}, {2,-4}, {3,-4}, {4,-4}, {5,-4},
								{3,-3}, {4,-3}, 
			 		 
		{0, -1},{1,-1}
};

//Not aligned
struct sparseNode sprChrJump[] =
{                
					 {2,-6}, {3,-6}, {4,-6}, {5,-6}, {6,-6},
	         {1,-4}, {2,-5}, {3,-5},                         {7,-5},
	 {0,-3}, {1,-3}, {2,-4},         {4,-4},         {6,-4}, 
	 {0,-2},         {2,-3},
	                 {2,-2}, {3,-2},              
	         {1,-1},         {3,-1}, {4,-1}, {5,-2},         {7,-2},
	                 {2, 0}, {3, 0}, {4, 0}, {5,-1}, {6, -1}
};

//Not aligned
struct sparseNode sprChrAir[] =
{                
					 {2,-6}, {3,-6}, {4,-6}, {5,-6}, {6,-6},
	         {1,-6}, {2,-5}, {3,-5},                         {7,-5},
	 {0,-6}, {1,-5}, {2,-4},         {4,-4},         {6,-4}, 
	 {-1,-6},         {2,-3},
	                 {2,-2}, {3,-2},              	{6,-2},
	         {1,-1},         {3,-1}, {4,-1}, {5,-1},         {7,-1},
	                 {2, 0}, {3, 0}, {4, 0}, {5,0}, {6, 0}
};

//Not aligned
struct sparseNode sprChrFall[] =
{                
					 {2,-6}, {3,-6}, {4,-6}, {5,-6}, {6,-6},
	         {1,-6}, {2,-5}, {3,-5},                         {7,-5},
	 {0,-7}, {1,-5}, {2,-4},         {4,-4},         {6,-4}, 
	 {0,-6},         {2,-3},
	                 {2,-2}, {3,-2},                 {6,-1},
	         {1,-1},         {3,-1}, {4,-1}, {5,0},         {7,0},
	                 {2, 0}, {3, 0}, {4, 0}, {5,1}, {6, 1}
};

struct Player playerC =
{
    standing,      //state
	3,             //hitPoints
	2,            //lives
    3,             //xPos
    24,             //yPos
    0,             //xVel
    0,             //yVel
	0,             //xPosPrev
	0,             //yPosPrev
	{0, 0},        //gravityFraction
	sprChr,        //spr
	len(sprChr),   //sprSize
	sprChrJump,
	len(sprChrJump),
	sprChrAir,
	len(sprChrAir),
	sprChrFall,
	len(sprChrFall),
	sprChrDash,
	len(sprChrDash),
	7,             //sprHeight
	8,             //sprWidth
	0,			   //score
	right,
};

/* ======================================== */

/*======= Forward functions =============== */

void applyGravity(struct Player* p, struct Stage* s);        //applies gravity to PC
int8_t collisionHelper(int p1, int p2, int c1, int c2);	     //fins collisions between two line segments
int detectFloor(struct Player* p, struct Stage* s);			 //Detects if there is floor beneath the PC and changes player state to standing if yes (calls standingOn)
int entityCollision(struct Player* p, struct Stage* s);      //Detects box collisions with entities such as coins, spikes, hearts
struct sparseNode findCollision(struct Player* p, struct Stage* s); //General collision finder for geometry
int8_t findXCollision(struct Player* p, int colliderOffset, struct xColliderNode* node); //Collision finder when moving in x-direction
int8_t findYCollision(struct Player* p, int colliderOffset, struct yColliderNode* node); //Collision finder when moving in y-direction
struct Player* getPlayer();    //returns a reference of the player struct
int isBetween(int a, int x1, int x2); //1 if a is between x1 and x2
void jump(struct Player* p);  //applies the jump logic
void killplane(struct Player* p, struct Stage* s); //What happens when you fall below the map. (as in when you fall in a hole)
int8_t standingOn(struct Player* p, struct Stage* s);          //The function that actually finds the flood the PC is standing on, if any. Loops through components
int8_t standingOnAux(struct Player* p, int colliderOffset, struct yColliderNode* node);   //checks for floors on a specific component
void takeDamage(struct Player* p, struct Stage* s);  //Take damage if falling in hole or touching spike or whatever. If 0 hitpoints, lose a life, if 0 lives revive
void updateChar(struct Player* p, struct Stage* s);  //Calls updatePos and applyGravity
void updatePos(struct Player* p, struct Stage* s);   //Updates game physics and char position while taking collisions into consideration

/*==========================================*/

/* ======= Functions ======================*/
//Returns player reference
struct Player* getPlayer()
{
    return &playerC;
}

//Applies gravity to player
//Uses a gravity fraction system to circumvent integer only
// and small screen. So will only change yVel every few frames.
//The x and y are just two different granularity counters
void applyGravity(struct Player* p, struct Stage* s)
{
	if (detectFloor(p, s) == 0)
	{
		if (p->gravityFraction.x >= 1){
			if (p->gravityFraction.y == 0){
				p->gravityFraction.x = 0;
				p->yVel += 1;
			}
			else p->gravityFraction.y--;
		}
		else p->gravityFraction.x++;
	}
}

//If there is floor under player, set state to standing and return said floor
int detectFloor(struct Player* p, struct Stage* s)
{
	int isOnFloor = standingOn(p, s);
    if (isOnFloor)
	{
		p->state = standing;
		return isOnFloor;
	}
	return isOnFloor;
}

//Jump. 
void jump(struct Player* p)
{
    p->yVel -= 3;
	p->gravityFraction.x = 0;
	p->gravityFraction.y = 0;
    p->state = jumping;
}

//The meat of the update process.
//Checks all kinds of collisions, updates states, positions
// velocities and checks for killplanes and if player is within bounds.
void updatePos(struct Player* p, struct Stage* s)
{
	//Saves previous position in case of collision
	p->xPrev = p->x;
	p->yPrev = p->y;

	//Increments position with current velocity
    p->x += p->xVel;
    p->y += p->yVel;
    


	//Finds collisions in x and y directions and applies
	//appropriate kickback and reposition
	struct sparseNode collision = findCollision(p, s);

	if (collision.y != NO_COLLISION)
	{
		int sign;
		if (p->yVel > 0) sign = -1;
		else sign = 1;
		p->y = collision.y + sign;
		p->yVel = - (p->yVel /4);
		p->state = standing;
	}

	if (collision.x != NO_COLLISION)
	{
		p->x = p->xPrev;
		/*int sign = 1;
		if (p->facing == left) sign = -1;
		p->xVel = sign*8;*/
	}

	//Detect floor to change state to standing
	detectFloor(p, s);
	//Detects collisions with entities and resolves their effect
	entityCollision(p, s);

	//Decrements velocity over time	
	int xVel = p->xVel;
	if ((xVel == 1) || (xVel == -1)) xVel = 0;
	else if (xVel < 0) xVel++;
	else if (xVel > 0) xVel--;
	p->xVel = xVel;

	//Checks stage boundaries
	if (p->facing == left)
	{
		if (p->x - p->width <= 0) p->x = p->width;
		if (p->x >= s->xMax) p->x = s->xMax;
	}
	else if (p->facing == right)
	{
		if (p->x <= 0) p->x = 0;
		if ((p->x + p->width) >= s->xMax) p->x = s->xMax - p->width;
	}

    if (p->y >= 31+p->height +10) killplane(p, s);
	if ((p->y - p->height) <= 0) p->y = p->height;
}

//Function called from main. Updates gravity and position
void updateChar(struct Player* p, struct Stage* s)
{
	applyGravity(p, s);
    updatePos(p, s);
}

//Cycles through the active component, the previous and the next to find collision
struct sparseNode findCollision(struct Player* p, struct Stage* s)
{
	int activeComp = getActiveStgComponent(p, s);
	int i, xCollision, yCollision;

	struct sparseNode collision = {NO_COLLISION, NO_COLLISION};

	for (i = (activeComp)-1; i < (activeComp + 2); i++)
	{
		if (i < 0) continue;
		if (i >= s->numComps) continue;
		
		xCollision = findXCollision(p, i*(s->xMax / s->numComps), s->stageComponents[i]->xColliders);
		yCollision = findYCollision(p, i*(s->xMax / s->numComps), s->stageComponents[i]->yColliders);
		
		if (xCollision != NO_COLLISION) collision.x = xCollision;
		if (yCollision != NO_COLLISION) collision.y = yCollision;
	}

	return collision;
}

//Recursive function the goes through Y colliders in a component to find collisions
int8_t findYCollision(struct Player* p, int colliderOffset, struct yColliderNode* node)
{
	if (!node) return NO_COLLISION;

	int sign = 1;
	if (p->facing == left) sign = -1;
	else if (p->facing == right) sign = 1;
	
	if (isBetween(node->yKey, p->y, p->y - p->height)) //if the collider key (in this case the y level) is between the char coords, we check x as well
	{
		if(collisionHelper(p->x, p->x + sign*p->width, node->xLeft + colliderOffset, node->xRight + colliderOffset)) return node->yKey;
	}
	return findYCollision(p, colliderOffset, node->next);	
}

//Recursive function the goes through X colliders in a component to find collisions
int8_t findXCollision(struct Player* p, int colliderOffset, struct xColliderNode* node)
{
	if (!node) return NO_COLLISION;
		
	int sign = 1;
	if (p->facing == left) sign = -1;
	else if (p->facing == right) sign = 1;

	if (isBetween(node->xKey + colliderOffset, p->x, p->x + sign*p->width))
	{
		if(collisionHelper(p->y, p->y - p->height, node->yGreater, node->ySmaller)) return node->xKey;
	}
	return findXCollision(p, colliderOffset, node->next);	
}

//Checks if two line parallell line segments collide
int8_t collisionHelper(int p1, int p2, int c1, int c2)
{
	if (isBetween(p1, c1, c2)) return 1;
	if (isBetween(p2, c1, c2)) return 1;
	if (isBetween(c1, p1, p2) && isBetween(c2, p1, p2)) return 1;
	return 0;
}

//Checks active component, previous and next if there is floor beneath PC
int8_t standingOn(struct Player* p, struct Stage* s)
{
	int activeComp = getActiveStgComponent(p, s);
	int i;

	for (i = (activeComp - 1); i < (activeComp + 2); i++)
	{	
		if (i < 0) continue;
		if (i >= s->numComps) continue;

		if (standingOnAux(p, i*(s->xMax / s->numComps), s->stageComponents[i]->yColliders)) return 1;
	}
	return 0;
}

//Checks a components colliders for floors
int8_t standingOnAux(struct Player* p, int colliderOffset, struct yColliderNode* node)
{
	if (node == 0) return 0;

	int pFloor = p->y + 1;

	int sign = 1;
	if (p->facing == left) sign = -1;
	else if (p->facing == right) sign = 1;

	if (pFloor == node->yKey)
	{
		int pLeft = p->x;
		int pRight = p->x + sign*p->width;
		int cLeft = node->xLeft + colliderOffset;
		int cRight = node->xRight + colliderOffset;
	
		if (isBetween(pLeft, cLeft, cRight)) return 1;
		if (isBetween(pRight, cLeft, cRight)) return 1;
		if (isBetween(cLeft, pLeft, pRight) && isBetween(cRight, pLeft, pRight)) return 1;
	}

	return standingOnAux(p, colliderOffset, node->next);
}

//Checks if a is between x1 and x2
int isBetween(int a, int x1, int x2)
{
	int smaller, larger;

	if (x1 > x2)
	{
		larger = x1;
		smaller = x2;
	}
	else
	{
		smaller = x1;
		larger = x2;
	}

	if ((a == x1) || (a == x2)) return 1;
	if ((a > smaller) && (a < larger)) return 1;
	return 0;
}

//What happens when you fall in a hole.
void killplane(struct Player* p, struct Stage* s)
{
	if (p->hitPoints > 1) p->hitPoints--;
	else
	{
		p->hitPoints = 3;
		p->lives--;
	}
	p->state = respawning;
}

//Damage routine
void takeDamage(struct Player* p, struct Stage* s)
{
	if (p->damageTimeout <= 60) return;
	p->damageTimeout = 0;
	if (p->hitPoints > 1) p->hitPoints--;
	else
	{
		p->hitPoints = 3;
		p->lives--;
		p->state = respawning;
	}
}


//Finds box collisions with entities throughout the stage and executes corresponding behaviour
int entityCollision(struct Player* p, struct Stage* s)
{
	int i;

	int sign = 1;
	//Determines left and right based on facing
	int playerLeft, playerRight;
	if (p->facing == right){
		sign = 1;
		playerLeft = p->x + 1;
		playerRight = p->x + p->width;
	}
	else if (p->facing == left)
	{
		sign = -1;
		playerLeft = p->x - p->width;
		playerRight = p->x - 1;
	}


	//Loops through all entitites to find collisions
	for (i = 0; i < s->numSEntities; i++)
	{
		struct StageEntity* e = &s->stageEntities[i];
		if (!e->isActive) continue;

		if ((playerLeft < e->x + e->width-1) &&
			(playerRight > e->x+1) &&
			(p->y < e->y + e->height-1) &&
			(p->y + p->height > e->y))
		{
			if (e->type == collectible)
			{
				if (e->e == Heart)
				{
					if (p->hitPoints < 3){
						p->score += 500;
						e->isActive = 0;
						p->hitPoints = (p->hitPoints + 1) % 4;
					}	
				}
				if (e->e == Coin)
				{
					p->score += 300;
					e->isActive = 0;
				}
			}
			if (e->type == obstacle)
			{
				if(e->e == Spike)
				{
					int sign = -1;
					if (p->xVel < 0) sign = 1; 
					p->xVel = 3*sign;
					p->yVel = -4;
					takeDamage(p, s);
				}
				if(e->e == InvSpike)
				{
					int sign = -1;
					if (p->xVel < 0) sign = 1; 
					p->xVel = 3*sign;
					p->yVel = 4;
					takeDamage(p, s);
				}
			}
			if (e->type == ending)
			{
				if(e->e == EndFlag){
					s->stageCompleted = 1;
				}
			}
		}
	}
	return 0;
}
