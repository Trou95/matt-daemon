#pragma once

#include "AConfigProvider.h"
#include <string>
#include <cstdlib>

class EnvConfigProvider : public AConfigProvider {
    public:
        EnvConfigProvider(const char* KEY_PREFIX = nullptr) : AConfigProvider(E_CONFIG_PRIORITY::HIGHEST), ENV_PREFIX(KEY_PREFIX) {}
        EnvConfigProvider(std::set<Key> keys, const char* KEY_PREFIX = nullptr) : EnvConfigProvider(KEY_PREFIX) {
            this->load(keys);
        }
        ~EnvConfigProvider() = default;

        Value get(Key key) const override
        {
            auto key_with_prefix = key_include_prefix(key);
            printf("key_with prefix: %s\n", key_with_prefix);
            return getenv(key_include_prefix(key));
        }

        void set(Key key, Value value) override
        {
            auto key_with_prefix = key_include_prefix(key);
            if (value == nullptr)
            {
                #ifdef _WIN32
                    _putenv_s(key_with_prefix, "");
                #else
                    setenv(key_with_prefix, "", 1);
                #endif
                AConfigProvider::remove(key_with_prefix);
            }
            else
            {
                #ifdef _WIN32
                    _putenv_s(key_with_prefix, value);
                #else
                    setenv(key_with_prefix, value, 1);
                #endif
                AConfigProvider::set(key_with_prefix, value);
            }
        }

        void load(std::set<Key> keys)
        {
            for (auto &key : keys)
            {
                auto value = this->get(key);
                printf("Key: %s Value: %s\n", key, value);
                AConfigProvider::set(key, value);
            }
        }

        void add_key(Key key)
        {
            auto value = this->get(ENV_PREFIX != nullptr ? (std::string(ENV_PREFIX) + key).c_str() : key);
            this->set(key, value);
        }

    private:
        bool has_prefix(Key key) const
        {
            if (ENV_PREFIX == nullptr)
                return false;
                
            auto key_str = std::string(key);

            auto delimiter = key_str.find_first_of("_");
            if(delimiter == std::string::npos)
                return false;

            auto prefix = key_str.substr(0, delimiter);
            return prefix == ENV_PREFIX;
        }

        Key key_include_prefix(Key key) const
        {
            return has_prefix(key) ? key : (ENV_PREFIX != nullptr ? (std::string(ENV_PREFIX) + key).c_str() : key);
        }

        const char* ENV_PREFIX = nullptr;
};