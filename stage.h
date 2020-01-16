#ifndef STAGE_H
#define STAGE_H

#include <stdint.h>
#include "structs.h"

struct Stage* getStage(int i);
void initStageEntities(struct Stage* s);
int getNumStages();
int getActiveStgComponent(struct Player* p, struct Stage* s);
void resetEntities(struct Stage* s);

#endif