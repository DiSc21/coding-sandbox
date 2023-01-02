#include <gtest/gtest.h>
#include <iostream>
#include <numeric>
#include <memory>

#include "../src/DS_Prototype.hpp"


TEST(Projectile_, getDamage) // NOLINT
{
    const ProjectileFactory projectile_factory;

    const auto& arrow = projectile_factory.create(ProjectileFactory::Type::ARROW);
    const auto& bullet = projectile_factory.create(ProjectileFactory::Type::BULLET);

    EXPECT_EQ(0+Arrow::DAMAGE, arrow->getDamage());
    EXPECT_EQ(0+Bullet::DAMAGE, bullet->getDamage());
}


TEST(Projectile_, someMethodOnHit) // NOLINT
{
    const ProjectileFactory projectile_factory;

    std::set<std::shared_ptr<Projectile_>> projectiles = {
        projectile_factory.create(ProjectileFactory::Type::ARROW),
        projectile_factory.create(ProjectileFactory::Type::BULLET)
    };

    uint8_t damage_sum = 0; 
    const uint8_t max_bounces = 5;
    for(uint8_t i=0; i<max_bounces; i++)
    {
        damage_sum = 0; 
        for(const auto& proj: projectiles)
        {
            proj->someMethodOnHit();
            damage_sum += proj->getDamage();
        }
    }
    EXPECT_EQ(uint8_t(0), uint8_t(damage_sum));
}


TEST(ProjectileFactory, create) // NOLINT
{
    const ProjectileFactory projectile_factory;

    std::set<std::shared_ptr<Projectile_>> projectiles = {
        projectile_factory.create(ProjectileFactory::Type::ARROW),
        projectile_factory.create(ProjectileFactory::Type::BULLET)
    };

    uint8_t damage_sum = std::accumulate(projectiles.begin(), projectiles.end(), 0,
                                         [&](uint8_t sum, const std::shared_ptr<Projectile_>& contrib)
                                         { return sum + contrib->getDamage(); }
                                        );

    EXPECT_EQ(uint8_t(damage_sum), uint8_t(Bullet::DAMAGE+Arrow::DAMAGE));
}



int main(int argc, char** argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

