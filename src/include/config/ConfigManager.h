#pragma once

#include <vector>
#include <memory>
#include <stdexcept>
#include "providers/AConfigProvider.h"

class ConfigManager
{
public:
    ConfigManager(std::shared_ptr<AConfigProvider> provider)
        : m_providers({provider}) {}

    ConfigManager(std::vector<std::shared_ptr<AConfigProvider>> providers)
        : m_providers(std::move(providers)) {}

    ~ConfigManager() = default;

    template <typename T>
    T *get_provider()
    {
        for (auto &provider : m_providers)
        {
            if (dynamic_cast<T *>(provider.get()))
            {
                return dynamic_cast<T *>(provider.get());
            }
        }
        throw std::runtime_error("Provider not found");
    }

private:
    std::vector<std::shared_ptr<AConfigProvider>> m_providers;
};
