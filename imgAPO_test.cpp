// from system:
#include <unistd.h>  // for usleep
#include <sstream>
#include <memory>
#include <signal.h>

// from local:
#include "imgAPO_GUI.h"

using namespace std;

bool CtrlC = false;
void sigint_handler(int n)
{
    CtrlC = true;
    std::cerr << "sigint received - aborting: " << n << std::endl;
}

int main(int argc, char* argv[])
{
   /* Register a handler for control-c */
   signal(SIGINT, sigint_handler);

   bool debug=true;
   std::unique_ptr<imgAPO_GUI> gui = std::unique_ptr<imgAPO_GUI>(new imgAPO_GUI(debug));

   cJSON* config(NULL);
   if (gui->Init(config) == false)
   {
      std::cerr << "Command Processor initialization failed" << std::endl;
      exit(1);
   }

   gui->Start();

   while (!CtrlC)
   {
       usleep(1 * 1000);
   }

   gui->Shutdown();

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