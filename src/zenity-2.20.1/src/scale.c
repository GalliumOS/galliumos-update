/*
 * scale.c
 *
 * Copyright (C) 2002 Sun Microsystems, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Authors: Lucas Rocha <lucasr@gnome.org>
 */

#include "config.h"

#include <glade/glade.h>
#include "zenity.h"
#include "util.h"

static GtkWidget *scale;

static void zenity_scale_value_changed (GtkWidget *widget, gpointer data);
static void zenity_scale_dialog_response (GtkWidget *widget, int response, gpointer data);

void 
zenity_scale (ZenityData *data, ZenityScaleData *scale_data)
{
  GladeXML *glade_dialog;
  GtkWidget *dialog;
  GtkWidget *text;

  glade_dialog = zenity_util_load_glade_file ("zenity_scale_dialog");
  dialog = glade_xml_get_widget (glade_dialog, "zenity_scale_dialog");
  scale = glade_xml_get_widget (glade_dialog, "zenity_scale_hscale");
  text = glade_xml_get_widget (glade_dialog, "zenity_scale_text");

  g_signal_connect (G_OBJECT (dialog), "response",
                    G_CALLBACK (zenity_scale_dialog_response), data);
	
  if (glade_dialog == NULL) {
    data->exit_code = zenity_util_return_exit_code (ZENITY_ERROR);
    return;
  }

  if (scale_data->min_value >= scale_data->max_value) {
    g_printerr (_("Maximum value must be greater than minimum value.\n")); 
    data->exit_code = zenity_util_return_exit_code (ZENITY_ERROR);
    return;
  }

  if (scale_data->value < scale_data->min_value ||
      scale_data->value > scale_data->max_value) {
    g_printerr (_("Value out of range.\n")); 
    data->exit_code = zenity_util_return_exit_code (ZENITY_ERROR);
    return;
  }

  glade_xml_signal_autoconnect (glade_dialog);
        
  if (glade_dialog)
    g_object_unref (glade_dialog);

  if (data->dialog_title)
    gtk_window_set_title (GTK_WINDOW (dialog), data->dialog_title);

  zenity_util_set_window_icon (dialog, data->window_icon, ZENITY_IMAGE_FULLPATH ("zenity-scale.png"));
  
  if (data->width > -1 || data->height > -1)
    gtk_window_set_default_size (GTK_WINDOW (dialog), data->width, data->height);
        
  if (scale_data->dialog_text) 
    gtk_label_set_markup (GTK_LABEL (text), g_strcompress (scale_data->dialog_text));

  gtk_range_set_value (GTK_RANGE (scale), scale_data->value);
  gtk_range_set_range (GTK_RANGE (scale), scale_data->min_value, scale_data->max_value);
  gtk_range_set_increments (GTK_RANGE (scale), scale_data->step, 0);

  if (scale_data->print_partial) 
    g_signal_connect (G_OBJECT (scale), "value-changed",
                      G_CALLBACK (zenity_scale_value_changed), data);
  
  if (scale_data->hide_value)
    gtk_scale_set_draw_value (GTK_SCALE (scale), FALSE);
  
  zenity_util_show_dialog (dialog);

  if(data->timeout_delay > 0) {
    g_timeout_add (data->timeout_delay * 1000, (GSourceFunc) zenity_util_timeout_handle, NULL);
  }

  gtk_main ();
}

static void
zenity_scale_value_changed (GtkWidget *widget, gpointer data)
{
  g_print ("%.0f\n", gtk_range_get_value (GTK_RANGE (widget)));
}

static void
zenity_scale_dialog_response (GtkWidget *widget, int response, gpointer data)
{
  ZenityData *zen_data = data;

  switch (response) {
    case GTK_RESPONSE_OK:
      zen_data->exit_code = zenity_util_return_exit_code (ZENITY_OK);
      g_print ("%.0f\n", gtk_range_get_value (GTK_RANGE (scale)));
      break;

    case GTK_RESPONSE_CANCEL:
      zen_data->exit_code = zenity_util_return_exit_code (ZENITY_CANCEL);
      break;

    default:
      zen_data->exit_code = zenity_util_return_exit_code (ZENITY_ESC);
      break;
  }
  gtk_main_quit ();
}
