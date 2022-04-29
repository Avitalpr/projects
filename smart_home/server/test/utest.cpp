#include "mu_test.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include "router.hpp"
#include "subject.hpp"
#include "controller.hpp"
#include "observer.hpp"
#include "server_manager.hpp"
#include "server.hpp"
#include <memory>
#include "reader.hpp"
#include "config_data.hpp"
#include "loader.hpp"


BEGIN_TEST(run_game)
    using namespace smart_home;
    auto ptr = std::make_shared<Router>();
    ServerManager manager(ptr);
    manager.run();

    ASSERT_PASS();


END_TEST

BEGIN_TEST(reader_test)
    using namespace smart_home;

    Reader r;
    std::ifstream file = r.open("config.txt");
    std::vector<ConfigData> res = r.read(file, '|');
    std::cout << res[0].GetConfig() << '\n';
    std::cout << res[1].GetConfig() << '\n';


    ASSERT_EQUAL(res.size(), 1);


END_TEST


BEGIN_SUITE(is a description)

    TEST(run_game)
    //TEST(reader_test)
    
END_SUITE