#include <yaml-cpp/yaml.h>
#include "config.hpp"

Config Config::config = Config();

Config::Config() {
    load();
}

Config& Config::getConfig() {
    return config;
}

std::string Config::canSource() {
    return canSource_;
}

std::string Config::canDest() {
    return canDest_;
}

uint16_t Config::encryptPort() {
    return encryptPort_;
}

std::string Config::encryptHost() {
    return encryptHost_;
}

void Config::load() {
    YAML::Node config = YAML::LoadFile(configFileName);
    YAML::Node can = config["can"];
    canSource_ = can["source"].as<std::string>();
    canDest_ = can["dest"].as<std::string>();
    
    YAML::Node encrypt = config["encrypt"];
    encryptPort_ = encrypt["port"].as<uint16_t>();
    encryptHost_ = encrypt["host"].as<std::string>();
}