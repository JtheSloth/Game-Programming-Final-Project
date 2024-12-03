
#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f


#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "Utility.h"
#include "Scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

// ����� CONSTANTS ����� //
constexpr int WINDOW_WIDTH = 640 * 1.5f,
WINDOW_HEIGHT = 480 * 1.5f;

// Background color components
constexpr float BG_RED = 0.0f,
BG_BLUE = 0.0f,
BG_GREEN = 0.0f,
BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
VIEWPORT_Y = 0,
VIEWPORT_WIDTH = WINDOW_WIDTH,
VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_lit.glsl",
F_SHADER_PATH[] = "shaders/fragment_lit.glsl";


constexpr float MILLISECONDS_IN_SECOND = 1000.0;

enum AppStatus { RUNNING, TERMINATED };

// ����� GLOBAL VARIABLES ����� //
Scene* g_current_scene;
Menu* g_menu;
Level1* g_level_1;
Level2* g_level_2;
Level3* g_level_3;
SDL_Window* g_display_window;

AppStatus g_app_status = RUNNING;
ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

void switch_to_scene(Scene* scene)
{
    //trade value for number of lives
    if (g_current_scene != nullptr) {
        scene->set_num_lives(g_current_scene->get_num_lives());
    }
    g_current_scene = scene;
    g_current_scene->initialise();
}

void initialise();
void process_input();
void update();
void render();
void shutdown();


void initialise()
{
    // ����� VIDEO ����� //
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Dungeon!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    if (context == nullptr)
    {
        shutdown();
    }

#ifdef _WINDOWS
    glewInit();
#endif

    // ����� GENERAL ����� //
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    glUseProgram(g_shader_program.get_program_id());

    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);

    //menu
    g_menu = new Menu();
    //level 1
    g_level_1 = new Level1();
    //level 2
    g_level_2 = new Level2();
    //level 3
    g_level_3 = new Level3();

    //set next scenes 
    g_menu->set_next_scene(g_level_1);
    g_level_1->set_next_scene(g_level_2);
    g_level_2->set_next_scene(g_level_3);

    //set current scene to menu
    switch_to_scene(g_menu);

    //set initial number of lives to 5
    g_current_scene->set_num_lives(5);

    // ����� BLENDING ����� //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input()
{

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            g_app_status = TERMINATED;
        }
    }

    //get keyboard state
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    //only check for movement if we are not on the menu and the game is still being played
    if (g_current_scene != g_menu && g_current_scene->get_game_status() == PLAYING) {
        //reset movement
        g_current_scene->get_state().player->reset_movement();
        if (keyState[SDL_SCANCODE_LEFT]) { //player is moving left
            g_current_scene->get_state().player->move_left();
            g_current_scene->get_state().player->set_animation_state(WALK);
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {//player is moving right
            g_current_scene->get_state().player->move_right();
            g_current_scene->get_state().player->set_animation_state(WALK);
        }
        if (keyState[SDL_SCANCODE_UP]) {//player is moving up
            g_current_scene->get_state().player->move_up();
            g_current_scene->get_state().player->set_animation_state(WALK);
        }
        if (keyState[SDL_SCANCODE_DOWN]) { //player is moving down
            g_current_scene->get_state().player->move_down();
            g_current_scene->get_state().player->set_animation_state(WALK);
        }
        if (keyState[SDL_SCANCODE_SPACE]) { //player is attacking
            g_current_scene->get_state().player->set_animation_state(ATTACK);
            //play attack sound effect
            Mix_PlayChannel(-1, g_current_scene->get_state().attack, 0);
        }
        //if player is not moving make them idle
        if(!keyState[SDL_SCANCODE_SPACE] && g_current_scene->get_state().player->get_movement().x == 0 && g_current_scene->get_state().player->get_movement().y == 0){
            g_current_scene->get_state().player->set_animation_state(IDLE);
        }
        //check if player is trying to use health potion
        if (keyState[SDL_SCANCODE_E]) {
            g_current_scene->get_state().player->use_potion();
        }
        //normalize player movement
        if (glm::length(g_current_scene->get_state().player->get_movement()) > 1.0f)
            g_current_scene->get_state().player->normalise_movement();
    }
    //if our current scene is the menu then check if the user pressed enter
    else if (g_current_scene == g_menu && g_current_scene->get_game_status() == PLAYING) {
        if (keyState[SDL_SCANCODE_RETURN]) {//if the press return switch to level 1
            switch_to_scene(g_level_1);
        }
    }
}

void update()
{
    // ����� DELTA TIME / FIXED TIME STEP CALCULATION ����� //
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP) {
        // ����� UPDATING THE SCENE (i.e. map, character, enemies...) ����� //
        g_current_scene->update(FIXED_TIMESTEP);

        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;    
    //only move camera if the current scene is not the menu
    if (g_current_scene != g_menu) {
        // ����� PLAYER CAMERA ����� //
        g_view_matrix = glm::mat4(1.0f);        
        //make camera follow player
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->get_state().player->get_position().x, -g_current_scene->get_state().player->get_position().y, 0));
        g_shader_program.set_light_position_matrix(g_current_scene->get_state().player->get_position());
        g_shader_program.set_spotlight(1);
    }
    else {
        g_shader_program.set_light_position_matrix(glm::vec3(0.0f, 0.0f, 0.0f));
        g_shader_program.set_spotlight(0);
    }

    //if the player has lost the game switch the grayscale
    if (g_current_scene->get_game_status() == LOST) {
        g_shader_program.set_spotlight(0);
    }

    //if the player has reached the stairs switch to the next level
    if (g_current_scene->get_game_status() == PLAYING && g_current_scene != g_menu && g_current_scene->get_next_scene() != nullptr && g_current_scene->get_state().player->get_reached_stairs()) {
        switch_to_scene(g_current_scene->get_next_scene());
    }
    //if the player has reached the stairs and the the next_scene pointer is nullptr, then the player has won the game
    else if(g_current_scene->get_game_status() == PLAYING && g_current_scene != g_menu && g_current_scene->get_next_scene() == nullptr && g_current_scene->get_state().player->get_reached_stairs()){
        g_current_scene->get_state().player->reset_movement();
        g_current_scene->get_state().player->set_animation_state(IDLE);
        g_current_scene->wonGame();
    }
    
}

void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);

    glClear(GL_COLOR_BUFFER_BIT);

    // ����� RENDERING THE SCENE (i.e. map, character, enemies...) ����� //
    g_current_scene->render(&g_shader_program);


    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    SDL_Quit();

    //delete all levels
    delete g_menu;
    delete g_level_1;
    delete g_level_2;
    delete g_level_3;
}

// ����� GAME LOOP ����� //
int main(int argc, char* argv[])
{
    initialise();

    while (g_app_status == RUNNING)
    {
        process_input();
        update();
        render();
    }

    shutdown();
    return 0;
}