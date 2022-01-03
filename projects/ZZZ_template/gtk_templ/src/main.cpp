#include "DS_HelloGTKWindow.hpp"

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>

#include <iostream>


int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example.HelloApp");

    DS_HelloGTKWindow hw;

    // this starts the application with our window
    // close the window to terminate the application
    return app->run(hw);
}

