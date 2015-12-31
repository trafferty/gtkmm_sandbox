#include <cstring>
#include <stdio.h>
#include "gtk_utils.h"

extern "C" {
#if 1

   void btnQuit_clicked (GtkButton * button, App * app)
   {
      // GtkEntry *entry = user_data;
      const gchar *text = gtk_button_get_label (button);
      printf("button label: %s\n", text);

      // gint position = 0;
      // gtk_editable_insert_text (GTK_EDITABLE (entPrefix), text, -1, &position);

   }

   void btnReconnect_clicked (GtkButton * button, App * app)
   {
   }

   void btnLoop_clicked (GtkButton * button, App * app)
   {
   }

   void btnSetStrategy_clicked (GtkButton * button, App * app)
   {
   }

   void spnStrategy_change_value (GtkButton * button, App * app)
   {
   }

   void btnQuery_clicked (GtkButton * button, App * app)
   {
   }

   void btnStop_clicked (GtkButton * button, App * app)
   {
   }

   void btnStart_clicked (GtkButton * button, App * app)
   {
   }

   void btnEndCapture_clicked (GtkButton * button, App * app)
   {
   }

   void btnBeginCapture_clicked (GtkButton * button, App * app)
   {
   }

   void on_entMainName_changed (GtkButton * button, App * app)
   {
   }

   void on_entPrefix_changed (GtkButton * button, App * app)
   {
   }
#else
GCallback
button1_clicked_cb (GtkButton * button, App * app)
{
  GET_UI_ELEMENT (GtkEntry, entry1);

  if (gtk_entry_get_text_length (entry1) == 0)
      gtk_entry_set_text (entry1, "test");
  else
      gtk_entry_set_text (entry1, "");
}

GCallback
button2_clicked_cb (GtkButton * button, App * app)
{
  gboolean active;

  GET_UI_ELEMENT (GtkSpinner, spinner1);
  GET_UI_ELEMENT (GtkWidget, eventbox1);

  g_object_get (G_OBJECT (spinner1), "active", &active,
                NULL);

  if (active) {
      gtk_spinner_stop (spinner1);
      gtk_widget_override_background_color (eventbox1,
                                            GTK_STATE_FLAG_NORMAL,
                                            app->
                                            active_color);
  }
  else {
      gtk_spinner_start (spinner1);
      gtk_widget_override_background_color (eventbox1,
                                            GTK_STATE_FLAG_NORMAL,
                                            app->
                                            inactive_color);
  }
}

GCallback
button3_clicked_cb (GtkButton * button, App * app)
{
  GdkRGBA bg = { 0, 0, 1, 1 };

  GET_UI_ELEMENT (GtkWidget, eventbox1);

  gtk_widget_override_background_color (eventbox1,
                                        GTK_STATE_FLAG_NORMAL,
                                        &bg);
}

GCallback
button4_clicked_cb (GtkButton * button, App * app)
{
  const gchar *str;

  GET_UI_ELEMENT (GtkLabel, label1);

  str = gtk_label_get_text (label1);

  if (strcmp (str, "label") == 0) {
      gtk_label_set_text (label1, "NewText");
  }
  else {
      gtk_label_set_text (label1, "label");
  }
}

GCallback
button5_clicked_cb (GtkButton * button, App * app)
{
  GET_UI_ELEMENT (GtkWidget, button1);
  GET_UI_ELEMENT (GtkWidget, button2);
  GET_UI_ELEMENT (GtkWidget, button4);

  g_signal_emit_by_name (button1, "clicked", app);
  g_signal_emit_by_name (button2, "clicked", app);
  g_signal_emit_by_name (button4, "clicked", app);
}
#endif
}
