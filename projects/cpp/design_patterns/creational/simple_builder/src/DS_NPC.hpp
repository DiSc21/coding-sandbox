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

#ifndef DS_NPC_HPP
#define DS_NPC_HPP

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "DS_Armor.hpp"

/// @brief simple NPC struct
class SimpleNPC
{
  public:
    /// @brief enum for warrior/wizard/civilian npc
    enum class Type : uint8_t
    {
        CIVILIAN,
        WARRIOR,
        WIZARD
    };

    /// @brief parameterized NPC constructor
    /// @param name of the NPC
    /// @param type of the NPC
    /// @param armor of the NPC
    SimpleNPC(std::string name, const Type type, SimpleArmor armor = {})
        : name_(std::move(name)), type_(type), armor_(std::move(armor))
    {
    }

    /// @brief name getter
    /// @return name of NPC
    [[nodiscard]] auto getName() const -> std::string { return name_; }
    /// @brief type getter
    /// @return type of NPC
    [[nodiscard]] auto getType() const -> Type { return type_; }
    /// @brief Armor getter
    /// @return Armor of NPC
    [[nodiscard]] auto getArmor() const -> SimpleArmor { return armor_; }

  private:
    const std::string name_;  ///> name of the NPC
    const Type        type_;  ///> type of the NPC
    SimpleArmor       armor_; ///> armor of the NPC
};

/// @brief just a simple collection of functions for creation of different NPC types
class SimpleNPCBuilder
{
  public:
    /// @brief function building a civilian NPC with civilian Armor
    /// @param name of the NPC
    /// @return shared_ptr to freshly build NPC
    [[nodiscard]] static auto civilian(const std::string &name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::CIVILIAN, SimpleArmorBuilder::civilian());
    }

    /// @brief function building a warrior NPC with civilian Armor
    /// @param name of the NPC
    /// @return shared_ptr to freshly build NPC
    [[nodiscard]] static auto warrior(const std::string &name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::WARRIOR, SimpleArmorBuilder::warrior());
    }

    /// @brief function building a wizard NPC with civilian Armor
    /// @param name of the NPC
    /// @return shared_ptr to freshly build NPC
    [[nodiscard]] static auto wizard(const std::string &name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::WIZARD, SimpleArmorBuilder::wizard());
    }
};


#endif
