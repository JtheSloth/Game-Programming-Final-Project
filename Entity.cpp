#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"
// Default constructor
Entity::Entity()
    : m_position(0.0f), m_movement(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_velocity(0.0f), m_acceleration(0.0f), m_model_matrix(1.0f),
    m_speed(0.0f), m_animation_cols(0), m_animation_frames(0), m_animation_index(0),
    m_animation_rows(0), m_animation_indices(nullptr), m_animation_time(0.0f),
    m_current_animation(IDLE)
{
}

// Parameterized constructor
Entity::Entity(std::vector<GLuint> texture_ids, float speed, float jump_power,
    std::vector<std::vector<int>> animations, float animation_time,
    int animation_frames, int animation_index, int animation_cols,
    int animation_rows, Animation animation, EntityType EntityType, float width, float height)
    : m_position(0.0f), m_movement(0.0f), m_velocity(0.0f), m_acceleration(0.0f), m_scale(1.0f, 1.0f, 0.0f), m_model_matrix(1.0f),
    m_speed(speed), m_texture_ids(texture_ids), m_animations(animations),
    m_animation_cols(animation_cols), m_animation_frames(animation_frames),
    m_animation_index(animation_index), m_animation_rows(animation_rows),
    m_animation_time(animation_time), m_current_animation(animation), m_jumping_power(jump_power),
    m_entity_type(EntityType), m_width(width), m_height(height), m_is_jumping(false), m_is_active(true)
{
    set_animation_state(m_current_animation);  // Initialize animation state

}


Entity::~Entity() { }

void Entity::set_animation_state(Animation new_animation)
{
    m_current_animation = new_animation;
    //set frames, cols, and scaling based on current animation
    if (m_entity_type == PLAYER) {
        if (m_current_animation == IDLE) { //standing still
            m_animation_frames = 8;
            m_animation_cols = 8;
            m_animation_rows = 6;
            m_scale = glm::vec3(3.0f, 3.0f, 0.0f);
        }
        else if (m_current_animation == WALK) { //walking
            m_animation_frames = 8;
            m_animation_cols = 8;
            m_animation_rows = 6;
            m_scale = glm::vec3(3.0f, 3.0f, 0.0f);
        }
        else if (m_current_animation == ATTACK) {//attack
            m_animation_frames = 8;
            m_animation_cols = 8;
            m_animation_rows = 8;
            m_scale = glm::vec3(3.0f, 3.0f, 0.0f);
        }
        // Update the texture and animation indices based on current direction of player
        m_animation_indices = m_animations[m_direction].data();
    }else if (m_entity_type == HEARTS) { //if the entity is a heart
        if (m_current_animation == IDLE) { //still has heart
            m_animation_frames = m_animations[IDLE].size();
            m_animation_cols = m_animations[IDLE].size();
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        else if (m_current_animation == EMPTY) { //heart is empty
            m_animation_frames = m_animations[EMPTY].size();
            m_animation_cols = m_animations[EMPTY].size();
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        m_animation_indices = m_animations[m_current_animation].data();
    }else if (m_entity_type == ENEMY && m_ai_type == SPIKE){ // if an enemy is a spike 
        m_animation_frames = 9;
        m_animation_cols = 9;
        m_animation_rows = 1;
        m_scale = glm::vec3(3.0f, 3.0f, 0.0f);
        m_animation_indices = m_animations[m_current_animation].data();
    }
    else if (m_entity_type == ENEMY && m_ai_type == CROSSBOW) {//if the enemy is a crossbow
        if (m_current_animation == IDLE) {
            m_animation_frames = 1;
            m_animation_cols = 1;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);

        }
        else if (m_current_animation == ATTACK) {
            m_animation_frames = 8;
            m_animation_cols = 8;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        m_animation_indices = m_animations[m_current_animation].data();

    }
    else if (m_entity_type == ENEMY && m_ai_type == ARROW) {//if enemy is an arrow
        m_animation_frames = 1;
        m_animation_cols = 1;
        m_animation_rows = 1;
        m_scale = glm::vec3(0.6f, 0.6f, 0.0f);
        m_animation_indices = m_animations[m_current_animation].data();
    }
    else if (m_entity_type == ENEMY && m_ai_type == SLIME) {//if the enemey is a slime
        m_animation_frames = 4;
        m_animation_cols = 4;
        m_animation_rows = 4;
        m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        m_animation_indices = m_animations[m_direction].data();
    }
    else if (m_entity_type == DOOR) {
        if (m_current_animation == CLOSED) {
            m_animation_frames = 1;
            m_animation_cols = 1;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.55f, 1.55f, 0.0f);
        }
        else if(m_current_animation == OPENING){
            m_animation_frames = 8;
            m_animation_cols = 8;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.55f, 1.55f, 0.0f);
        }
        else {
            m_animation_frames = 1;
            m_animation_cols = 1;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.55f, 1.55f, 0.0f);
        }
        m_animation_indices = m_animations[m_current_animation].data();
    }
    else if (m_entity_type == KEY) {
        if (m_current_animation == IDLE) {
            m_animation_frames = 1;
            m_animation_cols = 1;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        else {
            m_animation_frames = 16;
            m_animation_cols = 16;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        m_animation_indices = m_animations[m_current_animation].data();

    }
    else if (m_entity_type == POTION) {
        if (m_current_animation == IDLE) {
            m_animation_frames = 1;
            m_animation_cols = 1;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        else {
            m_animation_frames = 16;
            m_animation_cols = 16;
            m_animation_rows = 1;
            m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        m_animation_indices = m_animations[m_current_animation].data();
    }
    else if (m_entity_type == STAIRS) {
        m_animation_frames = 1;
        m_animation_cols = 1;
        m_animation_rows = 1;
        m_scale = glm::vec3(3.2f, 3.2f, 0.0f);
        m_animation_indices = m_animations[m_current_animation].data();
    }

    
}
void Entity::move_left() {
    m_movement.x = -1.0f;
    m_direction = LEFT;
    m_animation_indices = m_animations[m_direction].data();
}
void Entity::move_right() {
    m_movement.x = 1.0f;
    m_direction = RIGHT;
    m_animation_indices = m_animations[m_direction].data();
}
void Entity::move_up() {
    m_movement.y = 1.0f;
    m_direction = UP;
    m_animation_indices = m_animations[m_direction].data();
}
void Entity::move_down() {
    m_movement.y = -1.0f;
    m_direction = DOWN;
    m_animation_indices = m_animations[m_direction].data();
}
void Entity::reset_movement() {
    m_movement.y = 0;
    m_movement.x = 0;
};

void Entity::ai_activate(Entity* player,Entity* other_entities, int entity_count) {
    //call the correct ai function based on the type of enemy
    if (m_ai_type == CROSSBOW) {
        ai_sideCrossbow(player, other_entities, entity_count);
    }
    else if (m_ai_type == ARROW) {
        ai_sideArrow();
    }
    else if (m_ai_type == SLIME) {
        ai_slime(player);
    }
}
void Entity::ai_slime(Entity* player) {
    //if the player is dead set animatin state to idle and return
    if (player->m_health == 0) {
        reset_movement();
        set_animation_state(IDLE);
        return;
    }
    //if the player is close enough attack
    if (glm::distance(player->get_position(), m_position) < 1) {
        set_animation_state(ATTACK);
    }
    else if (glm::distance(player->get_position(), m_position) < 2) { //if player is close move towards them
        set_animation_state(WALK);
    }
    else {
        reset_movement();
        set_animation_state(IDLE);
    }
    if (m_current_animation == WALK) {
        if (m_position.x > player->get_position().x) {
            move_left();
        }
        if(m_position.x < player->get_position().x) {
            move_right();
        }
        if (m_position.y > player->get_position().y) {
            move_down();
        }
        if(m_position.y < player->get_position().y) {
            move_up();
        }
    }
}

void Entity::ai_sideCrossbow(Entity* player, Entity* other_entities, int entity_count) {
    //if the player is close to us and we haven't already shot and an arrow and if we haven't reached the end of the attack animation shoot an arrow
    //check that the player is in front of us
    if (glm::distance(player->get_position().y, m_position.y) < 1.0 && glm::distance(player->get_position().x, m_position.x) < 3.0 && m_animation_index < 7 && !m_fired  && player->get_position().x < m_position.x) {
        set_animation_state(ATTACK);
        if (m_animation_index == 3) {
            //item in the arrow right after the crossbow is it's arrow
            for (int ind = 0; ind < entity_count; ind++) {
                //once we have found ourselve in the array we know that the item after it is the arrow
                if (&other_entities[ind] == this) {
                    other_entities[ind + 1].m_fired = true;
                }
            }
        }
        
    }
    else if(m_current_animation == ATTACK){//if the player is far go back to idle
        set_animation_state(IDLE);
        m_fired = true;
    }
}
//function for ai side arrow
void Entity::ai_sideArrow() {
    //if the arrow hit something deactivate it
    if (m_collided_bottom || m_collided_left || m_collided_right || m_collided_top) {
        deactivate();
        return;
    }
    //if the arrow has been fired then move it forward
    if (m_fired == true) {
        m_movement.x = -1.0f;
    }
    else {
        m_movement.x = 0.0f;
    }
}
//gain key method
void Entity::gain_key(Entity* key) {
    //if the key has already been collected return
    if (key->m_collected) {
        return;
    }
    m_got_new_item = true;
    key->m_collected = true;
    key->set_animation_state(IDLE);
    keys.push_back(key);
    key->m_position.x = keys.size() - 1;
}
//gain potion method
void Entity::gain_potion(Entity* potion) {
    //if the potion has already been collected return
    if(potion->m_collected) {
        return;
    }
    m_got_new_item = true;
    potion->m_collected = true;
    potion->set_animation_state(IDLE);
    potions.push_back(potion);
    potion->m_position.x = potions.size() - 1;
}
//use potion method
void Entity::use_potion(){
    //if the player has full health or no potions just return
    if (m_health == 5 || potions.size() == 0) {
        return;
    }
    else {
        //remove potion from player vector and increase health
        potions[potions.size() - 1]->deactivate();
        potions.pop_back();
        m_health++;
    }
}
// Render the appropriate texture and animation frame
void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program)
{
    GLuint current_texture = m_texture_ids[m_current_animation];  // Get the right texture

    float u_coord = (float)(m_animation_indices[m_animation_index] % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(m_animation_indices[m_animation_index] / m_animation_cols) / (float)m_animation_rows;

    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;

    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width,
        v_coord, u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    glBindTexture(GL_TEXTURE_2D, current_texture);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0,
        vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0,
        tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

void Entity::update(float delta_time, Entity* player, Entity* collidable_entities, int collidable_entity_count, Map* map)
{
    //if we are not active just return
    if (!m_is_active) {
        return;
    }
    //if the enitiy is a spike
    if (m_entity_type == ENEMY && m_ai_type == SPIKE) {
        //do animations for spike
        m_animation_time += delta_time;
        float frames_per_second = 1.0f / SECONDS_PER_FRAME;
        //slow down the spike's animation time
        if (m_animation_time >= frames_per_second*5.0f)
        {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }
        m_model_matrix = glm::mat4(1.0f);
        m_model_matrix = glm::translate(m_model_matrix, m_position);
        m_model_matrix = glm::scale(m_model_matrix, m_scale);
        return;
    }
    
    //if we are an enemy activate ai
    if (m_entity_type == ENEMY) {
        ai_activate(player, collidable_entities, collidable_entity_count);
    }
    //if we hearts then follow the players movement
    if (m_entity_type == HEARTS) {
        m_model_matrix = glm::mat4(1.0f);
        m_model_matrix = glm::translate(m_model_matrix, glm::vec3(player->m_position.x + m_position.x - 4.25f, player->m_position.y + 3.0f, 0.0f));
        m_model_matrix = glm::scale(m_model_matrix, m_scale);
        return;
    }
    //if we are a door
    if (m_entity_type == DOOR) {
        //if the door has finished doing the opening animation switch to Opened
        if (m_animation_index >= 7 && m_current_animation == OPENING) {
            set_animation_state(OPENED);
        }
        //do animations for door
        m_animation_time += delta_time;
        float frames_per_second = 1.0f / SECONDS_PER_FRAME;
        if (m_animation_time >= frames_per_second)
        {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }
        m_model_matrix = glm::mat4(1.0f);
        m_model_matrix = glm::translate(m_model_matrix, m_position);
        m_model_matrix = glm::scale(m_model_matrix, m_scale);
        return;
    }
    //if we are a key
    if (m_entity_type == KEY) {
        //do animations
        m_animation_time += delta_time;
        float frames_per_second = 1.0f / SECONDS_PER_FRAME;
        if (m_animation_time >= frames_per_second)
        {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }        
        m_model_matrix = glm::mat4(1.0f);
        //if this key has been collected move it to the bottom left corner
        if (m_collected) {
            m_model_matrix = glm::translate(m_model_matrix, glm::vec3(player->m_position.x - 4.25f + m_position.x, player->m_position.y - 3.0f, 0.0f));
        }
        else {
            m_model_matrix = glm::translate(m_model_matrix, m_position);
        }
        m_model_matrix = glm::scale(m_model_matrix, m_scale);
        return;
    }
    //if we are a potion
    if (m_entity_type == POTION) {
        //do animations
        m_animation_time += delta_time;
        float frames_per_second = 1.0f / SECONDS_PER_FRAME;
        if (m_animation_time >= frames_per_second)
        {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }

        m_model_matrix = glm::mat4(1.0f);
        //if this potion has been collected move it to the top right corner
        if (m_collected) {
            m_model_matrix = glm::translate(m_model_matrix, glm::vec3(player->m_position.x - m_position.x + 4.25f, player->m_position.y + 3.0f, 0.0f));
        }
        else {
            m_model_matrix = glm::translate(m_model_matrix, m_position);
        }
        m_model_matrix = glm::scale(m_model_matrix, m_scale);
        return;
    }
   
    //increase our time since hit value
    m_time_since_hit += delta_time;
    m_animation_time += delta_time;
    float frames_per_second = 1.0f / SECONDS_PER_FRAME;

    m_collided_top = false;
    m_collided_bottom = false;
    m_collided_left = false;
    m_collided_right = false;

    if (m_animation_time >= frames_per_second)
    {
        m_animation_time = 0.0f;
        m_animation_index++;

        if (m_animation_index >= m_animation_frames)
        {
            m_animation_index = 0;
        }
    }
    //reset got new item bool
    m_got_new_item = false;
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;
    m_velocity += m_acceleration * delta_time;

    m_position.y += m_velocity.y * delta_time;
    if (m_entity_type == PLAYER) {
        check_collision_y(collidable_entities, collidable_entity_count);
    }
    check_collision_y(map);

    m_position.x += m_velocity.x * delta_time;
    if (m_entity_type == PLAYER) {
        check_collision_x(collidable_entities, collidable_entity_count);
    }
    check_collision_x(map);

    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = glm::scale(m_model_matrix, m_scale);
}

void Entity::render(ShaderProgram* program)
{
    //don't render character if they aren't active 
    if (!m_is_active) {
        return;
    }
    program->set_model_matrix(m_model_matrix);

    if (m_animation_indices != nullptr) draw_sprite_from_texture_atlas(program);
    if (m_animation_indices == nullptr) {
        std::cout << "ERROR";
    }
}

//------COLLISIONS-------//
bool const Entity::check_collision(Entity* other) const
{
    float x_distance = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_distance = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return x_distance < 0.0f && y_distance < 0.0f;
}

void const Entity::check_collision_y(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (collidable_entity->m_is_active && check_collision(collidable_entity))
        {
            float y_distance = fabs(m_position.y - collidable_entity->m_position.y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->m_height / 2.0f));
            if (m_velocity.y > 0)
            {
                if (collidable_entity->m_entity_type == DOOR && collidable_entity->m_current_animation == CLOSED) {
                    m_position.y -= y_overlap;
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                    //if the player has a key open the door
                    if (keys.size() != 0) {
                        collidable_entity->set_animation_state(OPENING);
                        keys[keys.size() - 1]->deactivate();
                        keys.pop_back();
                    }
                   
                }
                //if we are hiting a key or a potion we collect it 
                else if (collidable_entity->m_entity_type == KEY) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                    gain_key(collidable_entity);
                }
                else if (collidable_entity->m_entity_type == POTION) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                    gain_potion(collidable_entity);
                }
                else if (collidable_entity->m_ai_type == SPIKE) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                }
                else if (collidable_entity->m_ai_type == ARROW) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                    lose_health(1);
                    collidable_entity->deactivate();
                }
                else if (collidable_entity->m_ai_type == SLIME) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                    //if there is a collision but the player is not attacking they lose health
                    if (m_current_animation != ATTACK) { 
                        lose_health(1);
                    }
                    else {
                        collidable_entity->lose_health(1);
                    }
                }
                else if (collidable_entity->m_entity_type == ENEMY && collidable_entity->m_ai_type == CROSSBOW) {
                    m_position.y -= y_overlap;
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_top = true;
                }
                else if (collidable_entity->m_entity_type == STAIRS) {
                    m_reached_stairs = true;
                }
                
            }
            else if (m_velocity.y < 0)
            {
                if (collidable_entity->m_entity_type == DOOR && collidable_entity->m_current_animation == CLOSED) {
                    m_position.y += y_overlap;
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    //if the player has a key open the door
                    if (keys.size() != 0) {
                        collidable_entity->set_animation_state(OPENING);
                        keys[keys.size() - 1]->deactivate();
                        keys.pop_back();
                    }
                    
                }//if we are hiting a key or a potion we collect it 
                else if (collidable_entity->m_entity_type == KEY) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    gain_key(collidable_entity);
                }
                else if (collidable_entity->m_entity_type == POTION) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    gain_potion(collidable_entity);
                }
                else if (collidable_entity->m_ai_type == SPIKE) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    if (collidable_entity->m_animation_index > 2) {
                        //if index > 2 spikes are up and not safe to pass
                        //so try to lower player health
                        lose_health(1);
                    }
                }
                else if (collidable_entity->m_ai_type == ARROW) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    lose_health(1);
                    collidable_entity->deactivate();

                }
                else if (collidable_entity->m_ai_type == SLIME) {
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                    //if there is a collision but the player is not attacking they lose health
                    if (m_current_animation != ATTACK) {
                        lose_health(1);
                    }
                    else {
                        collidable_entity->lose_health(1);
                    }
                }
                else if (collidable_entity->m_entity_type == ENEMY && collidable_entity->m_ai_type == CROSSBOW) {
                    m_position.y += y_overlap;
                    m_velocity.y = 0;
                    // Collision!
                    m_collided_bottom = true;
                }
                else if (collidable_entity->m_entity_type == STAIRS) {
                    m_reached_stairs = true;
                }
            }
        }
    }
}

void const Entity::check_collision_x(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (collidable_entity->m_is_active && check_collision(collidable_entity))
        {
            float x_distance = fabs(m_position.x - collidable_entity->m_position.x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->m_width / 2.0f));
            if (m_velocity.x > 0)
            {
                if (collidable_entity->m_entity_type == DOOR && collidable_entity->m_current_animation == CLOSED) {
                    m_position.x -= x_overlap;
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                    //if the player has a key open the door
                    if (keys.size() != 0) {
                        collidable_entity->set_animation_state(OPENING);
                        keys[keys.size() - 1]->deactivate();
                        keys.pop_back();
                    }
                }
                //if we are hiting a key or a potion we collect it 
                else if (collidable_entity->m_entity_type == KEY) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                    gain_key(collidable_entity);
                }
                else if (collidable_entity->m_entity_type == POTION) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                    gain_potion(collidable_entity);
                }
                else if (collidable_entity->m_ai_type == SPIKE) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                    if (collidable_entity->m_animation_index > 2) {
                        //if index > 2 spikes are up and not safe to pass
                        //so try to lower player health
                        lose_health(1);
                    }
                }
                else if (collidable_entity->m_ai_type == ARROW) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right= true;
                    lose_health(1);
                    collidable_entity->deactivate();

                }
                else if (collidable_entity->m_ai_type == SLIME) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                    //if there is a collision but the player is not attacking they lose health
                    if (m_current_animation != ATTACK) {
                        lose_health(1);
                    }
                    else {
                        collidable_entity->lose_health(1);
                    }
                }
                else if (collidable_entity->m_entity_type == ENEMY && collidable_entity->m_ai_type == CROSSBOW) {
                    m_position.x -= x_overlap;
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_right = true;
                }
                else if (collidable_entity->m_entity_type == STAIRS) {
                    m_reached_stairs = true;
                }
            }
            else if (m_velocity.x < 0)
            {
                if (collidable_entity->m_entity_type == DOOR && collidable_entity->m_current_animation == CLOSED) {
                    m_position.x += x_overlap;
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                    //if the player has a key open the door
                    if (keys.size() != 0) {
                        collidable_entity->set_animation_state(OPENING);
                        keys[keys.size() - 1]->deactivate();
                        keys.pop_back();
                    }
                }
                //if we are hiting a key or a potion we collect it 
                else if (collidable_entity->m_entity_type == KEY) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                    gain_key(collidable_entity);
                }
                else if (collidable_entity->m_entity_type == POTION) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                    gain_potion(collidable_entity);
                }
                else if (collidable_entity->m_ai_type == SPIKE) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left= true;
                    if (collidable_entity->m_animation_index > 2) {
                        //if index > 2 spikes are up and not safe to pass
                        //so try to lower player health
                        lose_health(1);
                    }
                }
                else if (collidable_entity->m_ai_type == ARROW) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                    lose_health(1);
                    collidable_entity->deactivate();
                }
                else if (collidable_entity->m_ai_type == SLIME) {
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                    //if there is a collision but the player is not attacking they lose health
                    if (m_current_animation != ATTACK) {
                        lose_health(1);
                    }
                    else {
                        collidable_entity->lose_health(1);
                    }
                }
                else if(collidable_entity->m_entity_type == ENEMY && collidable_entity->m_ai_type == CROSSBOW){
                    m_position.x += x_overlap;
                    m_velocity.x = 0;
                    // Collision!
                    m_collided_left = true;
                }
                else if (collidable_entity->m_entity_type == STAIRS) {
                    m_reached_stairs = true;
                }
            }
        }
    }
}

void const Entity::check_collision_y(Map* map)
{
    // Probes for tiles above
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);

    // Probes for tiles below
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    // If the map is solid, check the top three points
    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }

    // And the bottom three points
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void const Entity::check_collision_x(Map* map)
{
    // Probes for tiles; the x-checking is much simpler
    glm::vec3 left = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x < 0)
    {
        m_position.x += penetration_x;
        m_velocity.x = 0;
        m_collided_left = true;
    }
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x > 0)
    {
        m_position.x -= penetration_x;
        m_velocity.x = 0;
        m_collided_right = true;
    }
}
//------- HEALTH METHODS ------//
void Entity::lose_health(int dec) {
    //if we have passed our invincibility time and we aren't at 0 health then we can decrease health
    if (m_time_since_hit >= m_time_for_invincibility && m_health != 0) {
        //decrease health
        m_health -= dec;
        //reset our timer
        m_time_since_hit = 0.0f;
    }
}
//  GETTERS  //
glm::vec3 const Entity::get_position() const { return m_position; }
glm::vec3 const Entity::get_velocity()     const { return m_velocity; }
glm::vec3 const Entity::get_acceleration() const { return m_acceleration; }
glm::vec3 const Entity::get_movement() const { return m_movement; }
glm::vec3 const Entity::get_scale() const { return m_scale; }
float     const Entity::get_speed()        const { return m_speed; }
bool      const Entity::get_collided_top() const { return m_collided_top; }
bool      const Entity::get_collided_bottom() const { return m_collided_bottom; }
bool      const Entity::get_collided_right() const { return m_collided_right; }
bool      const Entity::get_collided_left() const { return m_collided_left; }
int       const Entity::get_health() const { return m_health; }
AIType    const Entity::get_ai_type() const { return m_ai_type; }
EntityType const Entity::get_entity_type() const { return m_entity_type; }
Animation const Entity::get_animation_state() const { return m_current_animation; }
bool      const Entity::get_reached_stairs() const { return m_reached_stairs; }
bool      const Entity::get_new_item() const { return m_got_new_item; };
//  SETTERS  //
void const Entity::set_position(glm::vec3 new_position) { m_position = new_position; }
void const Entity::set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; }
void const Entity::set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
void const Entity::set_movement(glm::vec3 new_movement) { m_movement = new_movement; }
void const Entity::set_scale(glm::vec3 new_scale) { m_scale = new_scale; }
void const Entity::set_speed(float new_speed) { m_speed = new_speed; }
void const Entity::set_jumping_power(float new_jumping_power) { m_jumping_power = new_jumping_power; }
void const Entity::set_width(float new_width) { m_width = new_width; }
void const Entity::set_height(float new_height) { m_height = new_height; }
void const Entity::set_ai_type(AIType new_ai_type) { m_ai_type = new_ai_type; };
void const Entity::set_health(int newHealth) { m_health = newHealth; };