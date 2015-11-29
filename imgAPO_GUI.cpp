#include <gtkmm.h>
#include <iostream>

Gtk::Window* pDialog = 0;

static
void on_button_clicked()
{
  if(pDialog)
    pDialog->hide(); //hide() will cause main::run() to end.
}

int main (int argc, char **argv)
{
   Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "cnt.imgAPO.gui");

   //Load the GtkBuilder file and instantiate its widgets:
   Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
   try
   {
      refBuilder->add_from_file("imgAPO_GUI.glade");
   }
   catch(const Glib::FileError& ex)
   {
      std::cerr << "FileError: " << ex.what() << std::endl;
      return 1;
   }
   catch(const Glib::MarkupError& ex)
   {
      std::cerr << "MarkupError: " << ex.what() << std::endl;
      return 1;
   }
   catch(const Gtk::BuilderError& ex)
   {
      std::cerr << "BuilderError: " << ex.what() << std::endl;
      return 1;
   }

   //Get the GtkBuilder-instantiated Dialog:
   refBuilder->get_widget("main_window", pDialog);
   if(pDialog)
   {
      //Get the GtkBuilder-instantiated Button, and connect a signal handler:
      Gtk::Button* pButton = 0;
      refBuilder->get_widget("btnQuit", pButton);
      if(pButton)
      {
         pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
      }

      app->run(*pDialog);
   }

   delete pDialog;

   return 0;
}
