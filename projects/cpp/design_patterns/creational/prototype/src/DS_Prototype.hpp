#ifndef DS_PROJECTILE_HPP
#define DS_PROJECTILE_HPP

#include <memory>
#include <string>
#include <map>

class Projectile_
{
  public:
    Projectile_()                         = default;
    Projectile_(const Projectile_ &other) = default;
    Projectile_(Projectile_&& other)      = default;

    auto operator=(const Projectile_& /*other*/) -> Projectile_& = default;
    auto operator=(Projectile_&& other) noexcept -> Projectile_&
    {
        damage_ = other.damage_;
        return *this;
    }
    virtual ~Projectile_() = default;


    /// @brief substitute for "virtual copy constructor" as c++ doesn't support that
    [[nodiscard]] virtual auto clone() const -> std::shared_ptr<Projectile_> = 0;

    /// @brief some common method for projectiles
    virtual void someMethodOnHit() = 0;

    /// @brief simple getter for bullet damage 
    [[nodiscard]] auto getDamage() const -> uint8_t { return damage_; }

  protected:
    /// @brief setter for damage
    void setDamage(const uint8_t new_damage)
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

    [[nodiscard]] auto clone() const -> std::shared_ptr<Projectile_> final
    {
        return std::make_shared<Arrow>(*this);
    }

    void someMethodOnHit() final { setDamage( (getDamage()>=DAMAGE_REDUCE) ? getDamage() - DAMAGE_REDUCE : 0 ); }

    Arrow() { setDamage(DAMAGE); }
    Arrow(const Arrow& other) : Projectile_(other) { setDamage(other.getDamage()); }
    Arrow(Arrow&& other)      = default;
    auto operator=(const Arrow& /*other*/) -> Arrow& = default;
    auto operator=(Arrow&& other) noexcept -> Arrow&
    {
        setDamage(other.getDamage());
        return *this;
    }
    ~Arrow() override = default;

    static const uint8_t DAMAGE{7};
    static const uint8_t DAMAGE_REDUCE{5};
};

class Bullet : public Projectile_
{
  public:

    [[nodiscard]] auto clone() const -> std::shared_ptr<Projectile_> final
    {
        return std::make_shared<Bullet>(*this);
    }

    void someMethodOnHit() final { setDamage( (getDamage()>=DAMAGE_REDUCE) ? getDamage() - DAMAGE_REDUCE : 0 ); }

    Bullet() { setDamage(DAMAGE); }
    Bullet(const Bullet& other) : Projectile_(other) { setDamage(other.getDamage()); }
    Bullet(Bullet&& other) noexcept = default; 
    auto operator=(const Bullet& /*other*/) -> Bullet& = default;
    auto operator=(Bullet&& other) noexcept -> Bullet&
    {
        setDamage(other.getDamage());
        return *this;
    }
    ~Bullet() override = default;

    static const uint8_t DAMAGE{12};
    static const uint8_t DAMAGE_REDUCE{4};
};


class ProjectileFactory
{
    public:
      enum class Type : uint8_t
      {
          ARROW,
          BULLET
      };

      [[nodiscard]] auto create(const Type type) const -> std::shared_ptr<Projectile_>
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

