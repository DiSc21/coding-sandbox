#ifndef DS_FACTORY_METHOD_HPP
#define DS_FACTORY_METHOD_HPP

#include <iostream>
#include <memory>
#include <vector>

class ObjectBase_
{
  public:
    ObjectBase_()                         = default;
    ObjectBase_(const ObjectBase_ &other) = default;
    ObjectBase_(ObjectBase_ &&other)      = default;

    auto operator=(const ObjectBase_ & /*other*/) -> ObjectBase_ & = default;
    auto operator=(ObjectBase_ &&other) noexcept -> ObjectBase_ &
    {
        is_used_ = other.is_used_;
        return *this;
    }
    virtual ~ObjectBase_() = default;

    /// @brief getter for is_used_ member
    /// @return private member is_used_
    [[nodiscard]] auto isUsed() const -> bool { return is_used_; }

    /// @brief just some pure virtual test function
    [[nodiscard]] virtual auto doWhatNeedsToBeDone() const -> uint16_t = 0;

    /// @brief simple test function for forEach-lambda return by reference
    /// @param vec simple vector of bools
    void returnHorst(std::vector<bool> &vec) const { vec.push_back(isUsed()); }

    /// @brief sets is_used_ member true
    void enable() { is_used_ = true; }
    /// @brief sets is_used_ member false
    void disable() { is_used_ = false; }

  private:
    /// @brief just some simple member used for ObjectHandler's custom forEach (see below)
    bool is_used_{true};
};

class ObjectOne : public ObjectBase_
{
  public:
    ObjectOne() { disable(); }

    [[nodiscard]] auto doWhatNeedsToBeDone() const -> uint16_t override { return 1; }
};

class ObjectTwo : public ObjectBase_
{
  public:
    ObjectTwo() { enable(); }
    [[nodiscard]] auto doWhatNeedsToBeDone() const -> uint16_t override { return 2; }
};


class ObjectHandler
{
  public:
    /// @brief simple constructor assembling vector of shared ptr objects
    ObjectHandler()
    {
        static_cast<void>(objects_.emplace_back(createObject<ObjectOne>()));
        static_cast<void>(objects_.emplace_back(createObject<ObjectTwo>()));
    }

    /// @brief templated factory method creating shared pointer
    template <typename T> [[nodiscard]] static auto createObject() -> std::shared_ptr<ObjectBase_>
    {
        return std::make_shared<T>();
    }

    /// @brief simple test function calling ObjectBase_::returnHorst for each instantiated object
    /// @return accumulated doWhatNeedsToBeDone values for all ENABLED objects
    [[nodiscard]] auto doWhatNeedsToBeDone() -> uint16_t
    {
        uint16_t value{0};
        forEach([](const std::shared_ptr<ObjectBase_> &obj, uint16_t &val) { val += obj->doWhatNeedsToBeDone(); }, value);
        return value;
    }

    /// @brief simple test function calling ObjectBase_::returnHorst for each instantiated object
    /// @param vec simple vector of bools
    void processReturnHorsts(std::vector<bool> &vec)
    {
        forEach([](const std::shared_ptr<ObjectBase_> &obj, std::vector<bool> &vec_ref) { obj->returnHorst(vec_ref); }, vec);
    }

  private:
    /// @brief lambda wrapper for operations performed on all objects
    /// @tparam Lambda the lambda called for each object, first arg object ptr, second arg reference to target param
    /// @tparam Target type of the processed target data returned by reference
    /// @param lambda function called for each object
    /// @param target data to be returned by reference
    template <typename Lambda, typename Target> void forEach(Lambda lambda, Target &target)
    {
        for (auto &obj : objects_)
        {
            (obj->isUsed()) ? lambda(obj, target) : void();
        }
    }

    /// @brief vector of instantiated objects
    std::vector<std::shared_ptr<ObjectBase_>> objects_;
};

#endif
