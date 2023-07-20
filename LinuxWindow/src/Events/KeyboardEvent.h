#include "Event.h"
#include <sstream>

namespace MWin {
    class KeyEvent : public Event
    {
        public:
            unsigned int GetKeyCode() const { return m_KeyCode; };

            virtual std::string ToString() const = 0;

            GENERATE_CATEGORY_METHOD(KeyboardEventCategory)
        protected:
            KeyEvent(unsigned int code) : m_KeyCode(code) {}
            unsigned int m_KeyCode;
    };

    class KeyboardPress : public KeyEvent 
    {
        public:
            KeyboardPress(unsigned int keycode) : KeyEvent(keycode) {}

            virtual const char* GetName() const override
            {
                return "KeyPress";
            }

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetName() << ": " << m_KeyCode;
                return ss.str();
            }
    };

    class KeyboardRelease : public KeyEvent 
    {
        public:
            KeyboardRelease(unsigned int keycode) : KeyEvent(keycode) {}

            virtual const char* GetName() const override
            {
                return "KeyRelease";
            }

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetName() << ": " << m_KeyCode;
                return ss.str();
            }
    };
}