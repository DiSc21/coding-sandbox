//*****************************************************************************************|
//     ______ _              ____            _      ,                      _               |
//    (_) |  | |            (|   \ o        | |    /|   /         o       | |              |
//        |  | |     _       |    |    ,_   | |     |__/   _  _       __, | |   _|_        |
//      _ |  |/ \   |/      _|    ||  /  |  |/_)    | \   / |/ |  |  /  | |/ \   |         |
//     (_/   |   |_/|__/   (/\___/ |_/   |_/| \_/   |  \_/  |  |_/|_/\_/|/|   |_/|_/       |
//    *****************************************************************/|***********       |
//                                                                     \|                  |
//_________________________________________________________________________________________|
//                                                                                         |
// Copyright (c) 2023  DiSc21-Fantasies@TDK. All rights reserved.                          |
// None of the code is licensed under any License.                                         |
//_________________________________________________________________________________________|

#ifndef DS_Singleton_HPP
#define DS_Singleton_HPP

#include <memory>

/// @brief simple singleton example
class DS_Singleton
{
  public:
    /// @brief getter for single instance
    /// @return shared_ptr to singleton
    [[nodiscard]] static auto getInstance() -> std::shared_ptr<DS_Singleton>;

    /// @brief simple counter for test purposes
    /// @return number counted
    [[nodiscard]] auto getCount() -> int { return counter_++; }

  protected:
    /// @brief protected default constructor.
    DS_Singleton() = default;

  private:
    /// @brief for sharing the singleton instance
    /// @note: not thread safe implementation
    static std::shared_ptr<DS_Singleton> instance_; // NOLINT cppcoreguidelines-avoid-non-const-global-variables

    /// @brief simple conter for no reason
    int counter_{0};
};

#endif
