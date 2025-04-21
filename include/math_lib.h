#pragma once
#define PI 3.14159
struct mat4
{
    float data [16];
};

struct vec3 
{
    float data [3];
};

mat4 create_matrix_transform(vec3 translation);
mat4 create_z_rotate(float angle);
mat4 create_y_rotate(float angle);
mat4 create_x_rotate(float angle);