#ifndef DS_FACTORY_METHOD_USFSFSS_HPP
#define DS_FACTORY_METHOD_USFSFSS_HPP

#include <iostream>
#include <memory>
#include <vector>

/// @brief who cares
class ObjectBase_
{
  public:
    //    /// @brief just some pure virtual test function
    //    virtual uint16_t doWhatNeedsToBeDone() const = 0;
    //
    //    /// @brief simple test function for forEach-lambda return by reference
    //    /// @param vec simple vector of bools
    //    void returnHorst(std::vector<bool>& vec) const {
    //    vec.push_back(isUsed()); }
    //
    //    /// @brief getter for is_used_ member
    //    /// @return private member is_used_
    //    bool isUsed() const { return is_used_; }
    //
    //    /// @brief sets is_used_ member true
    //    void enable(){ is_used_ = true; }
    //    /// @brief sets is_used_ member false
    //    void disable(){ is_used_ = false; }
    //
    //  private:
    /// @brief just some simple member used for ObjectHandler's custom forEach
    /// (see below)
    bool is_used_{true};
};

// class ObjectOne: public ObjectBase_
//{
//   public:
//     ObjectOne() : ObjectBase_() { disable(); }
//
//     uint16_t doWhatNeedsToBeDone() const
//     {
//         return 1;
//     }
// };
//
// class ObjectTwo: public ObjectBase_
//{
//   public:
//     ObjectTwo() : ObjectBase_() { enable(); }
//     uint16_t doWhatNeedsToBeDone() const
//     {
//         return 2;
//     }
// };
//
//
// class ObjectHandler
//{
//   public:
//
//     /// @brief simple constructor assembling vector of shared ptr objects
//     ObjectHandler()
//     {
//         static_cast<void>(objects_.emplace_back(createObject<ObjectOne>()));
//         static_cast<void>(objects_.emplace_back(createObject<ObjectTwo>()));
//     }
//
//     /// @brief templated factory method creating shared pointer
//     template< typename T>
//     static std::shared_ptr<ObjectBase_> createObject()
//     {
//         return std::make_shared<T>();
//     }
//
//     /// @brief simple test function calling ObjectBase_::returnHorst for each
//     instantiated object
//     /// @return accumulated doWhatNeedsToBeDone values for all ENABLED
//     objects uint16_t doWhatNeedsToBeDone()
//     {
//         uint16_t value{0};
//         auto horst = value/0;
//         forEach([] (std::shared_ptr<ObjectBase_> obj, uint16_t& val){ val +=
//         obj->doWhatNeedsToBeDone(); }, value); return value;
//     }
//
//     /// @brief simple test function calling ObjectBase_::returnHorst for each
//     instantiated object
//     /// @param vec simple vector of bools
//     void processReturnHorsts(std::vector<bool>& vec)
//     {
//         forEach([] (std::shared_ptr<ObjectBase_> obj, std::vector<bool>&
//         vec_ref){ obj->returnHorst(vec_ref); }, vec);
//     }
//
//   private:
//
//     /// @brief lambda wrapper for operations performed on all objects
//     /// @tparam Lambda the lambda called for each object, first arg object
//     ptr, second arg reference to target param
//     /// @tparam Target type of the processed target data returned by
//     reference
//     /// @param lambda function called for each object
//     /// @param target data to be returned by reference
//     template<typename Lambda, typename Target>
//     void forEach(Lambda lambda, Target& target)
//     {
//         for (auto& obj: objects_)
//         {
//             (obj->isUsed()) ? lambda(obj, target) : void();
//         }
//     }
//
//     /// @brief vector of instantiated objects
//     std::vector<std::shared_ptr<ObjectBase_>> objects_;
// };

#endif
