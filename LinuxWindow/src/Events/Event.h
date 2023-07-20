#pragma once
#include <string>

namespace MWin {
    enum class EventType
    {
        None = 0,
        KeyPress, KeyRelease,
        MousePress, MouseRelease, MouseMove,
        WindowClose, WindowResize, WindowFocus, WindowBlur
    };

    enum EventCategory {
        None = 0,
        KeyboardEventCategory = 1 << 0,
        MouseEventCategory = 1 << 1,
        ApplicationEventCategory = 1 << 2
    };

    class Event
    {
        public: 
            virtual int GetEventCategories() const = 0;
            virtual EventType GetEventType() const { return EventType::None; };
            virtual const char* GetName() const = 0;
            virtual std::string ToString() const = 0;
    };

    #define GENERATE_CATEGORY_METHOD(x) int GetEventCategories() const override { return x; }
}