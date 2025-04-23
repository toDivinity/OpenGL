#pragma once

#include "DivineConfig.h"
#include <cmath>

#define PI 3.14159

namespace DivineMath
{
    struct vec2
    {
        float x, y;

        vec2(float x = 0.0f, float y = 0.0f) 
            : x(x), y(y) {}
    };

    struct vec3
    {
        float x, y, z;

        vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) 
            : x(x), y(y), z(z) {}
    };

    struct vec4
    {
        float x, y, z, w;
        
        vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) 
            : x(x), y(y), z(z), w(w) {}
            
        explicit vec4(const vec3& v, float w = 1.0f)
            : x(v.x), y(v.y), z(v.z), w(w) {}
    };
    
    struct mat4
    {
        float data [16];
    };

    static mat4 operator*(const mat4& left, const mat4& right)
    {
        mat4 result = {0};

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                for (int k = 0; k < 4; ++k) {
                    result.data[row * 4 + col] += 
                        left.data[row * 4 + k] * 
                        right.data[k * 4 + col];
                }
            }
        }

        return result;
    }

    static mat4 operator+(const mat4& left, const mat4& right)
    {
        mat4 result = {0};

        for(int i=0; i<16; i++)
        {
            result.data[i]=left.data[i]+right.data[i];
        }

        return result;
    }

    

    mat4 create_translation_matrix(vec3 translation_vector);
    mat4 create_z_rotation_matrix(float rotation_angle_degrees);
    mat4 create_y_rotation_matrix(float rotation_angle_degrees);
    mat4 create_x_rotation_matrix(float rotation_angle_degrees);
    mat4 create_scale_matrix(vec3 scale_vector);
}