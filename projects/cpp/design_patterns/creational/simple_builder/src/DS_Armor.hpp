//----------------------------------------------------------------------------------------------------
//- (SIMPLE) BUILDER Pattern  ------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// The builder pattern "separates the construction of a complex object from its representation".
// - This allows to create different representations with the same construction process.
// - Construction of complex objects is done step by step and the final step returns the object.
// - The construction process is generic to be be used for creation of different representations.
//
// NOTE: This is not an official GangOfFour pattern! It's a simplified version of the Builder pattern
//       for less complex products which skips the abstract Builder and the Director class.
//----------------------------------------------------------------------------------------------------
//
// COMPONENTS:
// -----------
// - PRODUCT:
//   Product class defines type of the object to be generated by the builder pattern.
//
// - CONCRETE BUILDER(S):
//   Daughter(s) of abstract Builder. Here, steps for creation of particular products are implemented.
//
//----------------------------------------------------------------------------------------------------
//
// ADVANTAGES:
// -----------
// - Parameters for constructor are reduced providing highly readable method calls.
// - Circumvents the need for optional parameters in the constructor.
// - Object is always instantiated in a complete state.
// - Immutable objects can be build without much complex logic in the object building process.
// - Usually yields a better design flexibility
// - Usually yields a better readable code.
//----------------------------------------------------------------------------------------------------
//
// DISADVANTAGES:
// --------------
// - Number of lines of code increase to double
// - Requires a separate ConcreteBuilder for each different type of Product.
//
//----------------------------------------------------------------------------------------------------

#ifndef DS_ARMOR_HPP
#define DS_ARMOR_HPP

#include <map>
#include <numeric>
#include <set>
#include <string>

/// @brief Just a an auxiliary class used in the PRODUCT class
class SimpleArmorPart
{
  public:
    enum class Type : uint8_t
    {
        BODY,
        HEAD,
        SHOULDERS,
        ARMS,
        HANDS,
        LEGS,
        FEET,
        NONE
    };

    SimpleArmorPart() = delete;
    explicit SimpleArmorPart(const Type type, std::string name = "", uint8_t protection = 0)
        : type_(type), name_(std::move(name)), protection_(protection)
    {
    }

    auto operator<(const SimpleArmorPart &rhs) const -> bool { return (type_ < rhs.type_); }

    [[nodiscard]] auto getType() const -> Type { return type_; }
    [[nodiscard]] auto getName() const -> std::string { return name_; }
    [[nodiscard]] auto getProtection() const -> uint8_t { return protection_; }

  private:
    /// @brief const armor type
    const Type type_;

    /// @brief name of armor part
    std::string name_;
    /// @brief protection vlaue of armor part
    uint8_t protection_;
};

/// @brief the so-called PRODUCT
class SimpleArmor
{
  public:
    SimpleArmor() = default;
    explicit SimpleArmor(const std::set<SimpleArmorPart> &parts)
    {
        for (const auto &part : parts)
        {
            static_cast<void>(armor_parts_.insert({part.getType(), part}));
        }
    }

    [[nodiscard]] auto getTypeProtection(const SimpleArmorPart::Type type) const -> uint8_t
    {
        const auto &part_it = armor_parts_.find(type);
        return (part_it != armor_parts_.end()) ? part_it->second.getProtection() : 0;
    }

    [[nodiscard]] auto getProtection() const -> uint16_t
    {
        // clang-format off
        return std::accumulate(std::begin(armor_parts_), std::end(armor_parts_), 0,
                               [](const std::uint16_t sum, const auto &part) { return sum + part.second.getProtection(); });
        // clang-format on
    }

  private:
    std::map<SimpleArmorPart::Type, SimpleArmorPart> armor_parts_{};
};

/// @brief the so-called BUILDER
class SimpleArmorBuilder
{
    // just for clang complaining about magic numbers down there
    static const uint8_t MAGIC_1  = 1;
    static const uint8_t MAGIC_3  = 3;
    static const uint8_t MAGIC_4  = 4;
    static const uint8_t MAGIC_5  = 5;
    static const uint8_t MAGIC_7  = 6;
    static const uint8_t MAGIC_12 = 12;

  public:
    static auto civilian() -> SimpleArmor
    {
        return SimpleArmor({SimpleArmorPart(SimpleArmorPart::Type::BODY, "Plain Shirt", MAGIC_1),
                            SimpleArmorPart(SimpleArmorPart::Type::LEGS, "Cloth trousers", MAGIC_1),
                            SimpleArmorPart(SimpleArmorPart::Type::FEET, "Simple Shoes", MAGIC_1)});
    }
    static auto warrior() -> SimpleArmor
    {
        return SimpleArmor({SimpleArmorPart(SimpleArmorPart::Type::BODY, "Leather Chest Protector", MAGIC_12),
                            SimpleArmorPart(SimpleArmorPart::Type::HEAD, "Leather Helmet", MAGIC_7),
                            SimpleArmorPart(SimpleArmorPart::Type::LEGS, "Bavarian Leather Trousers", MAGIC_5),
                            SimpleArmorPart(SimpleArmorPart::Type::HANDS, "Leather Gloves", MAGIC_4),
                            SimpleArmorPart(SimpleArmorPart::Type::FEET, "Leather Boots", MAGIC_3)});
    }
    static auto wizard() -> SimpleArmor
    {
        return SimpleArmor({SimpleArmorPart(SimpleArmorPart::Type::BODY, "Magic Rope", MAGIC_4),
                            SimpleArmorPart(SimpleArmorPart::Type::HEAD, "Pointed Hat", MAGIC_3),
                            SimpleArmorPart(SimpleArmorPart::Type::LEGS, "Long Underpants", MAGIC_1),
                            SimpleArmorPart(SimpleArmorPart::Type::FEET, "Slipers", MAGIC_1)});
    }
};

#endif
