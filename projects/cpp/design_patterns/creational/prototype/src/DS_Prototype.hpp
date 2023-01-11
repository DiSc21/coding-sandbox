//*****************************************************************************************|
//     ______ _              ____            _      ,                      _               |
//    (_) |  | |            (|   \ o        | |    /|   /         o       | |              |
//        |  | |     _       |    |    ,_   | |     |__/   _  _       __, | |   _|_        |
//      _ |  |/ \   |/      _|    ||  /  |  |/_)    | \   / |/ |  |  /  | |/ \   |         |
//     (_/   |   |_/|__/   (/\___/ |_/   |_/| \_/   |  \_/  |  |_/|_/\_/|/|   |_/|_/       |
//    *****************************************************************/|***********       |
//                                                                     \|                  |
//_________________________________________________________________________________________|
//                                                                                         |
// Copyright (c) 2023  DiSc21-Fantasies@TDK. All rights reserved.                          |
// None of the code is licensed under any License.                                         |
//_________________________________________________________________________________________|

#ifndef DS_PROJECTILE_HPP
#define DS_PROJECTILE_HPP

#include <map>
#include <memory>
#include <string>

/// @brief abstract projectile class
class Projectile_
{
  public:
    Projectile_()                                = default; ///> default-constructor
    Projectile_(const Projectile_ & /*> other*/) = default; ///> copy-constructor
    Projectile_(Projectile_ && /*> other*/)      = default; ///> move-constructor

    /// @return Projectile_
    auto operator=(const Projectile_ & /*> other*/) -> Projectile_  & = default; ///> =ops
    /// @param other the rhs Projectile_
    /// @return Projectile_
    auto operator=(Projectile_ &&other) noexcept -> Projectile_ &
    {
        damage_ = other.damage_;
        return *this;
    } ///> =ops

    virtual ~Projectile_() = default; ///> destructor


    /// @brief substitute for "virtual copy constructor" as c++ doesn't support that
    /// @return shared ptr on freshly created concrete projectile
    [[nodiscard]] virtual auto clone() const -> std::shared_ptr<Projectile_> = 0;

    /// @brief some common method for projectiles
    virtual void someMethodOnHit() = 0;

    /// @brief simple getter for bullet damage
    /// @return damage value of projectile
    [[nodiscard]] auto getDamage() const -> uint8_t { return damage_; }

  protected:
    /// @brief setter for damage
    /// @param new_damage the new dame value
    void setDamage(const uint8_t new_damage) { damage_ = new_damage; }

  private:
    /// @brief just some exemplary value for damage taken if hit
    uint8_t damage_{0};
};

/// @brief concrete arrow class derived from Projectile_
class Arrow : public Projectile_
{
  public:
    /// @brief concrete clone function
    /// @return shared ptr on freshly created concrete projectile
    [[nodiscard]] auto clone() const -> std::shared_ptr<Projectile_> final { return std::make_shared<Arrow>(*this); }

    /// @brief some common method for projectiles
    void someMethodOnHit() final { setDamage((getDamage() >= DAMAGE_REDUCE) ? getDamage() - DAMAGE_REDUCE : 0); }

    Arrow() { setDamage(DAMAGE); }              ///> default-constructor
    Arrow(const Arrow & /*> other*/) = default; ///> copy-constructor
    Arrow(Arrow && /*> other*/)      = default; ///> move-constructor

    /// @return Arrow Object
    auto operator=(const Arrow & /*> other*/) -> Arrow & = default; ///> =ops
    /// @param other the rhs object
    /// @return Arrow Object
    auto operator=(Arrow &&other) noexcept -> Arrow &
    {
        setDamage(other.getDamage());
        return *this;
    } ///> =ops

    ~Arrow() override = default; ///> destructor

    static const uint8_t DAMAGE{7};        ///> some static const to not use magic numbers
    static const uint8_t DAMAGE_REDUCE{5}; ///> some static const to not use magic numbers
};

/// @brief concrete bullet class derived from Projectile_
class Bullet : public Projectile_
{
  public:
    /// @brief concrete clone function
    /// @return shared ptr on freshly created concrete projectile
    [[nodiscard]] auto clone() const -> std::shared_ptr<Projectile_> final { return std::make_shared<Bullet>(*this); }

    /// @brief some common method for projectiles
    void someMethodOnHit() final { setDamage((getDamage() >= DAMAGE_REDUCE) ? getDamage() - DAMAGE_REDUCE : 0); }

    Bullet() { setDamage(DAMAGE); }        ///> default-constructor
    Bullet(const Bullet & /*> other*/)     = default; ///> copy-constructor
    Bullet(Bullet && /*> other*/) noexcept = default; ///> move-constructor

    /// @return Bullet Object
    auto operator=(const Bullet & /*> other*/) -> Bullet & = default; ///> =ops
    /// @param other the other Bullet Object
    /// @return Bullet Object
    auto operator=(Bullet &&other) noexcept -> Bullet &
    {
        setDamage(other.getDamage());
        return *this;
    } ///> =ops

    ~Bullet() override = default; ///> destructor

    static const uint8_t DAMAGE{7};        ///> some static const to not use magic numbers
    static const uint8_t DAMAGE_REDUCE{5}; ///> some static const to not use magic numbers
};


/// @brief factory style class creating projectiles by cloning
class ProjectileFactory
{
  public:
    /// @brief enum mapping of all prototypes
    enum class Type : uint8_t
    {
        ARROW,
        BULLET
    };

    /// @brief creation function for new projectiles
    /// @param type the concrete projectile to create
    /// @return shared ptr on concrete projectile
    [[nodiscard]] auto create(const Type type) const -> std::shared_ptr<Projectile_>
    {
        return projectile_prototypes_.at(type)->clone();
    }

  private:
    /// @brief map of prototypes
    const std::map<Type, std::shared_ptr<Projectile_>> projectile_prototypes_ = {
        {Type::ARROW,  std::make_shared<Arrow>() },
        {Type::BULLET, std::make_shared<Bullet>()}
    };
};


#endif
