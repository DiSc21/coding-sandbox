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
//
//------------------------------------------------------------------------------------------
//- ABSTRACT FACTORY -----------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// The abstract factory pattern is useful when client doesn’t know exactly what type
// to create.kj
//
//------------------------------------------------------------------------------------------
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
//   Implements the operations declared in the Abstract Factory to create concrete objects.
// - CLIENT:
//   Uses only interfaces declared by Abstract Factory and Abstract Product classes.
//
//------------------------------------------------------------------------------------------
// Abstract factory pattern is useful when client doesn’t know exactly what type to create.
// ADVANTAGES:
// -----------
// - ISOLATION of concrete classes:
//   Abstract Factory pattern helps to control classes of objects created by an application.
//
// - FAST and EASY EXCHANGING of Product Families:
//   Class of concrete factories appear only once in an application where instantiated.
//   This makes it easy to change the concrete factory an application uses.
//
// - Enforcing CONSISTENCY among PRODUCTS:
//   When product objects in a family are designed to work together, it’s important that
//   applications use only objects from a single family at a time.
//   AbstractFactory makes this easy to enforce.
//
//------------------------------------------------------------------------------------------
//
// DISADVANTAGES:
// --------------
// - DIFFICULT to SUPPORT NEW KIND OF PRODUCTS:
//   Since the Abstract Factory interface fixes the set of products that can be created,
//   it's not straight-forward to extend abstract factories to produce new kind of products.
//
//------------------------------------------------------------------------------------------

#ifndef DS_ABSTRACT_FACTORY_HPP
#define DS_ABSTRACT_FACTORY_HPP

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

/// @brief Enum for different types of widgets
enum class WidgetType : uint8_t
{
    BUTTON,
    MENU
};

/// @brief Enum for different types of platforms
enum class PlatformType : uint8_t
{
    LINUX,
    WINDOWS
};

/// @brief Struct with Widget/Platform enum members
struct PlatformWidget
{
    /// @brief the platform type
    PlatformType p_type;
    /// @brief the widget type
    WidgetType   w_type;
};

/// @brief ABSTRACT PRODUCT. It should define an interface which will be common to all products.
/// Clients work with products through this interface, so should be sufficient to use all products.
class Widget_
{
  public:
    /// @brief pure virtual draw method
    /// @return PlatformWidget struct for testing
    [[nodiscard]] virtual auto draw() const -> PlatformWidget = 0;

    Widget_()                             = default; ///> default-constructor
    Widget_(const Widget_ & /*> other */) = default; ///> copy-constructor
    Widget_(Widget_ && /*> other */)      = default; ///> move-constructor

    /// @return Widget_
    auto operator=(const Widget_ & /*> other*/) -> Widget_ & = default; ///> =ops
    /// @return Widget_
    auto operator=(Widget_ && /*> other*/) noexcept -> Widget_ & { return *this; } ///> =ops

    virtual ~Widget_() = default; ///> destructor
};


/// @brief Concrete LINUX product BUTTON
class LinuxButton : public Widget_
{
  public:
    /// @brief concrete draw method
    /// @return PlatformWidget struct for testing
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::LINUX, WidgetType::BUTTON}); }
};
/// @brief Concrete LINUX product MENU
class LinuxMenu : public Widget_
{
  public:
    /// @brief concrete draw method
    /// @return PlatformWidget struct for testing
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::LINUX, WidgetType::MENU}); }
};


/// @brief Concrete WINDOWS product BUTTON
class WindowsButton : public Widget_
{
  public:
    /// @brief concrete draw method
    /// @return PlatformWidget struct for testing
    [[nodiscard]] auto draw() const -> PlatformWidget final
    {
        return PlatformWidget({PlatformType::WINDOWS, WidgetType::BUTTON});
    }
};
/// @brief Concrete WINDOWS product MENU
class WindowsMenu : public Widget_
{
  public:
    /// @brief concrete draw method
    /// @return PlatformWidget struct for testing
    [[nodiscard]] auto draw() const -> PlatformWidget final { return PlatformWidget({PlatformType::WINDOWS, WidgetType::MENU}); }
};


/// @brief ABSTRACT FACTORY defines methods to create all related products.
class Factory_
{
  public:
    /// @brief pure virtual creation method for button
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] virtual auto create_button() const -> std::shared_ptr<Widget_> = 0;
    /// @brief pure virtual creation method for menu
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] virtual auto create_menu() const -> std::shared_ptr<Widget_>   = 0;

    Factory_()                             = default; ///> default-constructor
    Factory_(const Factory_ & /*> other*/) = default; ///> copy-constructor
    Factory_(Factory_ && /*> other*/)      = default; ///> move-constructor


    /// @return Factory
    auto operator=(const Factory_ & /*> other*/) -> Factory_ & = default; ///> =ops
    /// @return Factory
    auto operator=(Factory_ && /*> other*/) noexcept -> Factory_ & { return *this; } ///> =ops

    virtual ~Factory_() = default; ///> destructor
};
/// @brief a CONCRETE FACTORY corresponding to LINUX product family
class LinuxFactory : public Factory_
{
  public:
    /// @brief concrete creation method for button
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] auto create_button() const -> std::shared_ptr<Widget_> final { return std::make_shared<LinuxButton>(); }
    /// @brief concrete creation method for menu
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] auto create_menu() const -> std::shared_ptr<Widget_> final { return std::make_shared<LinuxMenu>(); }
};
/// @brief a CONCRETE FACTORY corresponding to LINUX product family
class WindowsFactory : public Factory_
{
  public:
    /// @brief concrete creation method for button
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] auto create_button() const -> std::shared_ptr<Widget_> final { return std::make_shared<WindowsButton>(); }
    /// @brief concrete creation method for menu
    /// @return shared pointer on freshly created widget
    /// @note using template<Widget> and only having single create_widget method would be nicer
    [[nodiscard]] auto create_menu() const -> std::shared_ptr<Widget_> final { return std::make_shared<WindowsMenu>(); }
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
    WidgetClient() = delete;

    /// @brief Parameterized constructor
    /// @param factory shared pointer on the concrete (Windows or Linux) factory for client to use
    explicit WidgetClient(const std::shared_ptr<Factory_> &factory) : factory_(factory) {}

    /// @brief function to display window, i.e. in this case just returning a vector of Widgets
    /// @return vector of platfomrWidget structs
    [[nodiscard]] auto display_window() -> std::vector<PlatformWidget>
    {
        std::vector<std::shared_ptr<Widget_>> widgets = {factory_->create_button(), factory_->create_menu()};

        std::vector<PlatformWidget> concrete_widgets{};
        for ( const auto &widget : widgets )
        {
            static_cast<void>(concrete_widgets.emplace_back(widget->draw()));
        }

        return concrete_widgets;
    }

  private:
    // @brief const ref on factory daughtor, i.e. Windows or Linux factory
    const std::shared_ptr<Factory_> &factory_;
};

#endif
