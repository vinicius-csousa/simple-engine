#include <iostream>
#include "Engine.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
    Engine::GetInstance()->Init();

    while (Engine::GetInstance()->IsRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clear();

    return 0;
}
