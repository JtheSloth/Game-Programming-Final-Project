#include "Level3.h"
#include "Utility.h"

int LEVEL_WIDTH_3 = 18;
int  LEVEL_HEIGHT_3 = 24;

//variables for sprite textures
//player
constexpr char g_player_idle[] = "Idle.png";
constexpr char g_player_attack[] = "Attack.png";
constexpr char g_player_walk[] = "Walk.png";
//hearts
constexpr char g_fullHeart[] = "heart_full.png";
constexpr char g_emptyHeart[] = "heart_empty.png";
//spike
constexpr char g_spike[] = "Spike.png";
//crossbow
constexpr char g_sideCrossbowIdle[] = "crossbow_side_idle.png";
constexpr char g_sideCrossbowAttack[] = "crossbow_side_attack.png";
//arrow
constexpr char g_sideArrow[] = "Arrow_side.png";
//slime
constexpr char g_slimeIdle[] = "Slime_idle.png";
constexpr char g_slimeAttack[] = "Slime_attack.png";
constexpr char g_slimeWalk[] = "Slime_walk.png";
//door
constexpr char g_doorClosed[] = "Door.png";
constexpr char g_doorOpening[] = "Door_opening.png";
constexpr char g_doorOpened[] = "Door_open.png";
//key
constexpr char g_key[] = "key_idle.png";
constexpr char g_keyFloating[] = "key_floating.png";
//potion
constexpr char g_potion[] = "Potion_idle.png";
constexpr char g_potionFloating[] = "Potion_floating.png";
//stairs
constexpr char g_stairs[] = "Stairs.png";
//font stuff
constexpr char g_fontSheet3[] = "font1.png";
GLuint g_fontSheetTextureID3;

unsigned int LEVEL_3_WALL_DATA[] =
{
    0, 0, 30, 1, 2, 1, 35, 1, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0,
    0, 0, 12, 0, 0, 0, 17, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0,
    0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0,
    0, 0, 12, 0, 0, 0, 17, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0,
    0, 0, 6, 0, 0, 0, 11, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0,
    0, 0, 12, 0, 0, 0, 17, 30, 1, 2, 3, 4, 35, 0, 0, 0, 0, 0,
    0, 0, 6, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 30, 0, 0, 0, 35, 1, 2, 1, 5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 18, 0, 0, 0, 23, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0,
    12, 1, 12, 0, 0, 0, 17, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0,
    6, 0, 6, 0, 0, 0, 11, 1, 2, 1, 5, 0, 0, 0, 0, 0, 0, 0,
    24, 0, 30, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    18, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    12, 0, 18, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    12, 1, 12, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    5, 1, 2, 0, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    12, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    18, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    24, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    30, 1, 2, 3, 4, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned int LEVEL_3_FLOOR_DATA[] =
{
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

Level3::~Level3()
{
    delete[] m_game_state.enemies;
    delete[] m_game_state.hearts;
    delete    m_game_state.player;
    delete    m_game_state.walls;
    delete    m_game_state.floors;
    Mix_FreeChunk(m_game_state.attack);
    Mix_FreeChunk(m_game_state.door_open);
    Mix_FreeChunk(m_game_state.get_item);
    Mix_FreeMusic(m_game_state.bgm);
}

void Level3::initialise()
{
    //create level walls
    GLuint map_texture_id_walls = Utility::load_texture("Dungeon_Walls.png");
    m_game_state.walls = new Map(LEVEL_WIDTH_3, LEVEL_HEIGHT_3, LEVEL_3_WALL_DATA, map_texture_id_walls, 1.0f, 6, 6);
    //create level floors
    GLuint map_texture_id_floors = Utility::load_texture("Dungeon_Floors.png");
    m_game_state.floors = new Map(LEVEL_WIDTH_3, LEVEL_HEIGHT_3, LEVEL_3_FLOOR_DATA, map_texture_id_floors, 1.0f, 4, 2);

    //load texture id for font
    g_fontSheetTextureID3 = Utility::load_texture(g_fontSheet3);

    //vector of vectors with player animation indices
    std::vector<std::vector<int>> animationsPlayer = {
        {0, 1, 2, 3, 4, 5, 6, 7}, //down
        {8, 9, 10, 11, 12, 13, 14, 15}, //left
        {24, 25, 26, 27, 28, 29, 30, 31}, //up
        {40, 41, 42, 43, 44, 45, 46, 47}//right
    };
    //create vector of player texture IDs
    std::vector<GLuint> textureIdsPlayer = { Utility::load_texture(g_player_idle), Utility::load_texture(g_player_attack), Utility::load_texture(g_player_walk) };
    m_game_state.player = new Entity(
        textureIdsPlayer, //textureID
        1.0f, //speed
        3.0f, //jump power
        animationsPlayer, //animations
        0.0f, //animation time
        8, //frames
        0, //animation index
        8, //cols
        6, //rows
        IDLE, //animation
        PLAYER, //entity type
        1.0f, //width
        1.0f //height
    );
    m_game_state.player->set_position(glm::vec3(3.5f, -2.0f, 0.0f));

    m_game_state.player->set_health(m_game_state.num_lives);
    //create player hearts
    m_game_state.hearts = new Entity[5];
    for (size_t ind = 0; ind < 5; ind++) {
        //creating each heart
        std::vector<GLuint> textureIdsHeart = { Utility::load_texture(g_fullHeart), Utility::load_texture(g_emptyHeart) };
        std::vector<std::vector<int>> animationsHeart = {
            {0}, //full
            {0}, //empty
        };
        m_game_state.hearts[ind] = Entity(textureIdsHeart, 1.0f, 1.8f, animationsHeart, 0.0f, 1, 0, 1, 1, IDLE, HEARTS, 1.0f, 1.0f);
        m_game_state.hearts[ind].set_animation_state(IDLE);
        //space out hearts
        m_game_state.hearts[ind].set_position(glm::vec3(ind, 0.0f, 0.0f));
    }
    //update any hearts that need to be empty
    for (int curr = 5; curr > m_game_state.num_lives; curr--) {
        m_game_state.hearts[curr - 1].set_animation_state(EMPTY);
    }

    //create enemies
    m_game_state.enemies = new Entity[ENEMY_COUNT];

    //create door
    std::vector<std::vector<int>> animationsDoor{ {0}, {0, 1, 2, 3, 4, 5, 6, 7 }, {0} };
    std::vector<GLuint> textureIdsDoor = { Utility::load_texture(g_doorClosed), Utility::load_texture(g_doorOpening), Utility::load_texture(g_doorOpened) };
    m_game_state.enemies[0] = Entity(textureIdsDoor, 1.0f, 1.0f, animationsDoor, 0.0f, 1, 0, 1, 1, CLOSED, DOOR, 1.0f, 1.0f);
    m_game_state.enemies[0].set_position(glm::vec3(2.95f, -17.8f, 0.0f));
    m_game_state.enemies[0].set_animation_state(CLOSED);

    //create key
    std::vector<std::vector<int>> animationsKeys{ {0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} };
    std::vector<GLuint> textureIdsKey = { Utility::load_texture(g_key), Utility::load_texture(g_keyFloating) };
    m_game_state.enemies[1] = Entity(textureIdsKey, 1.0f, 1.0f, animationsKeys, 0.0f, 1, 0, 1, 1, IDLE, KEY, 1.0f, 1.0f);
    m_game_state.enemies[1].set_position(glm::vec3(7.5f, -10.0f, 0.0f));
    m_game_state.enemies[1].set_animation_state(FLOATING);

    //create potions
    std::vector<std::vector<int>> animationsPotions{ {0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} };
    std::vector<GLuint> textureIdsPotion = { Utility::load_texture(g_potion), Utility::load_texture(g_potionFloating) };
    m_game_state.enemies[2] = Entity(textureIdsPotion, 1.0f, 1.0f, animationsPotions, 0.0f, 1, 0, 1, 1, IDLE, POTION, 1.0f, 1.0f);
    m_game_state.enemies[2].set_position(glm::vec3(9.0f, -2.0f, 0.0f));
    m_game_state.enemies[2].set_animation_state(FLOATING);

    m_game_state.enemies[3] = Entity(textureIdsPotion, 1.0f, 1.0f, animationsPotions, 0.0f, 1, 0, 1, 1, IDLE, POTION, 1.0f, 1.0f);
    m_game_state.enemies[3].set_position(glm::vec3(1.0f, -11.0f, 0.0f));
    m_game_state.enemies[3].set_animation_state(FLOATING);

    //create spike enemies
    std::vector<std::vector<int>> animationsSpike = { {0, 1, 2, 3, 4, 5, 6, 7, 8} };
    std::vector<GLuint> textureIdsSpike = { Utility::load_texture(g_spike) };
    for (int ind = 4; ind < 9; ind++) {
        m_game_state.enemies[ind] = Entity(textureIdsSpike, 1.0f, 1.0f, animationsSpike, 0.0f, 9, 0, 9, 1, IDLE, ENEMY, 0.8f, 0.8f);
        m_game_state.enemies[ind].set_ai_type(SPIKE);
        m_game_state.enemies[ind].set_animation_state(IDLE);
    }
    m_game_state.enemies[4].set_position(glm::vec3(3.5f, -4.0f, 0.0f));
    m_game_state.enemies[5].set_position(glm::vec3(3.5f, -7.0f, 0.0f));
    m_game_state.enemies[6].set_position(glm::vec3(4.5f, -4.0f, 0.0f));
    m_game_state.enemies[7].set_position(glm::vec3(4.5f, -7.0f, 0.0f));
    m_game_state.enemies[8].set_position(glm::vec3(1.0f, -13.0f, 0.0f));

    //create a crossbows  and arrows
    std::vector<std::vector<int>> animationsCrossbow = { {0}, {0, 1, 2, 3, 4, 5, 6, 7} };
    std::vector<GLuint> textureIdsSideCrossbow = { Utility::load_texture(g_sideCrossbowIdle), Utility::load_texture(g_sideCrossbowAttack) };
    std::vector<std::vector<int>> animationsArrow{ {0} };
    std::vector<GLuint> textureIdsSideArrow = { Utility::load_texture(g_sideArrow) };

    m_game_state.enemies[9] = Entity(textureIdsSideCrossbow, 1.0f, 1.0f, animationsCrossbow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[9].set_ai_type(CROSSBOW);
    m_game_state.enemies[9].set_position(glm::vec3(5.1f, -12.75f, 0.0f));
    m_game_state.enemies[9].set_animation_state(IDLE);

    m_game_state.enemies[10] = Entity(textureIdsSideArrow, 1.0f, 1.0f, animationsArrow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[10].set_ai_type(ARROW);
    m_game_state.enemies[10].set_position(glm::vec3(5.1f, -12.85f, 0.0f));
    m_game_state.enemies[10].set_animation_state(IDLE);

    m_game_state.enemies[11] = Entity(textureIdsSideCrossbow, 1.0f, 1.0f, animationsCrossbow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[11].set_ai_type(CROSSBOW);
    m_game_state.enemies[11].set_position(glm::vec3(5.1f, -14.75f, 0.0f));
    m_game_state.enemies[11].set_animation_state(IDLE);

    m_game_state.enemies[12] = Entity(textureIdsSideArrow, 1.0f, 1.0f, animationsArrow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[12].set_ai_type(ARROW);
    m_game_state.enemies[12].set_position(glm::vec3(5.1f, -14.85f, 0.0f));
    m_game_state.enemies[12].set_animation_state(IDLE);

    m_game_state.enemies[13] = Entity(textureIdsSideCrossbow, 1.0f, 1.0f, animationsCrossbow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[13].set_ai_type(CROSSBOW);
    m_game_state.enemies[13].set_position(glm::vec3(5.1f, -16.75f, 0.0f));
    m_game_state.enemies[13].set_animation_state(IDLE);

    m_game_state.enemies[14] = Entity(textureIdsSideArrow, 1.0f, 1.0f, animationsArrow, 0.0f, 1, 0, 1, 1, IDLE, ENEMY, 0.5f, 0.5f);
    m_game_state.enemies[14].set_ai_type(ARROW);
    m_game_state.enemies[14].set_position(glm::vec3(5.1f, -16.85f, 0.0f));
    m_game_state.enemies[14].set_animation_state(IDLE);

    //create slime enemies
    std::vector<std::vector<int>> animationsSlime{
        {0, 1, 2, 3}, //down
        {4, 5, 6, 7}, //left
        {12, 13, 14, 15}, //up
        {8, 9, 10, 11} // right
    };
    std::vector<GLuint> textureIdsSlime = { Utility::load_texture(g_slimeIdle), Utility::load_texture(g_slimeAttack), Utility::load_texture(g_slimeWalk) };
    for (int ind = 15; ind < 19; ind++) {
        m_game_state.enemies[ind] = Entity(textureIdsSlime, 0.2f, 1.0f, animationsSlime, 0.0f, 4, 0, 4, 4, IDLE, ENEMY, 0.6f, 0.6f);
        m_game_state.enemies[ind].set_ai_type(SLIME);
        m_game_state.enemies[ind].set_animation_state(IDLE);
        m_game_state.enemies[ind].set_health(1);
    }
    m_game_state.enemies[15].set_position(glm::vec3(9.0f, -3.0f, 0.0f));
    m_game_state.enemies[16].set_position(glm::vec3(10.0f, -3.0f, 0.0f));
    m_game_state.enemies[17].set_position(glm::vec3(8.0f, -9.0f, 0.0f));
    m_game_state.enemies[18].set_position(glm::vec3(9.0f, -9.0f, 0.0f));

    //create stairs
    std::vector<std::vector<int>> animationsStairs{ {0} };
    std::vector<GLuint> textureIdsStairs = { Utility::load_texture(g_stairs) };
    m_game_state.enemies[19] = Entity(textureIdsStairs, 0.2f, 1.0f, animationsStairs, 0.0f, 1, 0, 1, 1, IDLE, STAIRS, 3.2f, 3.2f);
    m_game_state.enemies[19].set_animation_state(IDLE);
    m_game_state.enemies[19].set_position(glm::vec3(3.0f, -20.5f, 0.0f));

    
    //music and sound effects
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_game_state.bgm = Mix_LoadMUS("Goblins_Den_(Regular).mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    m_game_state.attack = Mix_LoadWAV("attack.wav");
    m_game_state.door_open = Mix_LoadWAV("door_open.wav");
    m_game_state.get_item = Mix_LoadWAV("get_item.wav");
    m_game_state.damage = Mix_LoadWAV("damage.wav");
}

void Level3::update(float delta_time)
{
    //if the player has 0 lives left lose the game
    if (m_game_state.player->isActive() && m_game_state.player->get_health() == 0) {
        lostGame();
        m_game_state.player->set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
        m_game_state.player->set_animation_state(IDLE);
    }
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.walls);
    //if the player is active and they need lose a life subtract 1 from game state number of lives
    if (m_game_state.player->isActive() && m_game_state.player->get_health() < m_game_state.num_lives) {
        m_game_state.num_lives -= 1;
        m_game_state.hearts[m_game_state.num_lives].set_animation_state(EMPTY);
        //play damage sound effect
        Mix_PlayChannel(-1, m_game_state.damage, 0);
    }
    //if the player needs to gain a life make a heart active
    if (m_game_state.player->isActive() && m_game_state.player->get_health() > m_game_state.num_lives) {
        m_game_state.hearts[m_game_state.num_lives].set_animation_state(FULL);
        m_game_state.num_lives += 1;
    }
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.walls);
        //if a slime enemy has 0 health deactivate them
        if (m_game_state.enemies[i].get_entity_type() == ENEMY && m_game_state.enemies[i].get_ai_type() == SLIME && m_game_state.enemies[i].get_health() == 0) {
            m_game_state.enemies[i].deactivate();
        }
        //if a door is opening play the door opening sound effect
        if (m_game_state.enemies[i].get_entity_type() == DOOR && m_game_state.enemies[i].get_animation_state() == OPENING) {
            //play door opening sound effect
            Mix_PlayChannel(-1, m_game_state.door_open, 0);
        }
    }
    //if the player got a new item play a sound
    if (m_game_state.player->get_new_item()) {
        //play getting new item sound
        Mix_PlayChannel(-1, m_game_state.get_item, 0);
    }
    for (int i = 0; i < 5; i++) {
        m_game_state.hearts[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.walls);
    }
}


void Level3::render(ShaderProgram* g_shader_program)
{
    //render walls and floor
    m_game_state.floors->render(g_shader_program);
    m_game_state.walls->render(g_shader_program);

    //render enemies that are not keys or potions
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_entity_type() != KEY && m_game_state.enemies[i].get_entity_type() != POTION) {
            m_game_state.enemies[i].render(g_shader_program);
        }
    }
    //render keys and potions
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_entity_type() == KEY || m_game_state.enemies[i].get_entity_type() == POTION) {
            m_game_state.enemies[i].render(g_shader_program);
        }
    }
    //render hearts
    for (int i = 0; i < 5; i++) {
        m_game_state.hearts[i].render(g_shader_program);
    }
    //render player
    m_game_state.player->render(g_shader_program);
    //if the player has lost the game render a message
    if (m_game_state.gameStat == LOST) {
        Utility::draw_text(g_shader_program, g_fontSheetTextureID3, "You Lost!", 0.5f, 0.001f, glm::vec3(m_game_state.player->get_position().x - 1.0f, m_game_state.player->get_position().y + 1.0f, 0.0f));
    }
    //if the player has won the game render a message
    if (m_game_state.gameStat == WON) {
        Utility::draw_text(g_shader_program, g_fontSheetTextureID3, "You Won!", 0.5f, 0.001f, glm::vec3(m_game_state.player->get_position().x - 1.0f, m_game_state.player->get_position().y + 1.0f, 0.0f));
    }
}