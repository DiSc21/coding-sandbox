#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_NPC.hpp"

const std::pair<std::string, SimpleNPC::Type> CIVILIAN{"Old McDonald", SimpleNPC::Type::CIVILIAN};
const std::pair<std::string, SimpleNPC::Type> WARRIOR{"The Dirk Knight", SimpleNPC::Type::WARRIOR};
const std::pair<std::string, SimpleNPC::Type> WIZARD{"The Wolowizard", SimpleNPC::Type::WIZARD};

TEST(SimpleNPC, getName) // NOLINT
{
    const SimpleNPC civilian(CIVILIAN.first, CIVILIAN.second);
    EXPECT_EQ(CIVILIAN.first, civilian.getName());
}
TEST(SimpleNPC, getType) // NOLINT
{
    const SimpleNPC civilian(CIVILIAN.first, CIVILIAN.second);
    EXPECT_EQ(CIVILIAN.second, civilian.getType());
}

TEST(SimpleNPCBuilder, civilian) // NOLINT
{
    const auto civilian = SimpleNPCBuilder::civilian(CIVILIAN.first);
    EXPECT_EQ(CIVILIAN.first, civilian->getName());
    EXPECT_EQ(CIVILIAN.second, civilian->getType());
}

TEST(SimpleNPCBuilder, warrior) // NOLINT
{
    const auto warrior = SimpleNPCBuilder::warrior(WARRIOR.first);
    EXPECT_EQ(WARRIOR.first, warrior->getName());
    EXPECT_EQ(WARRIOR.second, warrior->getType());
}

TEST(SimpleNPCBuilder, wizard) // NOLINT
{
    const auto wizard = SimpleNPCBuilder::wizard(WIZARD.first);
    EXPECT_EQ(WIZARD.first, wizard->getName());
    EXPECT_EQ(WIZARD.second, wizard->getType());
}

TEST(SimpleNPC, getArmor) // NOLINT
{
    const auto civilian = SimpleNPCBuilder::civilian(CIVILIAN.first);
    const auto warrior = SimpleNPCBuilder::warrior(WARRIOR.first);
    const auto wizard = SimpleNPCBuilder::wizard(WIZARD.first);

    EXPECT_LT(civilian->getArmor().getProtection(), wizard->getArmor().getProtection());
    EXPECT_LT(wizard->getArmor().getProtection(), warrior->getArmor().getProtection());
}

int main(int argc, char** argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

