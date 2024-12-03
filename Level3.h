#include "Scene.h"

class Level3 : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    int ENEMY_COUNT = 20;

    // ————— DESTRUCTOR ————— //
    ~Level3();

    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};