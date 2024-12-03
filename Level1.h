#include "Scene.h"

class Level1 : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    int ENEMY_COUNT = 18;

    // ————— DESTRUCTOR ————— //
    ~Level1();

    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};