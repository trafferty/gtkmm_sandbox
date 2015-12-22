// from system:
#include <unistd.h>  // for usleep
#include <sstream>
#include <memory>
#include <signal.h>

#include <gtkmm.h>
// #include <gtkmm/button.h>
// #include <gtkmm/window.h>
// #include <gtkmm/application.h>

// from local:
#include "imgAPO_GUI.h"

using namespace std;

bool CtrlC = false;
void sigint_handler(int n)
{
    CtrlC = true;
    std::cerr << "sigint received - aborting: " << n << std::endl;
}

void on_button_clicked(Glib::ustring data)
{
   std::cout << "imgAPO_GUI - " << data << " was pressed" << std::endl;
}

int main(int argc, char* argv[])
{
   /* Register a handler for control-c */
   signal(SIGINT, sigint_handler);

#if 0
   bool debug=true;
   std::unique_ptr<imgAPO_GUI> gui = std::unique_ptr<imgAPO_GUI>(new imgAPO_GUI(debug));

   cJSON* config(NULL);
   if (gui->Init(config) == false)
   {
      std::cerr << "Command Processor initialization failed" << std::endl;
      exit(1);
   }

   //gui->Start();

#else

   //set_border_width(10);

   argc=1;
   auto app = Gtk::Application::create(argc, argv, "cnt.imgAPO.gui");


   //Load the GtkBuilder file and instantiate its widgets:
   auto refBuilder = Gtk::Builder::create();
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

   //Get the GtkBuilder-instantiated window:
   Gtk::Window* win;
   refBuilder->get_widget("main_window", win);
   if (win)
   {
      //Get the GtkBuilder-instantiated Button, and connect a signal handler:
      Gtk::Button* pButton = 0;
      refBuilder->get_widget("btnQuit", pButton);
      if(pButton)
      {
         pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );

         //  pButton->signal_clicked().connect(sigc::bind<Glib::ustring>(
         //               sigc::mem_fun(*this, &imgAPO_GUI::on_button_clicked), "doQuit"));

         std::cout << "Window instantiated and widget signals connected" << std::endl;
      }
   }

   std::cout << "Running app..." << std::endl;

   app->run(*win);


#endif
   while (!CtrlC)
   {
       usleep(1 * 1000);
   }

   //gui->Shutdown();

   return 0;
}

#if 0

#include "hello_world.h"
#include <iostream>

HelloWorld::HelloWorld()
: m_button("Hello World")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));

  // This packs the button into the Window (a container).
  add(m_button);

  // The final step is to display this newly created widget...
  m_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}
#endif
