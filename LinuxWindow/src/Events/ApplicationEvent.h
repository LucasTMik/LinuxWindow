#pragma once

#include "Event.h"
#include <sstream>

namespace MWin {

    class ResizeEvent : public Event
    {
        public:
            ResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
            unsigned int GetWidth() const
            {
                return m_Width;
            }

            unsigned int GetHeight() const
            {
                return m_Height;
            }

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetName() << ": " << m_Width << "x" << m_Height;
                return ss.str();
            }

            virtual const char* GetName() const override 
            {
                return "WindowResize";
            }

            GENERATE_CATEGORY_METHOD(ApplicationEventCategory)
        private:
            unsigned int m_Width;
            unsigned int m_Height;
    };
}