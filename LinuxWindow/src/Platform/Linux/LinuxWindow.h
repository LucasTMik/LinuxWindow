#pragma once
#include "../../AWindow.h"
#include <X11/Xlib.h>
#include <functional>

namespace MWin {
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowData
    {
        unsigned int Width;
        unsigned int Height;
        std::string Name;
        EventCallbackFn Callback;
    };

    class LinuxWindow : public AWindow
    {
        public:
            LinuxWindow(const AWindowProps props);
            ~LinuxWindow();

            void OnUpdate() override;
            virtual void SetEventCallback(const EventCallbackFn& func) override;
            virtual unsigned int GetWidth() const override;
            virtual unsigned int GetHeight() const override;
        private:
            void Init(const AWindowProps props);
            void HandleWindowEvents();
            Display* m_Display;
            Window m_Window;
            WindowData m_Data;
    };
}