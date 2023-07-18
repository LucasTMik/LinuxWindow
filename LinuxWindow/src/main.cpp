#include <iostream>
#include "Core.h"
#include "./Events/MouseEvent.h"
#include "./Events/KeyboardEvent.h"

int main()
{
    AWINDOW window(800, 600, "Hello 1");

    window.OnMouseMoveCallback([](float xpos, float ypos) 
    {
        MWin::MouseMoveEvent event(xpos, ypos);
        std::cout << event.ToString() << std::endl;
    });

    window.OnKeyPressCallback([](unsigned int keycode) 
    {
        MWin::KeyboardPress event(keycode);
        std::cout << event.ToString() << std::endl;
    });

    window.OnKeyReleaseCallback([](unsigned int keycode)
    {
        MWin::KeyboardRelease event(keycode);
        std::cout << event.ToString() << std::endl;
    });


    while(1)
    {
        window.Update();
    }

    return 0;
}