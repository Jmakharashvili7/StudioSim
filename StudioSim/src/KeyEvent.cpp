#include "KeyEvent.h"

KeyEvent::KeyEvent() : m_Type(), m_Key(0u)
{
}

KeyEvent::KeyEvent(const EventType type, const unsigned char key) : m_Type(type), m_Key(key)
{
}

bool KeyEvent::IsPressed() const
{
    return m_Type == EventType::PRESS;
}

bool KeyEvent::IsReleased() const
{
    return m_Type == EventType::RELEASE;
}

bool KeyEvent::IsValid() const
{
    return m_Type != EventType::INVALID;
}

unsigned char KeyEvent::GetKeyCode() const
{
    return m_Key;
}
