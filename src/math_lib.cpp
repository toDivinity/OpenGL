#include "math_lib.h"
#include <cmath>

mat4 create_matrix_transform(vec3 translation)
{
    mat4 matrix = 
    {
        1.0f, 
        0.0f, 
        0.0f, 
        0.0f, 
        
        0.0f, 
        1.0f, 
        0.0f, 
        0.0f, 
        
        0.0f, 
        0.0f, 
        1.0f, 
        0.0f, 
        
        0.0f, 
        0.0f, 
        0.0f, 
        1.0f
    };
    matrix.data[12]=translation.data[0];
    matrix.data[13]=translation.data[1];
    matrix.data[14]=translation.data[2];

    return matrix;
}

mat4 create_z_rotate(float angle)
{
    angle = angle*(float)PI/180;
    mat4 matrix = 
    {
        cosf(angle), 
        sinf(angle), 
        0.0f, 
        0.0f, 
        
        -sinf(angle), 
        cosf(angle), 
        0.0f, 
        0.0f, 
        
        0.0f, 
        0.0f, 
        1.0f, 
        0.0f, 
        
        0.0f, 
        0.0f, 
        0.0f, 
        1.0f
    };

    return matrix;
}

mat4 create_y_rotate(float angle)
{
    
    angle = angle*(float)PI/180;
    mat4 matrix = 
    {
        cosf(angle),    
        0.0f, 
        sinf(angle),  
        0.0f,
        
        0.0f,         
        1.0f, 
        0.0f,         
        0.0f, 
        
        -sinf(angle), 
        0.0f, 
        cosf(angle),  
        0.0f, 
        
        0.0f,         
        0.0f, 
        0.0f,         
        1.0f
    };

    return matrix;
}

mat4 create_x_rotate(float angle)
{
    angle = angle*(float)PI/180;
    mat4 matrix = 
    {
        1.0f,   
        0.0f,           
        0.0f,           
        0.0f, 
        
        0.0f, 
        cosf(angle),    
        sinf(angle),    
        0.0f, 
        
        0.0f, 
        -sinf(angle),   
        cosf(angle),    
        0.0f, 
        
        0.0f, 
        0.0f,           
        0.0f,           
        1.0f
    };

    return matrix;
}