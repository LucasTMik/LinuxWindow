#pragma once

#include "Event.h"
#include <sstream>

namespace MWin {
    class MouseMoveEvent : public Event
    {
        public:
            MouseMoveEvent(float mouseX, float mouseY) : m_MouseX(mouseX), m_MouseY(mouseY) {}

            inline float GetX() const { return m_MouseX; }
            inline float GetY() const { return m_MouseY; }

            std::string ToString()
            {
                std::stringstream ss;
                ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
                return ss.str();
            }
        
            virtual EventType GetEventType() const override
            {
                return EventType::MouseMove;    
            };

            virtual const char* GetName() const override
            {
                return "MouseMove";
            };

        GENERATE_CATEGORY_METHOD(MouseEventCategory)

        private:
            float m_MouseX, m_MouseY;
    };
}