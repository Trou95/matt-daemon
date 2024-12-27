#include "include/utility/utility.h"
#include "include/Server.h"

#include "include/Config/ConfigManager.h"
#include "include/config/providers/EnvConfigProvider.h"

#include <iostream>

int main()
{
    /*
    Logger logger("matt_daemon.log2");
    logger.logLevel("Hello, World!", "asda");

    Server server(8080);
    server.run();

    */

    auto keys = std::set<const char *>{
        "PATH",
        "KEY2",
        "KEY3"};

    EnvConfigProvider env = EnvConfigProvider(keys, "MATT_");
    ConfigManager configManager = ConfigManager(std::make_shared<EnvConfigProvider>(env));

    auto provider = configManager.get_provider<EnvConfigProvider>();
    if(provider == nullptr) {
        std::cout << "Provider is null" << std::endl;
    }
    else {
       provider->add_key("KEY4");
    }

    return 0;
}