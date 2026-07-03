#ifndef LIB_ENTITY_H
#define LIB_ENTITY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "sprite.h"

typedef struct {
    Sprite *sprite;
    Vector2 pos;
    Vector2 scale;
    decimal angle;
} Entity;

/*Position Handling*/
void add_pos(Entity *entity, Vector2 add);
void sub_pos(Entity *entity, Vector2 sub);

/*Angle Handling*/
void add_angle(Entity *entity, decimal add);
void sub_angle(Entity *entity, decimal sub);

/*Other Handling*/
void draw_entity(Entity* entity, decimal dt, SDL_Renderer *ren);
bool check_entities_collision(Entity *a, Entity *b, Vector2 col_scale_a, Vector2 col_scale_b);

#endif /* LIB_ENTITY_H */