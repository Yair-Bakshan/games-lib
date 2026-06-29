#ifndef LIB_VECTOR_H
#define LIB_VECTOR_H

typedef float decimal;

typedef struct {
    decimal x, y;
} Vector2;

Vector2 add_vector2(Vector2 dst, Vector2 src);
Vector2 sub_vector2(Vector2 dst, Vector2 src);
Vector2 get_center(const Vector2 *src);

#endif /* LIB_VECTOR_H */