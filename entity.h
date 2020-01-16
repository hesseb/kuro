#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include "structs.h"

struct Player* getPlayer();
void jump(struct Player* p);
void updateChar(struct Player* p, struct Stage* stg);

#endif