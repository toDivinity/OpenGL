#include "DivineMath.h"
namespace DivineMath
{
    float radians(float degrees) {
        return float(degrees * (PI / 180.0f));
    }
    mat4 create_translation_matrix(vec3 translation_vector)
    {
        mat4 identity_matrix = 
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

    mat4 create_z_rotation_matrix(float rotation_angle_degrees)
    {
        float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
        
        mat4 rotation_matrix = 
        {
            cosf(angle_radians),  sinf(angle_radians), 0.0f, 0.0f, 
            -sinf(angle_radians), cosf(angle_radians), 0.0f, 0.0f, 
            0.0f,                 0.0f,                1.0f, 0.0f, 
            0.0f,                 0.0f,                0.0f, 1.0f
        };

        return rotation_matrix;
    }

    mat4 create_y_rotation_matrix(float rotation_angle_degrees)
    {
        float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
        
        mat4 rotation_matrix = 
        {
            cosf(angle_radians), 0.0f, -sinf(angle_radians), 0.0f,
            0.0f,                1.0f, 0.0f,                 0.0f, 
            sinf(angle_radians), 0.0f, cosf(angle_radians),  0.0f, 
            0.0f,                0.0f, 0.0f,                 1.0f
        };

        return rotation_matrix;
    }

    mat4 create_x_rotation_matrix(float rotation_angle_degrees)
    {
        float angle_radians = rotation_angle_degrees * (float)PI / 180.0f;
        
        mat4 rotation_matrix = 
        {
            1.0f, 0.0f,                 0.0f,                 0.0f, 
            0.0f, cosf(angle_radians),  sinf(angle_radians),  0.0f, 
            0.0f, -sinf(angle_radians), cosf(angle_radians),  0.0f, 
            0.0f, 0.0f,                 0.0f,                 1.0f
        };

        return rotation_matrix;
    }

    mat4 create_rotation_matrix(vec3 rotation)
    {
        return (DivineMath::create_x_rotation_matrix(rotation.x))
        * (DivineMath::create_y_rotation_matrix(rotation.y))
        * (DivineMath::create_z_rotation_matrix(rotation.z));
    }


    mat4 create_scale_matrix(vec3 scale_vector)
    {
        mat4 scale_matrix = 
        {
            scale_vector.x, 0.0f, 0.0f, 0.0f, 
            0.0f, scale_vector.y, 0.0f, 0.0f, 
            0.0f, 0.0f, scale_vector.z, 0.0f, 
            0.0f, 0.0f, 0.0f, 1.0f
        };
        
        return scale_matrix;
    }

    mat4 create_projection_matrix(float fov, float aspect, float zNear, float zFar)
    {
        float const tanHalfFov = tan(fov / 2.0f);

        mat4 projection_matrix = 
        {
            1.0f / (aspect * tanHalfFov), 0.0f,             0.0f,                          0.0f,
            0.0f,                        1.0f / tanHalfFov, 0.0f,                          0.0f,
            0.0f,                        0.0f,              -(zFar + zNear) / (zFar - zNear), -1.0f,
            0.0f,                        0.0f,              -(2.0f * zFar * zNear) / (zFar - zNear), 0.0f
        };
        
        return projection_matrix;
    }

    vec3 normalize(const vec3& v) 
    {
        float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length > 0.0f) {
            return {v.x / length, v.y / length, v.z / length};
        }
        return {0.0f, 0.0f, 0.0f};
    }
    vec3 vec3::normalize()
    {
        float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        this->x /= length;
        this->y /= length;
        this->z /= length;
        return  vec3(x,y,z);
    }

    vec3 cross(const vec3& a, const vec3& b) 
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    
    vec2 readVec2(std::vector<std::string> words)
    {
        return vec2(std::stof(words[1]), std::stof(words[2]));
    }
    vec3 readVec3(std::vector<std::string> words)
    {
        return vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
    }
}