#pragma once

#include <map>
#include <set>
#include "IConfigProvider.h"

class AConfigProvider : public IConfigProvider
{
protected:
    using Key = const char *;
    using Value = const char *;

public:
    AConfigProvider(E_CONFIG_PRIORITY priority) : PRIORITY(priority) {}
    ~AConfigProvider() = default;

    Value get(Key key) const override
    {
        return nullptr;
    }

    void set(Key key, Value value) override
    {
        m_config[key] = value;
    }

    void remove(Key key)
    {
        m_config.erase(key);
        
    }

    void load(const std::map<Key, Value> in)
    {
        m_config = in;
    }

    void load(const std::map<Key, Value>& in)
    {
        m_config = in;
    }

    void clear()
    {
        m_config.clear();
    }

    std::set<Key> keys() const
    {
        std::set<Key> keys;
        for (auto &pair : m_config)
        {
            keys.insert(pair.first);
        }
        return keys;
    }

    bool has(Key key) const
    {
        return m_config.find(key) != m_config.end();
    }

    const size_t PRIORITY;

protected:
    
    std::map<Key, Value> m_config;
};