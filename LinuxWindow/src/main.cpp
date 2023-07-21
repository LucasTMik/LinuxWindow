#include <iostream>
#include "AWindow.h"
#include "./Events/Event.h"
#include "glad/glad.h"
#include "Core.h"

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace MWin {
    class Application
    {
        public:
            void OnEvent(Event& event) 
            {
                // std::cout << event.ToString() << std::endl;
            }

            void Run()
            {
                AWindow* window = AWindow::Create({800, 640, "Hello window"});

                window->SetEventCallback(BIND_FN(Application::OnEvent));

                ASSERT(gladLoadGL());

                while(window->IsRunning())
                {
                    window->OnUpdate();

                    glClear(GL_COLOR_BUFFER_BIT);
                    glClearColor(0.4f, 0.3f, 0.3f, 1.0f);
                }

                delete window;
            }
    };
}

int main()
{
    MWin::Application app;
    app.Run();

    return 0;
}
