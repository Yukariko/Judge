#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

class Configuration
{
public:
    static Configuration* getInstance()
    {
        if(instance == nullptr)
            instance = new Configuration();
        return instance;
    }

    const string& getValue(const string& key)
    {
        auto val = config.find(key);
        if(val == config.end())
            return "";
        return val->second;
    }

    void setValue(const string& key, const string& val)
    {
        config[key] = val;
    }

protected:
    Configuration();
    
private:
    static Configuration* instance = nullptr;
    unordered_map<string, string> config;
}

#endif