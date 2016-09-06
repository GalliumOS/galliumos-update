/*
 * option.h
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
 * Authors: Glynn Foster <glynn.foster@sun.com>
 *          Lucas Rocha <lucasr@im.ufba.br>
 */

#include "config.h"

#include "option.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* General Options */
static gchar   *zenity_general_dialog_title;
static gchar   *zenity_general_window_icon;
static int      zenity_general_width;
static int      zenity_general_height;
static gchar   *zenity_general_dialog_text;
static gchar   *zenity_general_separator;
static gboolean zenity_general_multiple;
static gboolean zenity_general_editable;
static gchar   *zenity_general_uri;
static gboolean zenity_general_dialog_no_wrap;
static guint    zenity_general_timeout_delay;

/* Calendar Dialog Options */
static gboolean zenity_calendar_active;
static int      zenity_calendar_day;
static int      zenity_calendar_month;
static int      zenity_calendar_year;
static gchar   *zenity_calendar_date_format;

/* Entry Dialog Options */
static gboolean zenity_entry_active;
static gchar   *zenity_entry_entry_text;
static gboolean zenity_entry_hide_text;

/* Error Dialog Options */
static gboolean zenity_error_active;

/* Info Dialog Options */
static gboolean zenity_info_active;

/* File Selection Dialog Options */
static gboolean zenity_file_active;
static gboolean zenity_file_directory;
static gboolean zenity_file_save;
static gboolean zenity_file_confirm_overwrite;

/* List Dialog Options */
static gboolean zenity_list_active;
static gchar  **zenity_list_columns;
static gboolean zenity_list_checklist;
static gboolean zenity_list_radiolist;
static gchar   *zenity_list_print_column;
static gchar   *zenity_list_hide_column;

/* Notification Dialog Options */
static gboolean zenity_notification_active;
static gboolean zenity_notification_listen;

/* Progress Dialog Options */
static gboolean zenity_progress_active;
static int      zenity_progress_percentage;
static gboolean zenity_progress_pulsate;
static gboolean zenity_progress_auto_close;
static gboolean zenity_progress_auto_kill;

/* Question Dialog Options */
static gboolean zenity_question_active;

/* Text Dialog Options */
static gboolean zenity_text_active;

/* Warning Dialog Options */
static gboolean zenity_warning_active;

/* Scale Dialog Options */
static gboolean zenity_scale_active;
static gint zenity_scale_value;
static gint zenity_scale_min_value;
static gint zenity_scale_max_value;
static gint zenity_scale_step;
static gboolean zenity_scale_print_partial;
static gboolean zenity_scale_hide_value;

/* Miscelaneus Options */
static gboolean zenity_misc_about;
static gboolean zenity_misc_version;

static GOptionEntry general_options[] = {
  {
    "title",
    '\0',
    0,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_title,
    N_("Set the dialog title"),
    N_("TITLE")
  },
  {
    "window-icon",
    '\0',
    0,
    G_OPTION_ARG_FILENAME,
    &zenity_general_window_icon,
    N_("Set the window icon"),
    N_("ICONPATH")
  },
  {
    "width",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_general_width,
    N_("Set the width"),
    N_("WIDTH")
  },
  {
    "height",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_general_height,
    N_("Set the height"),
    N_("HEIGHT")
  },
  {
    "timeout",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_general_timeout_delay,
    N_("Set dialog timeout in seconds"),
    NULL
  },
  {
    NULL
  }
};

static GOptionEntry calendar_options[] = {
  {
    "calendar",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_calendar_active,
    N_("Display calendar dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "day",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_calendar_day,
    N_("Set the calendar day"),
    N_("DAY")
  },
  {
    "month",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_calendar_month,
    N_("Set the calendar month"),
    N_("MONTH")
  },
  {
    "year",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_calendar_year,
    N_("Set the calendar year"),
    N_("YEAR")
  },
  {
    "date-format",
    '\0',
    0,
    G_OPTION_ARG_STRING,
    &zenity_calendar_date_format,
    N_("Set the format for the returned date"),
    N_("PATTERN")
  },
  {
    NULL
  } 
};

static GOptionEntry entry_options[] = {
  {
    "entry",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_entry_active,
    N_("Display text entry dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "entry-text",
    '\0',
    0,
    G_OPTION_ARG_STRING,
    &zenity_entry_entry_text,
    N_("Set the entry text"),
    N_("TEXT")
  },
  {
    "hide-text",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_entry_hide_text,
    N_("Hide the entry text"),
    N_("TEXT")
  },
  { 
    NULL 
  } 
};


static GOptionEntry error_options[] = {
  {
    "error",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_error_active,
    N_("Display error dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "no-wrap",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_dialog_no_wrap,
    N_("Do not enable text wrapping"),
    NULL
  },
  { 
    NULL 
  } 
};

static GOptionEntry info_options[] = {
  {
    "info",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_info_active,
    N_("Display info dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "no-wrap",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_dialog_no_wrap,
    N_("Do not enable text wrapping"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry file_selection_options[] = {
  {
    "file-selection",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_file_active,
    N_("Display file selection dialog"),
    NULL
  },
  {
    "filename",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_FILENAME,
    &zenity_general_uri,
    N_("Set the filename"),
    N_("FILENAME")
  },
  {
    "multiple",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_multiple,
    N_("Allow multiple files to be selected"),
    NULL
  },
  {
    "directory",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_file_directory,
    N_("Activate directory-only selection"),
    NULL
  },
  {
    "save",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_file_save,
    N_("Activate save mode"),
    NULL
  },
  {
    "separator",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_separator,
    N_("Set output separator character"),
    N_("SEPARATOR")
  },
  {
    "confirm-overwrite",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_file_confirm_overwrite,
    N_("Confirm file selection if filename already exists"),
    NULL
  },
  { 
    NULL 
  } 
};

static GOptionEntry list_options[] = {
  {
    "list",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_list_active,
    N_("Display list dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "column",
    '\0',
    0,
    G_OPTION_ARG_STRING_ARRAY,
    &zenity_list_columns,
    N_("Set the column header"),
    N_("COLUMN")
  },
  {
    "checklist",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_list_checklist,
    N_("Use check boxes for first column"),
    NULL
  },
  {
    "radiolist",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_list_radiolist,
    N_("Use radio buttons for first column"),
    NULL
  },
  {
    "separator",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_separator,
    N_("Set output separator character"),
    N_("SEPARATOR")
  },
  {
    "multiple",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_multiple,
    N_("Allow multiple rows to be selected"),
    NULL
  },
  {
    "editable",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_editable,
    N_("Allow changes to text"),
    NULL
  },
  {
    "print-column",
    '\0',
    0,
    G_OPTION_ARG_STRING,
    &zenity_list_print_column,
    N_("Print a specific column (Default is 1. 'ALL' can be used to print all columns)"),
    N_("NUMBER")
  },
  {
    "hide-column",
    '\0',
    0,
    G_OPTION_ARG_STRING,
    &zenity_list_hide_column,
    N_("Hide a specific column"),
    N_("NUMBER")
  },
  { 
    NULL 
  } 
};

static GOptionEntry notification_options[] = {
  {
    "notification",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_notification_active,
    N_("Display notification"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the notification text"),
    N_("TEXT")
  },
  {
    "listen",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_notification_listen,
    N_("Listen for commands on stdin"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry progress_options[] = {
  {
    "progress",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_progress_active,
    N_("Display progress indication dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "percentage",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_progress_percentage,
    N_("Set initial percentage"),
    N_("PERCENTAGE")
  },
  {
    "pulsate",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_progress_pulsate,
    N_("Pulsate progress bar"),
    NULL
  },
  {
    "auto-close",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_progress_auto_close,
    /* xgettext: no-c-format */
    N_("Dismiss the dialog when 100% has been reached"),
    NULL
  },
  {
    "auto-kill",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_progress_auto_kill,
    /* xgettext: no-c-format */
    N_("Kill parent process if cancel button is pressed"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry question_options[] = {
  {
    "question",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_question_active,
    N_("Display question dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "no-wrap",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_dialog_no_wrap,
    N_("Do not enable text wrapping"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry text_options[] = {
  {
    "text-info",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_text_active,
    N_("Display text information dialog"),
    NULL
  },
  {
    "filename",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_FILENAME,
    &zenity_general_uri,
    N_("Open file"),
    N_("FILENAME")
  },
  {
    "editable",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_editable,
    N_("Allow changes to text"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry warning_options[] = {
  {
    "warning",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_warning_active,
    N_("Display warning dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "no-wrap",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_NONE,
    &zenity_general_dialog_no_wrap,
    N_("Do not enable text wrapping"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry scale_options[] = {
  {
    "scale",
    '\0',
    G_OPTION_FLAG_IN_MAIN,
    G_OPTION_ARG_NONE,
    &zenity_scale_active,
    N_("Display scale dialog"),
    NULL
  },
  {
    "text",
    '\0',
    G_OPTION_FLAG_NOALIAS,
    G_OPTION_ARG_STRING,
    &zenity_general_dialog_text,
    N_("Set the dialog text"),
    N_("TEXT")
  },
  {
    "value",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_scale_value,
    N_("Set initial value"),
    N_("VALUE")
  },
  {
    "min-value",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_scale_min_value,
    N_("Set minimum value"),
    N_("VALUE")
  },
  {
    "max-value",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_scale_max_value,
    N_("Set maximum value"),
    N_("VALUE")
  },
  {
    "step",
    '\0',
    0,
    G_OPTION_ARG_INT,
    &zenity_scale_step,
    N_("Set step size"),
    N_("VALUE")
  },
  {
    "print-partial",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_scale_print_partial,
    N_("Print partial values"),
    NULL
  },
  {
    "hide-value",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_scale_hide_value,
    N_("Hide value"),
    NULL
  },
  { 
    NULL 
  }
};

static GOptionEntry miscellaneous_options[] = {
  {
    "about",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_misc_about,
    N_("About zenity"),
    NULL
  },
  {
    "version",
    '\0',
    0,
    G_OPTION_ARG_NONE,
    &zenity_misc_version,
    N_("Print version"),
    NULL
  },
  { 
    NULL 
  }
};

static ZenityParsingOptions *results;
static GOptionContext *ctx;

static void
zenity_option_init (void) {

  results = g_new0 (ZenityParsingOptions, 1);

  /* Initialize the various dialog structures */
  results->mode = MODE_LAST;
  results->data = g_new0 (ZenityData, 1);
  results->calendar_data = g_new0 (ZenityCalendarData, 1);
  results->msg_data = g_new0 (ZenityMsgData, 1);
  results->scale_data = g_new0 (ZenityScaleData, 1);
  results->file_data = g_new0 (ZenityFileData, 1);
  results->entry_data = g_new0 (ZenityEntryData, 1); 
  results->progress_data = g_new0 (ZenityProgressData, 1); 
  results->text_data = g_new0 (ZenityTextData, 1);
  results->tree_data = g_new0 (ZenityTreeData, 1);
  results->notification_data = g_new0 (ZenityNotificationData, 1);
}

void
zenity_option_free (void) {
  if (zenity_general_dialog_title)
    g_free (zenity_general_dialog_title);
  if (zenity_general_window_icon)
    g_free (zenity_general_window_icon);
  if (zenity_general_dialog_text)
    g_free (zenity_general_dialog_text);
  if (zenity_general_uri)
    g_free (zenity_general_uri);
  g_free (zenity_general_separator);

  if (zenity_calendar_date_format)
    g_free (zenity_calendar_date_format);

  if (zenity_entry_entry_text)
    g_free (zenity_entry_entry_text);

  if (zenity_list_columns)
    g_strfreev (zenity_list_columns);
  if (zenity_list_print_column)
    g_free (zenity_list_print_column);
  if (zenity_list_hide_column)
    g_free (zenity_list_hide_column);

  g_option_context_free (ctx);
}

static void
zenity_option_set_dialog_mode (gboolean is_active, ZenityDialogMode mode)  
{
  if (is_active == TRUE) {
    if (results->mode == MODE_LAST) 
      results->mode = mode; 
    else
      zenity_option_error (NULL, ERROR_DIALOG);
  }
}

static gchar *
zenity_option_get_name (GOptionEntry *entries, gpointer arg_data)
{
  int i;

  for (i = 1; entries[i].long_name != NULL; i++) {
    if (entries[i].arg_data == arg_data)
      return (gchar *) entries[i].long_name;
  }
  return NULL;   
}

/* Error callback */
static void 
zenity_option_error_callback (GOptionContext *context,
                              GOptionGroup   *group,
			      gpointer        data,
			      GError        **error)
{
  zenity_option_error (NULL, ERROR_SYNTAX);
}

/* Pre parse callbacks set the default option values */

static gboolean
zenity_general_pre_callback (GOptionContext *context,
		             GOptionGroup   *group,
		             gpointer	     data,
		             GError        **error)
{
  zenity_general_dialog_title = NULL;
  zenity_general_window_icon = NULL;
  zenity_general_width = -1;
  zenity_general_height = -1;
  zenity_general_dialog_text = NULL;
  zenity_general_separator = g_strdup ("|");
  zenity_general_multiple = FALSE;
  zenity_general_editable = FALSE;
  zenity_general_uri = NULL;
  zenity_general_dialog_no_wrap = FALSE;
  zenity_general_timeout_delay = -1;

  return TRUE;
}

static gboolean
zenity_calendar_pre_callback (GOptionContext *context,
		              GOptionGroup   *group,
		              gpointer        data,
		              GError        **error)
{
  zenity_calendar_active = FALSE;
  zenity_calendar_date_format = NULL; 
  zenity_calendar_day = -1;
  zenity_calendar_month = -1;
  zenity_calendar_year = -1;

  return TRUE;
}

static gboolean
zenity_entry_pre_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_entry_active = FALSE;
  zenity_entry_entry_text = NULL;
  zenity_entry_hide_text = FALSE;

  return TRUE;
}

static gboolean
zenity_error_pre_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_error_active = FALSE;

  return TRUE;
}

static gboolean
zenity_info_pre_callback (GOptionContext *context,
		          GOptionGroup   *group,
		          gpointer	  data,
		          GError        **error)
{
  zenity_info_active = FALSE;

  return TRUE;
}

static gboolean
zenity_file_pre_callback (GOptionContext *context,
		          GOptionGroup   *group,
		          gpointer	  data,
		          GError        **error)
{
  zenity_file_active = FALSE;
  zenity_file_directory = FALSE;
  zenity_file_save = FALSE;
  zenity_file_confirm_overwrite = FALSE;

  return TRUE;
}

static gboolean
zenity_list_pre_callback (GOptionContext *context,
		          GOptionGroup   *group,
		          gpointer	  data,
		          GError        **error)
{
  zenity_list_active = FALSE;
  zenity_list_columns = NULL;
  zenity_list_checklist = FALSE;
  zenity_list_radiolist = FALSE;
  zenity_list_print_column = NULL;
  zenity_list_hide_column = NULL;

  return TRUE;
}

static gboolean
zenity_notification_pre_callback (GOptionContext *context,
		                  GOptionGroup   *group,
		                  gpointer	  data,
		                  GError        **error)
{
  zenity_notification_active = FALSE;
  zenity_notification_listen = FALSE;

  return TRUE;
}

static gboolean
zenity_progress_pre_callback (GOptionContext *context,
		              GOptionGroup   *group,
		              gpointer	      data,
		              GError        **error)
{
  zenity_progress_active = FALSE;
  zenity_progress_percentage = 0;
  zenity_progress_pulsate = FALSE;
  zenity_progress_auto_close = FALSE;
  zenity_progress_auto_kill = FALSE;

  return TRUE;
}

static gboolean
zenity_question_pre_callback (GOptionContext *context,
		              GOptionGroup   *group,
		              gpointer	      data,
		              GError        **error)
{
  zenity_question_active = FALSE;

  return TRUE;
}

static gboolean
zenity_text_pre_callback (GOptionContext *context,
		          GOptionGroup   *group,
		          gpointer	  data,
		          GError        **error)
{
  zenity_text_active = FALSE;

  return TRUE;
}

static gboolean
zenity_warning_pre_callback (GOptionContext *context,
		             GOptionGroup   *group,
		             gpointer	     data,
		             GError        **error)
{
  zenity_warning_active = FALSE;

  return TRUE;
}

static gboolean
zenity_scale_pre_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer        data,
		           GError        **error)
{
  zenity_scale_active = FALSE;
  zenity_scale_value = 0;
  zenity_scale_min_value = 0;
  zenity_scale_max_value = 100;
  zenity_scale_step = 1;
  zenity_scale_print_partial = FALSE;
  zenity_scale_hide_value = FALSE;

  return TRUE;
}

static gboolean
zenity_misc_pre_callback (GOptionContext *context,
		          GOptionGroup   *group,
		          gpointer	  data,
		          GError        **error)
{
  zenity_misc_about = FALSE;
  zenity_misc_version = FALSE;

  return TRUE;
}

/* Post parse callbacks assign the option values to
   parsing result and makes some post condition tests */

static gboolean
zenity_general_post_callback (GOptionContext *context,
		              GOptionGroup   *group,
		              gpointer	      data,
		              GError        **error)
{
  results->data->dialog_title = zenity_general_dialog_title;
  results->data->window_icon = zenity_general_window_icon;
  results->data->width = zenity_general_width;
  results->data->height = zenity_general_height;
  results->data->timeout_delay=zenity_general_timeout_delay;
  return TRUE;
}

static gboolean
zenity_calendar_post_callback (GOptionContext *context,
		               GOptionGroup   *group,
		               gpointer	       data,
		               GError        **error)
{
  zenity_option_set_dialog_mode (zenity_calendar_active, MODE_CALENDAR);

  if (results->mode == MODE_CALENDAR) {
    struct tm *t;
    time_t current_time;

    time (&current_time);
    t = localtime (&current_time);

    if (zenity_calendar_day < 0)
       zenity_calendar_day = t->tm_mday;
    if (zenity_calendar_month < 0)
       zenity_calendar_month = t->tm_mon + 1;
    if (zenity_calendar_year < 0)
       zenity_calendar_year = t->tm_year + 1900;

    results->calendar_data->dialog_text = zenity_general_dialog_text;
    results->calendar_data->day = zenity_calendar_day;
    results->calendar_data->month = zenity_calendar_month;
    results->calendar_data->year = zenity_calendar_year;
    if (zenity_calendar_date_format)
      results->calendar_data->date_format = zenity_calendar_date_format;
    else
      results->calendar_data->date_format = g_locale_to_utf8 (nl_langinfo (D_FMT), -1, NULL, NULL, NULL);

  } else {
    if (zenity_calendar_day > -1)
      zenity_option_error (zenity_option_get_name (calendar_options, &zenity_calendar_day),
                           ERROR_SUPPORT);
    
    if (zenity_calendar_month > -1)
      zenity_option_error (zenity_option_get_name (calendar_options, &zenity_calendar_month),
                           ERROR_SUPPORT);

    if (zenity_calendar_year > -1)
      zenity_option_error (zenity_option_get_name (calendar_options, &zenity_calendar_year),
                           ERROR_SUPPORT);

    if (zenity_calendar_date_format)
      zenity_option_error (zenity_option_get_name (calendar_options, &zenity_calendar_date_format),
                           ERROR_SUPPORT);
  }
    
  return TRUE;
}

static gboolean
zenity_entry_post_callback (GOptionContext *context,
		            GOptionGroup   *group,
		            gpointer	    data,
		            GError        **error)
{
  zenity_option_set_dialog_mode (zenity_entry_active, MODE_ENTRY);
  
  if (results->mode == MODE_ENTRY) {
    results->entry_data->dialog_text = zenity_general_dialog_text;
    results->entry_data->entry_text = zenity_entry_entry_text;
    results->entry_data->hide_text= zenity_entry_hide_text;
  } else {
    if (zenity_entry_entry_text)
      zenity_option_error (zenity_option_get_name (entry_options, &zenity_entry_entry_text),
                           ERROR_SUPPORT);
    
    if (zenity_entry_hide_text)
      zenity_option_error (zenity_option_get_name (entry_options, &zenity_entry_hide_text),
                           ERROR_SUPPORT);
  }
    
  return TRUE;
}

static gboolean
zenity_error_post_callback (GOptionContext *context,
		            GOptionGroup   *group,
		            gpointer	    data,
		            GError        **error)
{
  zenity_option_set_dialog_mode (zenity_error_active, MODE_ERROR);

  if (results->mode == MODE_ERROR) {
    results->msg_data->dialog_text = zenity_general_dialog_text;
    results->msg_data->mode = ZENITY_MSG_ERROR; 
    results->msg_data->no_wrap = zenity_general_dialog_no_wrap; 
  }
    
  return TRUE;
}

static gboolean
zenity_info_post_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_option_set_dialog_mode (zenity_info_active, MODE_INFO);

  if (results->mode == MODE_INFO) {
    results->msg_data->dialog_text = zenity_general_dialog_text;
    results->msg_data->mode = ZENITY_MSG_INFO; 
    results->msg_data->no_wrap = zenity_general_dialog_no_wrap; 
  }
  
  return TRUE;
}

static gboolean
zenity_file_post_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_option_set_dialog_mode (zenity_file_active, MODE_FILE);

  if (results->mode == MODE_FILE) {
    results->file_data->uri = zenity_general_uri;
    results->file_data->multi = zenity_general_multiple;
    results->file_data->directory = zenity_file_directory;
    results->file_data->save = zenity_file_save;
    results->file_data->confirm_overwrite = zenity_file_confirm_overwrite;
    results->file_data->separator = zenity_general_separator;
  } else {
    if (zenity_file_directory)
      zenity_option_error (zenity_option_get_name (file_selection_options, &zenity_file_directory),
                           ERROR_SUPPORT);

    if (zenity_file_save)
      zenity_option_error (zenity_option_get_name (file_selection_options, &zenity_file_save),
                           ERROR_SUPPORT);
  }
    
  return TRUE;
}

static gboolean
zenity_list_post_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  int i = 0;
  gchar *column;
    
  zenity_option_set_dialog_mode (zenity_list_active, MODE_LIST);

  if (results->mode == MODE_LIST) {
    results->tree_data->dialog_text = zenity_general_dialog_text;
    
    if (zenity_list_columns) {
      column = zenity_list_columns[0];
      while (column != NULL) {
        results->tree_data->columns = g_slist_append (results->tree_data->columns, column);
        column = zenity_list_columns[++i]; 
      }
    }
    
    results->tree_data->checkbox = zenity_list_checklist;
    results->tree_data->radiobox = zenity_list_radiolist;
    results->tree_data->multi = zenity_general_multiple;
    results->tree_data->editable = zenity_general_editable;
    results->tree_data->print_column = zenity_list_print_column;
    results->tree_data->hide_column = zenity_list_hide_column;
    results->tree_data->separator = zenity_general_separator;
  } else {
    if (zenity_list_columns)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_list_columns),
                           ERROR_SUPPORT);

    if (zenity_list_checklist)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_list_checklist),
                           ERROR_SUPPORT);

    if (zenity_list_radiolist)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_list_radiolist),
                           ERROR_SUPPORT);

    if (zenity_list_print_column)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_list_print_column),
                           ERROR_SUPPORT);

    if (zenity_list_hide_column)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_list_hide_column),
                           ERROR_SUPPORT);
  }
    
  return TRUE;
}

static gboolean
zenity_notification_post_callback (GOptionContext *context,
		                   GOptionGroup   *group,
		                   gpointer	   data,
		                   GError        **error)
{
  zenity_option_set_dialog_mode (zenity_notification_active, MODE_NOTIFICATION);

  if (results->mode == MODE_NOTIFICATION) {
    results->notification_data->notification_text = zenity_general_dialog_text;
    results->notification_data->listen = zenity_notification_listen;
  } else {
    if (zenity_notification_listen)
      zenity_option_error (zenity_option_get_name (notification_options, &zenity_notification_listen),
                           ERROR_SUPPORT);
  }

  return TRUE;
}

static gboolean
zenity_progress_post_callback (GOptionContext *context,
		               GOptionGroup   *group,
		               gpointer	       data,
		               GError        **error)
{
  zenity_option_set_dialog_mode (zenity_progress_active, MODE_PROGRESS);

  if (results->mode == MODE_PROGRESS) {
    results->progress_data->dialog_text = zenity_general_dialog_text;
    results->progress_data->pulsate = zenity_progress_pulsate;
    results->progress_data->autoclose = zenity_progress_auto_close;
    results->progress_data->autokill = zenity_progress_auto_kill;
    results->progress_data->percentage = zenity_progress_percentage;
  } else {
    if (zenity_progress_pulsate)
      zenity_option_error (zenity_option_get_name (progress_options, &zenity_progress_pulsate),
                           ERROR_SUPPORT);

    if (zenity_progress_percentage)
      zenity_option_error (zenity_option_get_name (progress_options, &zenity_progress_percentage),
                           ERROR_SUPPORT);

    if (zenity_progress_auto_close)
      zenity_option_error (zenity_option_get_name (progress_options, &zenity_progress_auto_close),
                           ERROR_SUPPORT);
                           
    if (zenity_progress_auto_kill)
      zenity_option_error (zenity_option_get_name (progress_options, &zenity_progress_auto_kill),
                           ERROR_SUPPORT);
  }
    
  return TRUE;
}

static gboolean
zenity_question_post_callback (GOptionContext *context,
		               GOptionGroup   *group,
		               gpointer	       data,
		               GError        **error)
{
  zenity_option_set_dialog_mode (zenity_question_active, MODE_QUESTION);


  if (results->mode == MODE_QUESTION) {
    results->msg_data->dialog_text = zenity_general_dialog_text;
    results->msg_data->mode = ZENITY_MSG_QUESTION;
    results->msg_data->no_wrap = zenity_general_dialog_no_wrap; 
  }

  return TRUE;
}

static gboolean
zenity_text_post_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_option_set_dialog_mode (zenity_text_active, MODE_TEXTINFO);

  if (results->mode == MODE_TEXTINFO) {
    results->text_data->uri = zenity_general_uri;
    results->text_data->editable = zenity_general_editable;
  } 
    
  return TRUE;
}

static gboolean
zenity_warning_post_callback (GOptionContext *context,
		              GOptionGroup   *group,
		              gpointer	      data,
		              GError        **error)
{
  zenity_option_set_dialog_mode (zenity_warning_active, MODE_WARNING);

  if (results->mode == MODE_WARNING) {
    results->msg_data->dialog_text = zenity_general_dialog_text;
    results->msg_data->mode = ZENITY_MSG_WARNING;
    results->msg_data->no_wrap = zenity_general_dialog_no_wrap; 
  }

  return TRUE;
}

static gboolean
zenity_scale_post_callback (GOptionContext *context,
	                    GOptionGroup   *group,
		            gpointer        data,
		            GError        **error)
{
  zenity_option_set_dialog_mode (zenity_scale_active, MODE_SCALE);

  if (results->mode == MODE_SCALE) {
    results->scale_data->dialog_text = zenity_general_dialog_text;
    results->scale_data->value = zenity_scale_value;
    results->scale_data->min_value = zenity_scale_min_value;
    results->scale_data->max_value = zenity_scale_max_value;
    results->scale_data->step = zenity_scale_step;
    results->scale_data->print_partial = zenity_scale_print_partial;
    results->scale_data->hide_value = zenity_scale_hide_value;
  }

  return TRUE;
}

static gboolean
zenity_misc_post_callback (GOptionContext *context,
		           GOptionGroup   *group,
		           gpointer	   data,
		           GError        **error)
{
  zenity_option_set_dialog_mode (zenity_misc_about, MODE_ABOUT);
  zenity_option_set_dialog_mode (zenity_misc_version, MODE_VERSION);
  
  return TRUE;
}

static GOptionContext *
zenity_create_context (void) 
{
  GOptionContext *tmp_ctx;
  GOptionGroup *a_group;

  tmp_ctx = g_option_context_new(NULL); 
  
  /* Adds general option entries */
  a_group = g_option_group_new("general", 
                               N_("General options"), 
                               N_("Show general options"), NULL, NULL);
  g_option_group_add_entries(a_group, general_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_general_pre_callback, zenity_general_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds calendar option entries */
  a_group = g_option_group_new("calendar", 
                               N_("Calendar options"), 
                               N_("Show calendar options"), NULL, NULL);
  g_option_group_add_entries(a_group, calendar_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_calendar_pre_callback, zenity_calendar_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds entry option entries */
  a_group = g_option_group_new("entry", 
                               N_("Text entry options"), 
                               N_("Show text entry options"), NULL, NULL);
  g_option_group_add_entries(a_group, entry_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_entry_pre_callback, zenity_entry_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds error option entries */
  a_group = g_option_group_new("error", 
                               N_("Error options"), 
                               N_("Show error options"), NULL, NULL);
  g_option_group_add_entries(a_group, error_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_error_pre_callback, zenity_error_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds info option entries */
  a_group = g_option_group_new("info", 
                               N_("Info options"), 
                               N_("Show info options"), NULL, NULL);
  g_option_group_add_entries(a_group, info_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_info_pre_callback, zenity_info_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds file selection option entries */
  a_group = g_option_group_new("file-selection", 
                               N_("File selection options"), 
                               N_("Show file selection options"), NULL, NULL);
  g_option_group_add_entries(a_group, file_selection_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_file_pre_callback, zenity_file_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds list option entries */
  a_group = g_option_group_new("list", 
                               N_("List options"), 
                               N_("Show list options"), NULL, NULL);
  g_option_group_add_entries(a_group, list_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_list_pre_callback, zenity_list_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds notification option entries */
  a_group = g_option_group_new("notification", 
                               N_("Notification icon options"), 
                               N_("Show notification icon options"), NULL, NULL);
  g_option_group_add_entries(a_group, notification_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_notification_pre_callback, zenity_notification_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds progress option entries */
  a_group = g_option_group_new("progress", 
                               N_("Progress options"), 
                               N_("Show progress options"), NULL, NULL);
  g_option_group_add_entries(a_group, progress_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_progress_pre_callback, zenity_progress_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds question option entries */
  a_group = g_option_group_new("question", 
                               N_("Question options"), 
                               N_("Show question options"), NULL, NULL);
  g_option_group_add_entries(a_group, question_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_question_pre_callback, zenity_question_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds warning option entries */
  a_group = g_option_group_new("warning", 
                               N_("Warning options"), 
                               N_("Show warning options"), NULL, NULL);
  g_option_group_add_entries(a_group, warning_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_warning_pre_callback, zenity_warning_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds scale option entries */
  a_group = g_option_group_new("scale", 
                               N_("Scale options"), 
                               N_("Show scale options"), NULL, NULL);
  g_option_group_add_entries(a_group, scale_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_scale_pre_callback, zenity_scale_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds text option entries */
  a_group = g_option_group_new("text-info", 
                               N_("Text information options"), 
                               N_("Show text information options"), NULL, NULL);
  g_option_group_add_entries(a_group, text_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_text_pre_callback, zenity_text_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds misc option entries */
  a_group = g_option_group_new("misc", 
                               N_("Miscellaneous options"), 
                               N_("Show miscellaneous options"), NULL, NULL);
  g_option_group_add_entries(a_group, miscellaneous_options);
  g_option_group_set_parse_hooks (a_group,
                    zenity_misc_pre_callback, zenity_misc_post_callback);
  g_option_group_set_error_hook (a_group, zenity_option_error_callback);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Adds gtk option entries */
  a_group = gtk_get_option_group(TRUE);
  g_option_group_set_translation_domain (a_group, GETTEXT_PACKAGE);
  g_option_context_add_group(tmp_ctx, a_group);
  
  /* Enable help options */
  g_option_context_set_help_enabled (tmp_ctx, TRUE);
  g_option_context_set_ignore_unknown_options (tmp_ctx, FALSE);

  return tmp_ctx;
}

void
zenity_option_error (gchar *string, ZenityError error)
{
  switch (error) {
    case ERROR_SYNTAX:
      g_printerr (_("This option is not available. Please see --help for all possible usages.\n"));
      zenity_option_free ();
      exit (-1);
    case ERROR_SUPPORT:
      g_printerr (_("--%s is not supported for this dialog\n"), string);
      zenity_option_free ();
      exit (-1);
    case ERROR_DIALOG:
      g_printerr (_("Two or more dialog options specified\n"));
      zenity_option_free ();
      exit (-1);
    default:
      return;
  }
}

ZenityParsingOptions *
zenity_option_parse (gint argc, gchar **argv) 
{
  GError *error = NULL;

  zenity_option_init ();

  ctx = zenity_create_context ();
  
  g_option_context_parse (ctx, &argc, &argv, &error);

  /* Some option pointer a shared among more than one group and don't
     have their post condition tested. This test is done here. */
  
  if (zenity_general_dialog_text)
    if (results->mode == MODE_ABOUT || results->mode == MODE_VERSION)
      zenity_option_error (zenity_option_get_name (calendar_options, &zenity_general_dialog_text), ERROR_SUPPORT);
  
  if (strcmp (zenity_general_separator, "|") != 0)
    if (results->mode != MODE_LIST && results->mode != MODE_FILE)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_general_separator), ERROR_SUPPORT);
  
  if (zenity_general_multiple)
    if (results->mode != MODE_FILE && results->mode != MODE_LIST)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_general_multiple), ERROR_SUPPORT);

  if (zenity_general_editable)
    if (results->mode != MODE_TEXTINFO && results->mode != MODE_LIST)
      zenity_option_error (zenity_option_get_name (list_options, &zenity_general_editable), ERROR_SUPPORT);

  if (zenity_general_uri)
    if (results->mode != MODE_FILE && results->mode != MODE_TEXTINFO)
      zenity_option_error (zenity_option_get_name (text_options, &zenity_general_uri), ERROR_SUPPORT);
  
  if (zenity_general_dialog_no_wrap)
    if (results->mode != MODE_INFO && results->mode != MODE_ERROR && results->mode != MODE_QUESTION && results->mode != MODE_WARNING)
      zenity_option_error (zenity_option_get_name (text_options, &zenity_general_dialog_no_wrap), ERROR_SUPPORT);
  
  return results; 
}
