#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

#define len(sprite) sizeof(sprite) / sizeof(sprite[0])

struct sparseNode
{
	int x;
	int8_t y;
};

struct sprite
{
	int16_t xpos;
	int8_t ypos;
	struct sparseNode* spr;
	uint16_t sprSize;
	uint8_t height;
	uint8_t width;
};

enum PlayerState{standing, jumping, dashing, dead, respawning};
enum Facing{left, right};

struct Player
{
    enum PlayerState state;
    int8_t hitPoints;
    int8_t lives;
	int x;
	int8_t y;
    int8_t xVel;
    int8_t yVel;
	int xPrev;
	int8_t yPrev;
	struct sparseNode gravityFraction;
	struct sparseNode* spr;
	uint16_t sprSize;
	struct sparseNode* sprJump;
	uint8_t sprJumpSize;
	struct sparseNode* sprAir;
	uint8_t sprAirSize;	
	struct sparseNode* sprFall;
	uint8_t sprFallSize;	
	struct sparseNode* sprDash;
	uint8_t sprDashSize;
	uint8_t height;
	uint8_t width;
	int score;
	uint8_t damageTimeout;
	enum Facing facing;
	uint8_t dashStage;
};

struct Camera{
    int x;
    int y;
    int xLeft;
    int xRight;
    int width;
    int height;
};


enum EntityCat{collectible, enemy, obstacle, ending};
enum Entities{Spike, InvSpike, Heart, Coin, EndFlag};

struct StageEntity{
    enum Entities e;
    struct sparseNode* spr;
    uint8_t sprSize;
    enum EntityCat type;
    int x;
    int8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t isActive;
};

struct ComponentEntityGroup{
    enum Entities e;
    int numCopies;
    struct sparseNode* pos;
};

struct xColliderNode
{
    int xKey;
    int8_t yGreater;
    int8_t ySmaller;
    struct xColliderNode *next;
};

struct yColliderNode
{
    int8_t yKey;
    int xLeft;
    int xRight;
    struct yColliderNode *next;
};

struct Stage{
    int xMax;
    int numSEntities;
    struct StageEntity* stageEntities;
    int stageCompleted;
    int numComps;
    struct StageComponent* stageComponents[];
};

struct StageComponent{
    struct sparseNode* spr;
    int sprSize;
    int xSpawn;
    int ySpawn;
    struct xColliderNode* xColliders;
    struct yColliderNode* yColliders;
    int numEntities;
    struct ComponentEntityGroup* entityGroups[];
};


#endif