#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_FactoryMethod.hpp"

/// @brief simple aux class for testing
class TestFacMeth // NOLINT
{
  public:
    /// @brief simple aux function for creation of Objects
    /// @return vector of shared_ptrs of created objects
    static auto createObjects() -> std::vector<std::shared_ptr<ObjectBase_>>
    {
        std::vector<std::shared_ptr<ObjectBase_>> objects;
        static_cast<void>(objects.emplace_back(ObjectHandler::createObject<ObjectOne>()));
        static_cast<void>(objects.emplace_back(ObjectHandler::createObject<ObjectTwo>()));

        return objects;
    }
};


TEST(ObjectBase_, disable) // NOLINT
{
    ObjectOne obj = ObjectOne();

    obj.enable();
    obj.disable();
    EXPECT_FALSE(obj.isUsed());
}


TEST(ObjectBase_, enable) // NOLINT
{
    ObjectTwo obj = ObjectTwo();

    obj.disable();
    obj.enable();
    EXPECT_TRUE(obj.isUsed());
}


TEST(ObjectHandler, createObjects) // NOLINT
{
    auto objects = TestFacMeth::createObjects();
    EXPECT_EQ(2, objects.size());
}

TEST(ObjectBase_, doWhatNeedsToBeDone) // NOLINT
{
    auto objects = TestFacMeth::createObjects();

    std::set<uint16_t> valid_nums{1, 2};

    for ( const auto &obj_ptr : objects )
    {
        const auto num = obj_ptr->doWhatNeedsToBeDone();
        EXPECT_TRUE(valid_nums.find(num) != valid_nums.end());
        valid_nums.erase(num);
    }

    EXPECT_EQ(0, valid_nums.size());
}


TEST(ObjectHandler, doWhatNeedsToBeDone) // NOLINT
{
    ObjectHandler obj_handler;

    EXPECT_EQ(uint8_t(2), obj_handler.doWhatNeedsToBeDone());
}

TEST(ObjectHandler, processReturnHorsts) // NOLINT
{
    ObjectHandler     objects;
    std::vector<bool> vec{};
    objects.processReturnHorsts(vec);

    uint8_t num_enabled  = 0;
    uint8_t num_disabled = 0;
    for ( const auto &is_used : vec )
    {
        (is_used) ? ++num_enabled : ++num_disabled;
    }

    EXPECT_EQ(uint8_t(1), uint8_t(vec.size()));
    EXPECT_EQ(uint8_t(1), num_enabled);
    EXPECT_EQ(uint8_t(0), num_disabled);
}


int main(int argc, char **argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
