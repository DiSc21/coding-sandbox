#ifndef __DS_PROJECTILE__
#define __DS_PROJECTILE__

#include <memory>
#include <string>
#include <map>

class Projectile_
{
  public:
    /// @brief substitute for "virtual copy constructor" as c++ doesn't support that
    virtual std::shared_ptr<Projectile_> clone() const = 0;

    /// @brief some common method for projectiles
    virtual void someMethodOnHit() = 0;

    /// @brief simple getter for bullet damage 
    uint8_t getDamage() const { return damage_; }

  protected:
    /// @brief setter for damage
    void setDamage(const int16_t new_damage)
    {
        damage_ = (new_damage > 0) ? new_damage : 0;
    }

  private:
    /// @brief just some exemplary value for damage taken if hit
    uint8_t damage_{0};
};

class Arrow : public Projectile_
{
  public:

    std::shared_ptr<Projectile_> clone() const final
    {
        return std::make_shared<Arrow>(*this);
    }

    void someMethodOnHit() final { setDamage(getDamage()-5); }

    Arrow() {}
    Arrow(const Arrow& other) : Projectile_(other) { setDamage(DAMAGE); }

    static const uint8_t DAMAGE{7};
};

class Bullet : public Projectile_
{
  public:

    std::shared_ptr<Projectile_> clone() const final
    {
        return std::make_shared<Bullet>(*this);
    }

    void someMethodOnHit() final { setDamage(getDamage()-4); }

    Bullet() {}
    Bullet(const Bullet& other) : Projectile_(other) { setDamage(DAMAGE); }

    static const uint8_t DAMAGE{12};
};


class ProjectileFactory
{
    public:
      enum class Type : uint8_t
      {
          ARROW,
          BULLET
      };

      std::shared_ptr<Projectile_> create(const Type type) const
      {
          return projectile_prototypes_.at(type)->clone();
      }

    private:
      const std::map<Type, std::shared_ptr<Projectile_>> projectile_prototypes_ = {
          {Type::ARROW, std::make_shared<Arrow>()},
          {Type::BULLET, std::make_shared<Bullet>()}
      };
};



#endif

