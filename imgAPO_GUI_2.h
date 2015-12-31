#ifndef IMG_APO_GUI_H
#define IMG_APO_GUI_H

#include <gtk/gtk.h>

#include "Logger.h"
#include "cJSON.h"

#define GET_UI_ELEMENT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *) \
                                            app_get_ui_element(app, #ELEMENT);

#define UI_DEFINITIONS_FILE "imgAPO_GUI_new.glade"

typedef struct app_
{
   GtkBuilder *definitions;
   GSList *objects;
} App;

class imgAPO_GUI
{
 public:
   imgAPO_GUI(bool debug = false);
   virtual ~imgAPO_GUI();

   bool Init(cJSON* config);
   bool Start();
   bool Shutdown();

   GObject * app_get_ui_element (App * , const gchar * );

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

   App m_app;

   // Signal handlers:
   // Our new improved on_button_clicked(). (see below)
   void on_button_clicked(gchar *);

};

#endif // IMG_APO_GUI_H
