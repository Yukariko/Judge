#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <iostream>
#include <unordered_map>

using namespace std;

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
        return config[key];
    }

    void setValue(const string& key, const string& val)
    {
        config[key] = val;
    }

protected:
    Configuration(){}
    
private:
    static Configuration* instance;
    unordered_map<string, string> config;
};

#endif