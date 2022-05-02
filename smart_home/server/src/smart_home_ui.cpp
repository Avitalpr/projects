#include "smart_home_ui.hpp"

#include <unistd.h>

namespace smart_home
{

Home::Home(size_t a_height, size_t a_width, Devices& a_devices)
: m_window(sf::VideoMode(a_height, a_width), "Bar and Avital's building")
, m_devices(a_devices)
{}

void Home::initDevices(Devices const& a_devices)
{
    for(auto& d : a_devices)
    {
        d->draw(m_window);
    }
}



void Home::build()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window.close();
        }
        m_window.clear();
        initDevices(m_devices);
        m_window.display();
    }
}

} // namespace smart_home
