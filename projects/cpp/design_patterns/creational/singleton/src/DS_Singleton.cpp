#include "DS_Singleton.hpp"

std::shared_ptr<DS_Singleton> DS_Singleton::instance_ = nullptr; // NOLINT cppcoreguidelines-avoid-non-const-global-variables

[[nodiscard]] auto DS_Singleton::getInstance() -> std::shared_ptr<DS_Singleton>
{
    if (instance_ == nullptr)
    {
        instance_.reset(new DS_Singleton); // NOLINT cppcoreguidelines-owning-memory
    }

    return instance_;
}
