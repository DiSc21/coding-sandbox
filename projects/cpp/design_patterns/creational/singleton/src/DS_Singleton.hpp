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
    /// @brief for sharing the singleton instance
    /// @note: not thread safe implementation
    static std::shared_ptr<DS_Singleton> instance_; // NOLINT cppcoreguidelines-avoid-non-const-global-variables

    /// @brief simple conter for no reason
    int counter_{0};
};

#endif
