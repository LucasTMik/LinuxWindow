#pragma once
#include "functional"
#include "Events/Event.h"
#include <string>

#define MOUSE_MOVE_CALLBACK void(float xpos, float ypos)
#define KEY_CALLBACK        void(float keycode)


namespace MWin {
    using EventCallback = std::function<void(Event&)>;

    struct AWindowProps {
        unsigned int Width;
        unsigned int Height;
        std::string Name;

        AWindowProps(unsigned int wwidth = 600, unsigned int wheight = 800, const std::string& wname = "Hello Window")
        : Width(wwidth), Height(wheight), Name(wname)
        {};
    };

    class AWindow {
        public:
            static AWindow* Create(const AWindowProps& props = AWindowProps());
            virtual void OnUpdate() = 0;
            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;
            virtual bool IsRunning() const = 0;
            virtual void SetEventCallback(const EventCallback& func) = 0;
    };
}