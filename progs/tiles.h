#pragma once
#include "config.h"

class Tile {
    public:
    std::vector<float> data;
    Tile();
    int randomTile();
    void draw();
    void moveTile();
    ~Tile();

    unsigned int VBO, VAO, vertex_count;
    std::vector<std::vector<float>> possibleTiles
    {
        // Первая плитка (левый верхний угол)
        {
            // Первый треугольник
            -1.0f,  1.0f, 1.0f, 0.25f, 0.5f, 0.75f,
            -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Вторая плитка (средний верх)
        {
            // Первый треугольник
            -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Третья плитка (правый верхний угол)
        {
            // Первый треугольник
            0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Четвертая плитка (левый центр)
        {
            // Первый треугольник
            0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Пятая плитка (центральная)
        {
            // Первый треугольник
            -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Шестая плитка (правый центр)
        {
            // Первый треугольник
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Седьмая плитка (левый нижний угол)
        {
            // Первый треугольник
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Восьмая плитка (средний низ)
        {
            // Первый треугольник
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Девятая плитка (правый нижний угол)
        {
            // Первый треугольник
            -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Десятая плитка (правый верхний угол второй строки)
        {
            // Первый треугольник
            -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Одиннадцатая плитка (правый центр второй строки)
        {
            // Первый треугольник
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f
            
        },

        // Двенадцатая плитка (правый нижний угол)
        {
            // Первый треугольник
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Тринадцатая плитка (левый верхний угол третьей строки)
        {
            // Первый треугольник
            -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Четырнадцатая плитка (средний верх третьей строки)
        {
            // Первый треугольник
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Пятнадцатая плитка (правый верхний угол третьей строки)
        {
            // Первый треугольник
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        },

        // Шестнадцатая плитка (правый верхний угол четвертой строки)
        {
            // Первый треугольник
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            // Второй треугольник
            1.0f, -1.0f, 0.0f, 0.75f, 0.5f, 0.25f,
            0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        }
    };
};

class Map {
    public:
    Map();
    void drawMap();
    ~Map();
        
    private:
    unsigned int VBO, VAO, vertex_count;
    };    

    
int tiles();
bool isClickedOnBlackTile(double mousePosX, double mousePosY, unsigned int playground, Tile* tile);
