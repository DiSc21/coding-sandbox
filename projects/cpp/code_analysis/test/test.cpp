// NOLINTBEGIN
#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_FactoryMethod.hpp"


class TestFacMeth
{
  public:
    static std::vector<std::shared_ptr<ObjectBase_>> createObjects()
    {
        std::vector<std::shared_ptr<ObjectBase_>> objects;
        static_cast<void>(objects.emplace_back(ObjectHandler::createObject<ObjectOne>()));
        static_cast<void>(objects.emplace_back(ObjectHandler::createObject<ObjectTwo>()));

        return objects;
    }
};

TEST(ObjectBase_, disable)
{
    auto objects = TestFacMeth::createObjects();
    for (auto obj_ptr: objects)
    {
        obj_ptr->enable();
        obj_ptr->disable();
        EXPECT_FALSE(obj_ptr->isUsed());
    }
}
TEST(ObjectBase_, enable)
{
    auto objects = TestFacMeth::createObjects();
    for (auto obj_ptr: objects)
    {
        obj_ptr->disable();
        obj_ptr->enable();
        EXPECT_TRUE(obj_ptr->isUsed());
    }
}


TEST(ObjectHandler, createObjects)
{
    auto objects = TestFacMeth::createObjects();
    EXPECT_EQ(2, objects.size());
}
TEST(ObjectBase_, doWhatNeedsToBeDone)
{
    auto objects = TestFacMeth::createObjects();

    std::set<uint16_t> valid_nums{1,2};

    for (auto obj_ptr: objects)
    {
        const auto num = obj_ptr->doWhatNeedsToBeDone();
        EXPECT_TRUE(valid_nums.find(num) != valid_nums.end());
        valid_nums.erase(num);
    }
        
    EXPECT_EQ(0, valid_nums.size());
}


TEST(ObjectHandler, doWhatNeedsToBeDone)
{
    ObjectHandler obj_handler; 

    EXPECT_EQ(uint8_t(2), obj_handler.doWhatNeedsToBeDone());
}
TEST(ObjectHandler, processReturnHorsts)
{
    ObjectHandler objects;
    std::vector<bool> vec{};
    objects.processReturnHorsts(vec);

    uint8_t num_enabled = 0;
    uint8_t num_disabled = 0;
    for(const auto& is_used: vec)
    {
         (is_used) ? ++num_enabled : ++num_disabled;
    }
    
    EXPECT_EQ(uint8_t(1), uint8_t(vec.size()));
    EXPECT_EQ(uint8_t(1), num_enabled);
    EXPECT_EQ(uint8_t(0), num_disabled);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// NOLINTEND
