#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_HelloGTKWindow.hpp"

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>


int g_argc;
char** g_argv;

TEST(test_case, simple_test0)
{
    auto app = Gtk::Application::create(g_argc, g_argv, "org.gtkmm.example.HelloApp");
    DS_HelloGTKWindow hw;

    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    g_argc = argc;
    g_argv = argv;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

