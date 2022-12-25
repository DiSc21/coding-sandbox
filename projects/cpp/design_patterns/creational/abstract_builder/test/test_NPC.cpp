#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_Armor.hpp"

const std::pair<std::string, NPC::Type> CIVILIAN{"Old McDonald", NPC::Type::CIVILIAN};
const std::pair<std::string, NPC::Type> WARRIOR{"The Dirk Knight", NPC::Type::WARRIOR};
const std::pair<std::string, NPC::Type> WIZARD{"The Wolowizard", NPC::Type::WIZARD};

TEST(NPC, getName)
{
    const NPC civilian(CIVILIAN.first, CIVILIAN.second);
    EXPECT_EQ(CIVILIAN.first, civilian.getName());
}
TEST(NPC, getType)
{
    const NPC civilian(CIVILIAN.first, CIVILIAN.second);
    EXPECT_EQ(CIVILIAN.second, civilian.getType());
}

TEST(NPCBuilder, civilian)
{
    const auto civilian = NPCBuilder::civilian(CIVILIAN.first);
    EXPECT_EQ(CIVILIAN.first, civilian->getName());
    EXPECT_EQ(CIVILIAN.second, civilian->getType());
}

TEST(NPCBuilder, warrior)
{
    const auto warrior = NPCBuilder::warrior(WARRIOR.first);
    EXPECT_EQ(WARRIOR.first, warrior->getName());
    EXPECT_EQ(WARRIOR.second, warrior->getType());
}

TEST(NPCBuilder, wizard)
{
    const auto wizard = NPCBuilder::wizard(WIZARD.first);
    EXPECT_EQ(WIZARD.first, wizard->getName());
    EXPECT_EQ(WIZARD.second, wizard->getType());
}

TEST(NPC, getArmor)
{
    const auto civilian = NPCBuilder::civilian(CIVILIAN.first);
    const auto warrior = NPCBuilder::warrior(WARRIOR.first);
    const auto wizard = NPCBuilder::wizard(WIZARD.first);

    EXPECT_LT(civilian->getArmor().getProtection(), wizard->getArmor().getProtection());
    EXPECT_LT(wizard->getArmor().getProtection(), warrior->getArmor().getProtection());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

