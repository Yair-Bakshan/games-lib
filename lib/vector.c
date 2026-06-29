#include "vector.h"

Vector2 add_vector2(Vector2 dst, Vector2 src) {
    dst.x += src.x;
    dst.y += src.y;
    return dst;
}

Vector2 sub_vector2(Vector2 dst, Vector2 src) {
    dst.x -= src.x;
    dst.y -= src.y;
    return dst;
}

Vector2 get_center(const Vector2 *src){
    Vector2 center = {src->x / 2.0f, src->y / 2.0f};
    return center;
}