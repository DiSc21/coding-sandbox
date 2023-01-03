#ifndef DS_Singleton_HPP
#define DS_Singleton_HPP

#include <memory>

class DS_Singleton
{
  public:
    [[nodiscard]] static auto getInstance() -> std::shared_ptr<DS_Singleton>;

    [[nodiscard]] auto getCount() -> int { return counter_++; }

  protected:
    DS_Singleton() = default;

  private:
     static std::shared_ptr<DS_Singleton> instance_; // NOLINT cppcoreguidelines-avoid-non-const-global-variables
     int counter_{0};
};

#endif

