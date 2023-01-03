#ifndef DS_NPC_HPP
#define DS_NPC_HPP

#include <map>
#include <memory>
#include <string>

#include "DS_Armor.hpp"

class SimpleNPC
{
  public:
    enum class Type : uint8_t
    {
        CIVILIAN,
        WARRIOR,
        WIZARD
    };

    SimpleNPC(std::string name, const Type type, SimpleArmor armor = {})
        : name_(std::move(name)), type_(type), armor_(std::move(armor))
    {
    }

    [[nodiscard]] auto getName()  const -> std::string { return name_; }
    [[nodiscard]] auto getType()  const -> Type        { return type_; }
    [[nodiscard]] auto getArmor() const -> SimpleArmor { return armor_; }

  private:
    const std::string name_;
    const Type        type_;

    SimpleArmor armor_;
};

class SimpleNPCBuilder
{
  public:
    [[nodiscard]] static auto civilian(const std::string& name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::CIVILIAN, SimpleArmorBuilder::civilian());
    }

    [[nodiscard]] static auto warrior(const std::string& name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::WARRIOR, SimpleArmorBuilder::warrior());
    }

    [[nodiscard]] static auto wizard(const std::string& name) -> std::shared_ptr<SimpleNPC>
    {
        return std::make_shared<SimpleNPC>(name, SimpleNPC::Type::WIZARD, SimpleArmorBuilder::wizard());
    }
};


#endif

