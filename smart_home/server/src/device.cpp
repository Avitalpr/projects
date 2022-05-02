#include "device.hpp"
#include <iostream>

namespace smart_home
{
Status::Status(std::string const& a_texture, float xScale, float yScale, float xPos, float yPos)
{
    m_texture.loadFromFile(a_texture);
    m_status.setTexture(m_texture);
    m_status.setScale(xScale, yScale);
    m_status.setPosition(xPos, yPos);
}

void Status::draw(sf::RenderWindow& a_window)
{
    a_window.draw(m_status);
}

void Status::on()
{
    m_texture.loadFromFile("sources/on.jpeg");
}

void Status::off()
{
    m_texture.loadFromFile("sources/off.jpeg");
}

Device::Device(std::string const& a_texture, float xScale, float yScale, float xPos, float yPos)
: m_status("sources/off.jpeg", 0.5, 0.5, xPos + 300, yPos + 30)
{
    m_texture.loadFromFile(a_texture);
    m_device.setTexture(m_texture);
    m_device.setScale(xScale, yScale);
    m_device.setPosition(xPos, yPos);
}

void Device::draw(sf::RenderWindow& a_window)
{
    a_window.draw(m_device);
    m_status.draw(a_window);
}

void Device::turnOn()
{
    m_status.on();
}

void Device::turnOff()
{
    m_status.off();
}

} // namespace smart_home

