#include <gtkmm.h>
#include <iostream>

#include "imgAPO_GUI.h"

imgAPO_GUI::imgAPO_GUI(bool debug) :
   m_Debug(debug),
   m_Name("CommandProcessor"),
   m_win(0)
{
   m_Log = std::shared_ptr<Logger>(new Logger(m_Name, m_Debug));

   pthread_mutex_init(&m_Working_Program, NULL);

   // m_callback = new Callback2<CommandProcessor, bool, intptr_t, void*>(this, &CommandProcessor::recvCBRoutine, 0, 0);
   // m_ICallbackPtr = m_callback;

   // Sets the border width of the window.
   //set_border_width(10);

   int argc=1;
   char **argv;

   m_app = (App *) g_new (App, 1);
}

imgAPO_GUI::~imgAPO_GUI()
{
}

bool imgAPO_GUI::Init(cJSON* config)
{

   GError *err = NULL;

   m_app->definitions = gtk_builder_new ();

   gtk_builder_add_from_file (m_app->definitions,
                              UI_DEFINITIONS_FILE, &err);


   if (err != NULL)
   {
       g_printerr
           ("Error while loading app definitions file: %s\n",
            err->message);
       g_error_free (err);
       gtk_main_quit ();
   }

   gtk_builder_connect_signals (m_app->definitions, m_app);

   m_app->objects = gtk_builder_get_objects (m_app->definitions);



   // //Get the GtkBuilder-instantiated window:
   // refBuilder->get_widget("main_window", m_win);
   // if(m_win)
   // {
   //    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
   //    Gtk::Button* pButton = 0;
   //    refBuilder->get_widget("btnQuit", pButton);
   //    if(pButton)
   //    {
   //       //pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
   //
   //        pButton->signal_clicked().connect(sigc::bind<Glib::ustring>(
   //                     sigc::mem_fun(*this, &imgAPO_GUI::on_button_clicked), "doQuit"));
   //
   //       std::cout << "Window instantiated and widget signals connected" << std::endl;
   //    }
   // }

   return true;
}

bool imgAPO_GUI::Start()
{
   m_ThreadHelper.method = &imgAPO_GUI::runApp;
   m_ThreadHelper.obj = (this);
   m_ThreadHelper.Done = false;

   // create the RX Thread
   if (pthread_create(&(m_ThreadHelper.thread_handle), 0,
         imgAPO_GUI::thread_func, (void *)&m_ThreadHelper) != 0)
   {
      std::cerr << "Error spawning GUI thread" << std::endl;
      return false;
   }

   return true;
}

bool imgAPO_GUI::Shutdown()
{
   m_ThreadHelper.Done = true;
   m_Log->LogDebug("ProcessCommands thread stopped, shutting down comms...");

   m_Log->LogDebug("Waiting for join...");
   pthread_join(m_ThreadHelper.thread_handle, NULL);

   return true;
}

void imgAPO_GUI::on_button_clicked(Glib::ustring data)
{
   std::cout << "imgAPO_GUI - " << data << " was pressed" << std::endl;
   if (m_win)
      m_win->hide(); //hide() will cause main::run() to end.

}

bool imgAPO_GUI::runApp()
{
   std::cout << "Running app..." << std::endl;

   //m_app->run(*m_win);
   gtk_main_iteration();
   if (gtk_events_pending())
      gtk_main_iteration();

}

//=============================================================================
// thread_func
//=============================================================================
void *imgAPO_GUI::thread_func(void *args)
{
   ThreadHelper* threadHelper = static_cast<ThreadHelper*> (args);

   while (!threadHelper->Done)
   {
      (threadHelper->obj->*(threadHelper->method))();
   }

   pthread_exit(0);
   return NULL;
}
