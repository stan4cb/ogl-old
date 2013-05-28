#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "editor.h"
#include "gameObject.h"

static vec3 Zero(0,0,0);
static vec3 Up(0,1.0001,0) , Down = -Up;
static vec3 Left(-1.0001,0,0) , Right = -Left;
static vec3 Forward(0,0,-1.0001) , Backward = -Forward;

class Game
{
public:
    static Game* ins;
    static GameObject* onControl;
    static float deltaTime,lastTime,Speed;
    static bool isOpen,isEditor;
    Map map;
    Editor editor;
    Game();
    int Run();
    void Update();
    void input();
    void Timer();
};

#endif // GAME_H
