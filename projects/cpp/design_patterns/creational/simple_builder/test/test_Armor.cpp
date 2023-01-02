#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_Armor.hpp"

const SimpleArmorPart::Type ARMOR_TYPE = SimpleArmorPart::Type::FEET;
const std::string           ARMOR_NAME = "Simple Shoes";
const uint8_t               PROTECTION = 1;

const SimpleArmorPart simple_shoes(ARMOR_TYPE, ARMOR_NAME, PROTECTION);

TEST(SimpleArmorPart, getType) // NOLINT
{
    EXPECT_EQ(ARMOR_TYPE, simple_shoes.getType());
}
TEST(SimpleArmorPart, getName) // NOLINT
{
    EXPECT_EQ(ARMOR_NAME, simple_shoes.getName());
}
TEST(SimpleArmorPart, getProtection) // NOLINT
{
    EXPECT_EQ(PROTECTION, simple_shoes.getProtection());
}


TEST(SimpleArmorBuilder, getTypeProtection) // NOLINT
{
    const auto civilian = SimpleArmorBuilder::civilian();
    const auto warrior  = SimpleArmorBuilder::warrior();
    const auto wizard   = SimpleArmorBuilder::wizard();

    EXPECT_LT(civilian.getTypeProtection(SimpleArmorPart::Type::BODY), wizard.getTypeProtection(SimpleArmorPart::Type::BODY));
    EXPECT_LT(wizard.getTypeProtection(SimpleArmorPart::Type::BODY), warrior.getTypeProtection(SimpleArmorPart::Type::BODY));
}

TEST(SimpleArmorBuilder, getProtection) // NOLINT
{
    const auto civilian = SimpleArmorBuilder::civilian();
    const auto warrior  = SimpleArmorBuilder::warrior();
    const auto wizard   = SimpleArmorBuilder::wizard();

    EXPECT_LT(civilian.getProtection(), wizard.getProtection());
    EXPECT_LT(wizard.getProtection(), warrior.getProtection());
}

int main(int argc, char** argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

