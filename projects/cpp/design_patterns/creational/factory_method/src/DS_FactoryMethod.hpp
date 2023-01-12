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

#ifndef DS_FACTORY_METHOD_HPP
#define DS_FACTORY_METHOD_HPP

#include <iostream>
#include <memory>
#include <vector>

/// @brief pure virtual basis class
class ObjectBase_
{
  public:
    ObjectBase_()                                = default; ///> default-constructor
    ObjectBase_(const ObjectBase_ & /*> other*/) = default; ///> copy-constructor
    ObjectBase_(ObjectBase_ && /*> other*/)      = default; ///> move-constructor

    /// @return ObjectBase_
    auto operator=(const ObjectBase_ & /*> other*/) -> ObjectBase_ & = default; ///> =ops
    /// @return ObjectBase_
    /// @param other the rhs object
    auto operator=(ObjectBase_ &&other) noexcept -> ObjectBase_ &
    {
        is_used_ = other.is_used_;
        return *this;
    } ///> =ops

    virtual ~ObjectBase_() = default; ///> destructor

    /// @brief getter for is_used_ member
    /// @return private member is_used_
    [[nodiscard]] auto isUsed() const -> bool { return is_used_; }

    /// @brief just some pure virtual test function
    /// @return currenty nothind, later just an integer for test purposes
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

/// @brief concrete ObjectOne
class ObjectOne : public ObjectBase_
{
  public:
    ObjectOne() { disable(); } ///> a constructor, ... why makes me doxygen do that?

    /// @brief concrete test function
    /// @return an integer for test purposes
    [[nodiscard]] auto doWhatNeedsToBeDone() const -> uint16_t override { return 1; }
};

/// @brief concrete ObjectTwo
class ObjectTwo : public ObjectBase_
{
  public:
    ObjectTwo() { enable(); } ///> a constructor, ... why makes me doxygen do that?

    /// @brief concrete test function
    /// @return an integer for test purposes
    [[nodiscard]] auto doWhatNeedsToBeDone() const -> uint16_t override { return 2; }
};

/// @brief ObjectHandler
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
    /// @return shared ptr on create Object
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
        for ( auto &obj : objects_ )
        {
            (obj->isUsed()) ? lambda(obj, target) : void();
        }
    }

    /// @brief vector of instantiated objects
    std::vector<std::shared_ptr<ObjectBase_>> objects_;
};

#endif
