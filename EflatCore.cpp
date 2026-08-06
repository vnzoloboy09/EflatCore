#include "core/log/Log.h"
#include "core/Application.h"
#include "test/input/InputManagerTest.h"

class TestApp : public Eflat::Application {
public:
    using Application::Application;

    void OnFixedUpdate(float dt) override {}

    void OnRender(float alpha) override {}
};

int main()
{
    Eflat::RunInputManagerTests();

    TestApp app("EflatCore Test", 800, 600);
    if (!app.Initialize())
        return 1;
    return app.Run();
}