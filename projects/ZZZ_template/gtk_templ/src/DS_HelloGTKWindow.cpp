#include "DS_HelloGTKWindow.hpp"

DS_HelloGTKWindow::DS_HelloGTKWindow() : btn_("Click me!")
{
    // initialize button with a text label
    // when user presses the button "clicked" signal is emitted
    // connect an event handler for the signal with connect()
    // which accepts lambda expression, among other things
    btn_.signal_clicked().connect(
    [this]() {
        btn_.set_label("Hello World");
    });

    // add the push button to the window
    add(btn_);

    // make the window visible
    show_all();
}

