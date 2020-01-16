#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "structs.h"

void debugPrint(int line, char *s, char* textbuffer); //Printes a debug message
char * itoaconv(int num); //converts integers to strings
void renderPlayer(struct Player* p, uint8_t * displayBuffer, struct Camera* c);  //Renders the player
void renderStage(struct Stage* s, struct Player* p, struct Camera* c, uint8_t * displayBuffer); //Renders the whole stage (calls stagecomponent and entity)
void renderSelector(struct sparseNode* selector, int selLen, struct sparseNode* choicePos, uint8_t * displayBuffer); //Renders the main menu selector
void renderText(char * textBuffer, uint8_t * displayBuffer, int lines, int offset); //Renders text? Obsolete?
void renderUI(int stageNum, int score, int hearts, int lives, uint8_t * displayBuffer); //Renders the UI

#endif