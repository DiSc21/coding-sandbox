//----------------------------------------------------------------------------------------------------
//- ABSTRACT FACTORY ---------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// The abstract factory pattern is useful when client doesn’t know exactly what type to create.
//
//----------------------------------------------------------------------------------------------------
//
// COMPONENTS:
// -----------
// - (ABSTRACT) PRODUCT:
//   The abstract product to be created defining the product interface.
// - (CONCRETE) PRODUCT(S):
//   The concrete products to be created with the interface defined by the abstract product.
// - ABSTRACT FACTORY:
//   Declares an interface for operations that create abstract product objects.
// - CONCRETE FACTORY:
//   Implements the operations declared in the Abstract Factory to create concrete product objects.
// - CLIENT:
//   Uses only interfaces declared by Abstract Factory and Abstract Product classes.
//
//----------------------------------------------------------------------------------------------------
// The abstract factory pattern is useful when client doesn’t know exactly what type to create.
// ADVANTAGES:
// -----------
// - ISOLATION of concrete classes:
//   The Abstract Factory pattern helps to control classes of objects that an application creates.
//
// - FAST and EASY EXCHANGING of Product Families:
//   The class of concrete factories appear only once in an application, i.e. where instantiated.
//   This makes it easy to change the concrete factory an application uses.
//
// - Enforcing CONSISTENCY among PRODUCTS:
//   When product objects in a family are designed to work together, it’s important that applications
//   use only objects from a single family at a time. AbstractFactory makes this easy to enforce.
//
//----------------------------------------------------------------------------------------------------
//
// DISADVANTAGES:
// --------------
// - DIFFICULT to SUPPORT NEW KIND OF PRODUCTS:
//   Since the Abstract Factory interface fixes the set of products that can be created,
//   it's not straight-forward to extend abstract factories to produce new kinds of products.
//
//----------------------------------------------------------------------------------------------------

#ifndef DS_ABSTRACT_FACTORY_HPP
#define DS_ABSTRACT_FACTORY_HPP

#include <memory>
#include <vector>
#include <iostream>

enum class WidgetType : uint8_t
{
    BUTTON,
    MENU
};

enum class PlatformType : uint8_t
{
    LINUX,
    WINDOWS
};

struct PlatformWidget
{
    PlatformType p_type;
    WidgetType w_type;
};

/// @brief ABSTRACT PRODUCT. It should define an interface which will be common to all products.
/// Clients work with products through this interface, so should be sufficient to use all products.
class Widget_
{
  public:
    [[nodiscard]] virtual auto draw() const -> PlatformWidget = 0;

    Widget_()                     = default;
    Widget_(const Widget_ &other) = default;
    Widget_(Widget_&& other)      = default;

    auto operator=(const Widget_& /*other*/) -> Widget_& = default;
    auto operator=(Widget_&& /*other*/) noexcept -> Widget_& { return *this; }

    virtual ~Widget_() = default;
};


/// @brief Concrete LINUX product BUTTON
class LinuxButton : public Widget_
{
  public:
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::LINUX, WidgetType::BUTTON}); }
};
/// @brief Concrete LINUX product MENU
class LinuxMenu : public Widget_
{
  public:
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::LINUX, WidgetType::MENU}); }
};


/// @brief Concrete WINDOWS product BUTTON
class WindowsButton : public Widget_
{
  public:
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::WINDOWS, WidgetType::BUTTON}); }
};
/// @brief Concrete WINDOWS product MENU
class WindowsMenu : public Widget_
{
  public:
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::WINDOWS, WidgetType::MENU}); }
};


/// @brief ABSTRACT FACTORY defines methods to create all related products.
class Factory_
{
  public:
    [[nodiscard]] virtual auto create_button() const -> std::shared_ptr<Widget_> = 0;
    [[nodiscard]] virtual auto create_menu()   const -> std::shared_ptr<Widget_> = 0;

    Factory_()                      = default;
    Factory_(const Factory_ &other) = default;
    Factory_(Factory_&& other)      = default;

    auto operator=(const Factory_& /*other*/) -> Factory_& = default;
    auto operator=(Factory_&& /*other*/) noexcept -> Factory_& { return *this; }

    virtual ~Factory_() = default;
};
/// @brief a CONCRETE FACTORY corresponding to LINUX product family
class LinuxFactory : public Factory_
{
  public:
    [[nodiscard]] auto create_button() const -> std::shared_ptr<Widget_>  final { return std::make_shared<LinuxButton>(); }
    [[nodiscard]] auto create_menu()   const -> std::shared_ptr<Widget_>  final { return std::make_shared<LinuxMenu>();   }
};
/// @brief a CONCRETE FACTORY corresponding to LINUX product family
class WindowsFactory : public Factory_
{
  public:
    [[nodiscard]] auto create_button() const -> std::shared_ptr<Widget_>  final { return std::make_shared<WindowsButton>(); }
    [[nodiscard]] auto create_menu()   const -> std::shared_ptr<Widget_>  final { return std::make_shared<WindowsMenu>();   }
};


/// @brief Client receives a factory object from its creator.
/// @note All clients work with factories through abstract
///       interface. They don't know concrete classes of
///       factories. Because of this, you can interchange
///       concrete factories without breaking clients.
/// @note Clients don't know the concrete classes of created
///       products either, since abstract factory methods
///       returns abstract products.
class WidgetClient 
{
  public:
    explicit WidgetClient(const std::shared_ptr<Factory_>& factory) : factory_(factory) {}

    [[nodiscard]] auto display_window() -> std::vector<PlatformWidget>
    {
       std::vector<std::shared_ptr<Widget_>> widgets = {
           factory_->create_button(),
           factory_->create_menu()
       };

       std::vector<PlatformWidget> concrete_widgets{};
       for(const auto& widget: widgets)
       {
           static_cast<void>(concrete_widgets.emplace_back(widget->draw()));
       }

       return concrete_widgets;
    }

  private:
    const std::shared_ptr<Factory_>& factory_;
};

#endif

