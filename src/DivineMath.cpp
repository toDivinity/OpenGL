#include "DivineMath.h"

DivineMath::mat4 DivineMath::create_translation_matrix(vec3 translation_vector)
{
    DivineMath::mat4 identity_matrix = 
    {
        1.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    identity_matrix.data[12] = translation_vector.x;
    identity_matrix.data[13] = translation_vector.y;
    identity_matrix.data[14] = translation_vector.z;

    return identity_matrix;
}

DivineMath::mat4 DivineMath::create_z_rotation_matrix(float rotation_angle_degrees)
{
    float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
    
    DivineMath::mat4 rotation_matrix = 
    {
        cosf(angle_radians),  sinf(angle_radians), 0.0f, 0.0f, 
        -sinf(angle_radians), cosf(angle_radians), 0.0f, 0.0f, 
        0.0f,                 0.0f,                1.0f, 0.0f, 
        0.0f,                 0.0f,                0.0f, 1.0f
    };

    return rotation_matrix;
}

DivineMath::mat4 DivineMath::create_y_rotation_matrix(float rotation_angle_degrees)
{
    float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
    
    DivineMath::mat4 rotation_matrix = 
    {
        cosf(angle_radians), 0.0f, -sinf(angle_radians), 0.0f,
        0.0f,                1.0f, 0.0f,                 0.0f, 
        sinf(angle_radians), 0.0f, cosf(angle_radians),  0.0f, 
        0.0f,                0.0f, 0.0f,                 1.0f
    };

    return rotation_matrix;
}

DivineMath::mat4 DivineMath::create_x_rotation_matrix(float rotation_angle_degrees)
{
    float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
    
    DivineMath::mat4 rotation_matrix = 
    {
        1.0f, 0.0f,                 0.0f,                 0.0f, 
        0.0f, cosf(angle_radians),  sinf(angle_radians),  0.0f, 
        0.0f, -sinf(angle_radians), cosf(angle_radians),  0.0f, 
        0.0f, 0.0f,                 0.0f,                 1.0f
    };

    return rotation_matrix;
}


DivineMath::mat4 DivineMath::create_scale_matrix(vec3 scale_vector)
{
    DivineMath::mat4 scale_matrix = 
    {
        scale_vector.x, 0.0f, 0.0f, 0.0f, 
        0.0f, scale_vector.y, 0.0f, 0.0f, 
        0.0f, 0.0f, scale_vector.z, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return scale_matrix;
}

DivineMath::mat4 DivineMath::create_projection_matrix(float fov, float aspect, float zNear, float zFar)
{
    float const tanHalfFov = tan(fov / 2.0f);

    DivineMath::mat4 projection_matrix = 
    {
        1.0f / (aspect * tanHalfFov), 0.0f,             0.0f,                          0.0f,
        0.0f,                        1.0f / tanHalfFov, 0.0f,                          0.0f,
        0.0f,                        0.0f,              -(zFar + zNear) / (zFar - zNear), -1.0f,
        0.0f,                        0.0f,              -(2.0f * zFar * zNear) / (zFar - zNear), 0.0f
    };
    
    return projection_matrix;
}