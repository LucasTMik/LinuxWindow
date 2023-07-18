#pragma once
#include "../../AWindow.h"
#include <X11/Xlib.h>
#include <functional>

namespace MWin {
    class LinuxWindow : public AWindow
    {
        public:
            LinuxWindow(unsigned int width = 800, unsigned int height = 500, const char* name = nullptr);
            ~LinuxWindow();

            void Update() override;
        private:
            Display* m_Display;
            int m_Screen;
            Window m_Window;
            XEvent m_Event;

            
    };
}