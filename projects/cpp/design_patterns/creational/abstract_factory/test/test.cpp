#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_AbstractFactory.hpp"

void EXPECT_LINUX(const PlatformWidget &data) { EXPECT_EQ(PlatformType::LINUX, data.p_type); }
void EXPECT_WINDOWS(const PlatformWidget &data) { EXPECT_EQ(PlatformType::WINDOWS, data.p_type); }

void EXPECT_BUTTON(const PlatformWidget &data) { EXPECT_EQ(WidgetType::BUTTON, data.w_type); }
void EXPECT_MENU(const PlatformWidget &data) { EXPECT_EQ(WidgetType::MENU, data.w_type); }


TEST(LinuxWidget, Button) // NOLINT
{
    PlatformWidget data = LinuxButton().draw();
    EXPECT_LINUX(data);
    EXPECT_BUTTON(data);
}

TEST(LinuxWidget, Menu) // NOLINT
{
    PlatformWidget data = LinuxMenu().draw();
    EXPECT_LINUX(data);
    EXPECT_MENU(data);
}


TEST(LinuxFactory, create_button) // NOLINT
{
    PlatformWidget data = LinuxFactory().create_button()->draw();
    EXPECT_LINUX(data);
    EXPECT_BUTTON(data);
}

TEST(LinuxFactory, create_menu) // NOLINT
{
    PlatformWidget data = LinuxFactory().create_menu()->draw();
    EXPECT_LINUX(data);
    EXPECT_MENU(data);
}


TEST(LinuxWidgetClient, display_window) // NOLINT
{
    const auto data_vec = WidgetClient(std::make_shared<LinuxFactory>()).display_window();

    uint8_t btn_num{0};
    uint8_t menu_num{0};

    for (const auto &data : data_vec)
    {
        EXPECT_LINUX(data);
        (data.w_type == WidgetType::BUTTON) ? btn_num++ : menu_num++;
    }
    EXPECT_EQ(1, btn_num);
    EXPECT_EQ(1, menu_num);
}


TEST(Windows, Button) // NOLINT
{
    PlatformWidget data = WindowsButton().draw();
    EXPECT_WINDOWS(data);
    EXPECT_BUTTON(data);
}

TEST(Windows, Menu) // NOLINT
{
    PlatformWidget data = WindowsMenu().draw();
    EXPECT_WINDOWS(data);
    EXPECT_MENU(data);
}


TEST(WindowsFactory, create_button) // NOLINT
{
    PlatformWidget data = WindowsFactory().create_button()->draw();
    EXPECT_WINDOWS(data);
    EXPECT_BUTTON(data);
}

TEST(WindowsFactory, create_menu) // NOLINT
{
    PlatformWidget data = WindowsFactory().create_menu()->draw();
    EXPECT_WINDOWS(data);
    EXPECT_MENU(data);
}


TEST(WindowsWidgetClient, display_window) // NOLINT
{
    const auto data_vec = WidgetClient(std::make_shared<WindowsFactory>()).display_window();

    uint8_t btn_num{0};
    uint8_t menu_num{0};

    for (const auto &data : data_vec)
    {
        EXPECT_WINDOWS(data);
        (data.w_type == WidgetType::BUTTON) ? btn_num++ : menu_num++;
    }
    EXPECT_EQ(1, btn_num);
    EXPECT_EQ(1, menu_num);
}


int main(int argc, char **argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
