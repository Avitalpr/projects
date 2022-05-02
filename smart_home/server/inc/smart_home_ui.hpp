#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "device.hpp"

namespace smart_home
{
class Home
{
public:
    using Devices = std::vector<std::shared_ptr<Device>>;
    explicit Home(size_t a_height, size_t a_width, Devices& a_devices);

    void build();

private:
    void initDevices(Devices const& a_devices);

private:
    sf::RenderWindow m_window;
    Devices& m_devices;

};

} // namespace smart_home

