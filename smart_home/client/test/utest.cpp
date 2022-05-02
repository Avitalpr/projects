#include "mu_test.h"
#include "temperature_sensor.hpp"
#include "smoke_sensor.hpp"
#include "sensor_manager.hpp"
#include "date_time.hpp"
#include "location.hpp"
#include "protocol.hpp"

// BEGIN_TEST(communication_test)

//     smart_home::TemperatureSensor sensor('C', "on");
//     sensor.sample();
//     sensor.notify();
//     while(true);

//     ASSERT_PASS();

// END_TEST

BEGIN_TEST(communication_test)

    using namespace smart_home;
    using Container = std::vector<std::shared_ptr<Sensor>>;
    Container sensors;
    sensors.push_back(std::move(std::make_shared<TemperatureSensor>('C', "on")));
    sensors.push_back(std::move(std::make_shared<SmokeSensor>("on")));
    
    smart_home::SensorManager sm(sensors);
    sm.run();

    // while(true);

    ASSERT_PASS();

END_TEST

BEGIN_TEST(random_float_number)

    float f = -40 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100 - -40)));
    float k = -40 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100 - -40)));
    std::cout << "randon: " << f << " " << k << "\n";

    ASSERT_PASS();

END_TEST


BEGIN_TEST(date_time_test)

    smart_home::DateTime dt(16, 30, 24, 15, 8, 2022);

    ASSERT_EQUAL(dt.hours(), 16); 
    ASSERT_EQUAL(dt.minutes(), 30); 
    ASSERT_EQUAL(dt.seconds(), 24);

    ASSERT_EQUAL(dt.day(), 15);  
    ASSERT_EQUAL(dt.month(), 8); 
    ASSERT_EQUAL(dt.year(), 2022); 

END_TEST

BEGIN_TEST(now_time_test)

    smart_home::DateTime dt;
    std::cout << "date: " << dt.toString() << "\n";

END_TEST

BEGIN_TEST(location_test)

    smart_home::Location location("2", "43");

    ASSERT_EQUAL(location.floor(), "2"); 
    ASSERT_EQUAL(location.room(), "43"); 

END_TEST


BEGIN_TEST(event_test)

    smart_home::DateTime dt(16, 30, 24, 15, 8, 2022);
    smart_home::Location location("2", "43");
    
    smart_home::Event<size_t> event(10, dt, location, "temperature");

    ASSERT_EQUAL(event.data(), 10);

END_TEST

BEGIN_TEST(pack_unpack_test)

    smart_home::DateTime dt;
    smart_home::Location location("2", "43");
    
    smart_home::Event<size_t> event(10, dt, location, "temperature");

    char buffer[256];
    protocol::pack<size_t>(event, buffer);

    std::cout << "After pack: " << buffer << "\n";


    auto e = protocol::unpack<size_t>(buffer);
    ASSERT_PASS();

    ASSERT_EQUAL(e.data(), 10);
    ASSERT_EQUAL(e.type(), "temperature");

    std::cout << "date_time: " << e.timestamp().toString() << "\n";
    std::cout << "loacation: " << e.location().toString() << "\n";

END_TEST

BEGIN_SUITE(keep it simple)
    
    TEST(communication_test)
    //TEST(random_float_number)
    //TEST(date_time_test)
    //TEST(location_test)
    //TEST(event_test)
    //TEST(now_time_test)
    // TEST(pack_unpack_test)

END_SUITE