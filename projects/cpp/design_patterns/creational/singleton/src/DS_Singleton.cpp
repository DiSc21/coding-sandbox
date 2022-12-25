#include "DS_Singleton.hpp"

std::shared_ptr<DS_Singleton> DS_Singleton::instance_ = 0;

std::shared_ptr<DS_Singleton> DS_Singleton::getInstance()
{
    if (instance_ == 0)
    {
        instance_.reset(new DS_Singleton);
    }

    return instance_;
}

