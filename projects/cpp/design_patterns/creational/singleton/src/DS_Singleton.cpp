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

#include "DS_Singleton.hpp"

std::shared_ptr<DS_Singleton> DS_Singleton::instance_ = nullptr; // NOLINT cppcoreguidelines-avoid-non-const-global-variables

[[nodiscard]] auto DS_Singleton::getInstance() -> std::shared_ptr<DS_Singleton>
{
    if ( instance_ == nullptr )
    {
        instance_.reset(new DS_Singleton); // NOLINT cppcoreguidelines-owning-memory
    }

    return instance_;
}
