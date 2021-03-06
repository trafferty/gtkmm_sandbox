// from system:
#include <unistd.h>  // for usleep
#include <sstream>
#include <memory>
#include <signal.h>

#include "gtk_utils.h"


// from local:
#include "imgAPO_GUI.h"

using namespace std;

bool CtrlC = false;
void sigint_handler(int n)
{
    CtrlC = true;
    std::cerr << "sigint received - aborting: " << n << std::endl;
}

// void on_button_clicked(Glib::ustring data)
// {
//    std::cout << "imgAPO_GUI - " << data << " was pressed" << std::endl;
// }

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

   while (!CtrlC)
   {
       usleep(1 * 1000);
   }

   //gui->Shutdown();

#else

   //set_border_width(10);

   App *app;

   app = (App *) g_new (App, 1);

   gtk_init (&argc, &argv);

   app_init (app);

   GET_UI_ELEMENT (GtkWidget, main_window);

   gtk_widget_show_all (main_window);

   //gtk_main ();
   while (!CtrlC)
    {
       if (gtk_events_pending())
        gtk_main_iteration();
       else
        usleep(1 * 1000);
    }


#endif

   return 0;
}

extern "C" {

void btnGeneric_clicked (GtkButton * button, App * app)
{
   // GtkEntry *entry = user_data;
   const gchar *text = gtk_button_get_label (button);
   printf("button label: %s\n", text);

   // gint position = 0;
   // gtk_editable_insert_text (GTK_EDITABLE (entPrefix), text, -1, &position);

}
}
