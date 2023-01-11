#ifndef __DS_HELLO_GTK_WiNDOW__
#define __DS_HELLO_GTK_WiNDOW__

#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/button.h>

/// @brief main window of the application
class DS_HelloGTKWindow : public Gtk::ApplicationWindow
{
  public:
    DS_HelloGTKWindow();

  private:
    Gtk::Button btn_; ///> simple gtk button
};

#endif

