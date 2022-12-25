#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_Armor.hpp"

const ArmorPart::Type ARMOR_TYPE = ArmorPart::Type::FEET;
const std::string     ARMOR_NAME = "Simple Shoes";
const uint8_t         PROTECTION = 1;

const ArmorPart   simple_shoes(ARMOR_TYPE, ARMOR_NAME, PROTECTION);

TEST(ArmorPart, getType)
{
    EXPECT_EQ(ARMOR_TYPE, simple_shoes.getType());
}
TEST(ArmorPart, getName)
{
    EXPECT_EQ(ARMOR_NAME, simple_shoes.getName());
}
TEST(ArmorPart, getProtection)
{
    EXPECT_EQ(PROTECTION, simple_shoes.getProtection());
}


TEST(ArmorBuilder, getTypeProtection)
{
    const auto civilian = ArmorBuilder::civilian();
    const auto warrior  = ArmorBuilder::warrior();
    const auto wizard   = ArmorBuilder::wizard();

    EXPECT_LT(civilian.getTypeProtection(ArmorPart::Type::BODY), wizard.getTypeProtection(ArmorPart::Type::BODY));
    EXPECT_LT(wizard.getTypeProtection(ArmorPart::Type::BODY), warrior.getTypeProtection(ArmorPart::Type::BODY));
}

TEST(ArmorBuilder, getProtection)
{
    const auto civilian = ArmorBuilder::civilian();
    const auto warrior  = ArmorBuilder::warrior();
    const auto wizard   = ArmorBuilder::wizard();

    EXPECT_LT(civilian.getProtection(), wizard.getProtection());
    EXPECT_LT(wizard.getProtection(), warrior.getProtection());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

