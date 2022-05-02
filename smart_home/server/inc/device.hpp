#pragma once

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <memory>

namespace smart_home
{

class Status
{

public:
    explicit Status(std::string const& a_texture = " ", float xScale = 1, float yScale = 1, float xPos = 0, float yPos = 0);
    void draw(sf::RenderWindow& a_window);

    void on();
    void off();
    
private:
    sf::Texture m_texture;
    sf::Sprite m_status;

};



class Device
{
public:
    explicit Device(std::string const& a_texture = " ", float xScale = 1, float yScale = 1, float xPos = 0, float yPos = 0);
    void draw(sf::RenderWindow& a_window);

    void turnOn();
    void turnOff();
    Status m_status;

private: 
    sf::Texture m_texture;
    sf::Sprite m_device;

};


} // namespace smart_home