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


TEST(ArmorBuilder_Civilian, getTypeProtection)
{
    const auto armor = ArmorBuilder_Civilian().buildArmor();

    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::BODY));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::LEGS));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::FEET));
    EXPECT_EQ(0, armor.getTypeProtection(ArmorPart::Type::HANDS));
}
TEST(ArmorBuilder_Warrior, getTypeProtection)
{
    const auto armor = ArmorBuilder_Warrior().buildArmor();

    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::BODY));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::LEGS));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::FEET));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::HANDS));
}
TEST(ArmorBuilder_Wizard, getTypeProtection)
{
    const auto armor = ArmorBuilder_Wizard().buildArmor();

    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::BODY));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::LEGS));
    EXPECT_LT(0, armor.getTypeProtection(ArmorPart::Type::FEET));
    EXPECT_EQ(0, armor.getTypeProtection(ArmorPart::Type::HANDS));
}


TEST(ArmorBuilder_Civilian, getProtection)
{
    const auto armor = ArmorBuilder_Civilian().buildArmor();
    EXPECT_LT(armor.getTypeProtection(ArmorPart::Type::BODY), armor.getProtection());
}
TEST(ArmorBuilder_Warrior, getProtection)
{
    const auto armor = ArmorBuilder_Warrior().buildArmor();
    EXPECT_LT(armor.getTypeProtection(ArmorPart::Type::BODY), armor.getProtection());
}
TEST(ArmorBuilder_Wizard, getProtection)
{
    const auto armor = ArmorBuilder_Wizard().buildArmor();
    EXPECT_LT(armor.getTypeProtection(ArmorPart::Type::BODY), armor.getProtection());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

