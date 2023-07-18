#pragma once

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
        WindowEventCategory = 1 << 2
    };

    class Event
    {
        public: 
            virtual int GetEventCategories() const = 0;
            virtual EventType GetEventType() const {};
            virtual const char* GetName() const = 0;
    };

    #define GENERATE_CATEGORY_METHOD(x) int GetEventCategories() const override { return x; }
}