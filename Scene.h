#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Utility.h"
#include "Entity.h"
#include "Map.h"

enum GameStatus { PLAYING, WON, LOST };
class Scene;

struct GameState
{
    // ————— GAME OBJECTS ————— //
    Map* walls;
    Map* floors;
    Entity* player;
    Entity* enemies;
    Entity* hearts;

    // ————— AUDIO ————— //
    Mix_Music* bgm;
    Mix_Chunk* get_item;
    Mix_Chunk* attack;
    Mix_Chunk* door_open;
    Mix_Chunk* damage;
    
    // ————— POINTERS TO OTHER SCENES ————— //
    Scene* next_scene;
    //gameStatus
    GameStatus gameStat = PLAYING;
    //number of lives
    int num_lives;
};

class Scene {
protected:
    GameState m_game_state;
    
public:
    // ————— ATTRIBUTES ————— //
    int m_number_of_enemies = 0;
    
    // ————— METHODS ————— //
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram *program) = 0;
    
    
    // ————— GETTERS ————— //
    GameState const get_state() const { return m_game_state;             }
    int const get_number_of_enemies() const { return m_number_of_enemies; }
    int get_num_lives() const { return m_game_state.num_lives; };
    GameStatus get_game_status() const { return m_game_state.gameStat; };
    Scene* get_next_scene() const { return m_game_state.next_scene;  }

    //------ SETTERS ------//
    void set_num_lives(int newNum) { m_game_state.num_lives = newNum; };
    void set_next_scene(Scene* next) { m_game_state.next_scene = next; };
    void lostGame() { m_game_state.gameStat = LOST; };
    void wonGame() { m_game_state.gameStat = WON; };
};
