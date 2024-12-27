#pragma once

enum E_CONFIG_PRIORITY {
    LOWEST = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    HIGHEST = 4
};

class IConfigProvider {
    public:
        IConfigProvider() = default;
        virtual ~IConfigProvider() = default;

        virtual const char* get(const char* key) const = 0;
        virtual void set(const char* key, const char* value) = 0;
};