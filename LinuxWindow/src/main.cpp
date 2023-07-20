#include <iostream>
#include "AWindow.h"
#include "./Events/Event.h"


#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace MWin {
    class Application
    {
        public:
            void OnEvent(Event& event) 
            {
                std::cout << event.ToString() << std::endl;
            }

            void Run()
            {
                AWindow* window = AWindow::Create();

                window->SetEventCallback(BIND_FN(Application::OnEvent));

                while(1)
                {
                    window->OnUpdate();
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
