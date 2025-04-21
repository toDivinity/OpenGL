#include "tiles.h"
#include <unordered_set>

#define TILE_COUNT 3

int WHITE_TILES_WIDTH = 1000, WHITE_TILES_HEIGHT = 800;

int tiles()
{
    if (!glfwInit()) 
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WHITE_TILES_WIDTH, WHITE_TILES_HEIGHT, "Tiles", NULL, NULL);

    if (!window)
    {
        std::cerr << "Failed to create GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "GLAD initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    double mousePosX = -1;
    double mousePosY = -1;

    unsigned int shader = make_shader(
        "../../shaders/tilesVertex.glsl",
        "../../shaders/tilesFragments.glsl"
    );

    unsigned int lineShader = make_shader(
        "../../shaders/lineVertex.glsl",
        "../../shaders/lineFragments.glsl" 
    );
    
    Tile* tiles[TILE_COUNT];
    for (int i = 0; i < TILE_COUNT; ++i) {
        tiles[i] = new Tile();
    }
    Map* map = new Map();

    unsigned int playground = 500;
    unsigned int score = 0;

    glClearColor(1.0f, 0.98f, 0.88f, 1.0f);

    while (!glfwWindowShouldClose(window)) {

        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && playground<800) playground++;
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && playground>100) playground--;
        
        processInput(window);
        if(mousePosOnClickPress(window, &mousePosX, &mousePosY))
        {
            bool clickedOnBlack = false;

            for (int i = 0; i < TILE_COUNT; ++i) {
                if(isClickedOnBlackTile(mousePosX, mousePosY, playground, tiles[i]))
                {
                    score++;
                    std::cout<<"Score:"<<score<<std::endl;
                    tiles[i]->moveTile();
                    clickedOnBlack = true;
                    break;
                }
            }
            
            if (!clickedOnBlack) {
                score = 0;
                std::cout<<"Game Over"<<std::endl;
                std::cout<<"Score:"<<score<<std::endl;
                
                for (int i = 0; i < TILE_COUNT; ++i) delete tiles[i];
                for (int i = 0; i < TILE_COUNT; ++i) {
                    tiles[i] = new Tile();
                }

            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwGetWindowSize(window, &WHITE_TILES_WIDTH, &WHITE_TILES_HEIGHT); 
        glViewport(
            (WHITE_TILES_WIDTH - playground) / 2,    // x позиция
            (WHITE_TILES_HEIGHT - playground) / 2,   // y позиция
            playground,                             // ширина
            playground                              // высота
        );

        glUseProgram(shader);
        for (int i = 0; i < TILE_COUNT; ++i) {
            tiles[i]->draw();
        }

        glUseProgram(lineShader);
        glUniform3f(glGetUniformLocation(lineShader, "lineColor"), 0.25f, 0.25f, 0.5f);
        map->drawMap();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    for (int i = 0; i < TILE_COUNT; ++i) {
        delete tiles[i];
    }
    glDeleteProgram(lineShader);
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}

bool isClickedOnBlackTile(double mousePosX, double mousePosY, unsigned int playground, Tile* tile) {
    // 1. Получаем параметры viewport
    int viewportX = (WHITE_TILES_WIDTH - playground) / 2;
    int viewportY = (WHITE_TILES_HEIGHT - playground) / 2;
    int viewportWidth = playground;
    int viewportHeight = playground;
    
    // 2. Проверяем, что клик был внутри viewport
    if (mousePosX < viewportX || mousePosX > viewportX + viewportWidth ||
        mousePosY < viewportY || mousePosY > viewportY + viewportHeight) {
        return false;
    }
    
    // 3. Преобразуем координаты мыши относительно viewport в нормализованные координаты OpenGL
    double x = (2.0f * (mousePosX - viewportX)) / viewportWidth - 1.0f;
    double y = 1.0f - (2.0f * (mousePosY - viewportY)) / viewportHeight;

    if(x>tile->data[0] && x<tile->data[18] && y<tile->data[1] && y>tile->data[19])
    {
        std::cout<<x<<" "<<y<<std::endl;
        return true;
    }

    return false;
}

Map::Map()
{
    float lineVertices[] = {
        -0.5f, -1.0f, 0.0f,
        -0.5f,  1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,

        0.5f, -1.0f, 0.0f,
        0.5f,  1.0f, 0.0f,

        -1.0f, -0.5f, 0.0f,
        1.0f,  -0.5f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 0.0f,

        -1.0f, 0.5f, 0.0f,
        1.0f,  0.5f, 0.0f,

        -0.999f, -1.0f, 0.0f,
        -0.999f, 1.0f, 0.0f,

        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        
        1.0f, 0.999f, 0.0f,
        -1.0f, 0.999f, 0.0f,

    };

    vertex_count = 20;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Map::drawMap() 
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertex_count);
}

Map::~Map() 
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Tile::Tile() {
    data = possibleTiles[randomTile()];
    vertex_count = 6;  // 6 вершин для 2 треугольников

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    // position (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    // color (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);
}

int Tile::randomTile()
{
    static std::unordered_set<int> usedTiles;
    
    if(usedTiles.size() >= possibleTiles.size()) {
        usedTiles.clear();
    }
    
    int randomIndex;
    do {
        randomIndex = rand() % possibleTiles.size();
    } while(usedTiles.count(randomIndex) > 0);
    
    usedTiles.insert(randomIndex);
    
    return randomIndex;
}

void Tile::draw() 
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Tile::moveTile()
{
    auto prevData = data;
    data = possibleTiles[randomTile()];
    
    if (prevData == data)
    {
        data = possibleTiles[randomTile()];
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
}

Tile::~Tile() 
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}