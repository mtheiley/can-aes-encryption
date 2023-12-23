#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

class Config {
public:
    static Config& getConfig();
    std::string canSource();
    std::string canDest();
    uint16_t encryptPort();
    std::string encryptHost();

private:
    Config();
    void load();

    std::string configFileName = "config.yaml";
    static Config config;

    std::string canSource_ = "";
    std::string canDest_ = "";
    uint16_t encryptPort_ = 0;
    std::string encryptHost_ = "";
};

#endif //CONFIG_H