#ifndef IMG_APO_GUI_H
#define IMG_APO_GUI_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

#include "Callback.h"
#include "Logger.h"
#include "cJSON.h"

class imgAPO_GUI : public Gtk::Window
{
 public:
   imgAPO_GUI(bool debug = false);
   virtual ~imgAPO_GUI();

   bool Init(cJSON* config);
   bool Start();
   bool Shutdown();

 protected:
   struct ThreadHelper
   {
      pthread_t         thread_handle;
      pthread_attr_t    thread_attrib;

      imgAPO_GUI  *obj;

      bool  (imgAPO_GUI::*method)(void);
      bool  Done;
      int     SleepTime_us;
   };
   ThreadHelper m_ThreadHelper;
   pthread_mutex_t m_Working_Program;

   bool m_Debug;
   std::string m_Name;
   std::shared_ptr<Logger> m_Log;

   bool programLoop();

   // STATIC
   static void *thread_func(void *args);
   bool runApp();

   Glib::RefPtr<Gtk::Application> m_app;
   Gtk::Window* m_win;

   // Signal handlers:
   // Our new improved on_button_clicked(). (see below)
   void on_button_clicked(Glib::ustring data);

   //Member widgets:
   Gtk::Button m_button;
};

#endif // IMG_APO_GUI_H
