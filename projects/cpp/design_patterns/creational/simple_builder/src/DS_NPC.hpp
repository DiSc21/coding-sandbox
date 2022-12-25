#ifndef __DS_NPC__
#define __DS_NPC__

#include <map>
#include <memory>
#include <string>

#include "DS_Armor.hpp"

class NPC
{
  public:
    enum class Type : uint8_t
    {
        CIVILIAN,
        WARRIOR,
        WIZARD
    };

    NPC(const std::string& name, const Type type, const Armor& armor = {})
        : name_(name), type_(type), armor_(armor)
    {
    }

    std::string getName() const { return name_; }
    Type  getType()       const { return type_; }
    Armor getArmor()      const { return armor_; }

  private:
    const std::string name_;
    const Type        type_;

    Armor armor_;
};

class NPCBuilder
{
  public:
    static std::shared_ptr<NPC> civilian(const std::string& name)
    {
        return std::make_shared<NPC>(name, NPC::Type::CIVILIAN, ArmorBuilder::civilian());
    }

    static std::shared_ptr<NPC> warrior(const std::string& name)
    {
        return std::make_shared<NPC>(name, NPC::Type::WARRIOR, ArmorBuilder::warrior());
    }

    static std::shared_ptr<NPC> wizard(const std::string& name)
    {
        return std::make_shared<NPC>(name, NPC::Type::WIZARD, ArmorBuilder::wizard());
    }
};


#endif

