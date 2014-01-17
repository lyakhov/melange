/* gst.h: GStreamer API stubs header
 *
 * Copyright 2014 Fedor Lyakhov <fedor.lyakhov@gmail.com>
 *
 * This file is part of Melange.
 *
 * Melange is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Melange is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __GST_H__
#define __GST_H__

#include <glib.h>

typedef enum
{
  GST_MESSAGE_UNKNOWN           = 0,
  GST_MESSAGE_EOS               = (1 << 0),
  GST_MESSAGE_ERROR             = (1 << 1),
  GST_MESSAGE_WARNING           = (1 << 2),
  GST_MESSAGE_INFO              = (1 << 3),
  GST_MESSAGE_TAG               = (1 << 4),
  GST_MESSAGE_BUFFERING         = (1 << 5),
  GST_MESSAGE_STATE_CHANGED     = (1 << 6),
  GST_MESSAGE_STATE_DIRTY       = (1 << 7),
  GST_MESSAGE_STEP_DONE         = (1 << 8),
  GST_MESSAGE_CLOCK_PROVIDE     = (1 << 9),
  GST_MESSAGE_CLOCK_LOST        = (1 << 10),
  GST_MESSAGE_NEW_CLOCK         = (1 << 11),
  GST_MESSAGE_STRUCTURE_CHANGE  = (1 << 12),
  GST_MESSAGE_STREAM_STATUS     = (1 << 13),
  GST_MESSAGE_APPLICATION       = (1 << 14),
  GST_MESSAGE_ELEMENT           = (1 << 15),
  GST_MESSAGE_SEGMENT_START     = (1 << 16),
  GST_MESSAGE_SEGMENT_DONE      = (1 << 17),
  GST_MESSAGE_DURATION_CHANGED  = (1 << 18),
  GST_MESSAGE_LATENCY           = (1 << 19),
  GST_MESSAGE_ASYNC_START       = (1 << 20),
  GST_MESSAGE_ASYNC_DONE        = (1 << 21),
  GST_MESSAGE_REQUEST_STATE     = (1 << 22),
  GST_MESSAGE_STEP_START        = (1 << 23),
  GST_MESSAGE_QOS               = (1 << 24),
  GST_MESSAGE_PROGRESS          = (1 << 25),
  GST_MESSAGE_TOC               = (1 << 26),
  GST_MESSAGE_RESET_TIME        = (1 << 27),
  GST_MESSAGE_STREAM_START      = (1 << 28),
  GST_MESSAGE_NEED_CONTEXT      = (1 << 29),
  GST_MESSAGE_HAVE_CONTEXT      = (1 << 30),
  GST_MESSAGE_ANY               = ~0
} GstMessageType;

#define GST_MESSAGE_CAST(obj)      ((GstMessage*)(obj))
#define GST_MESSAGE_TYPE(message)  (GST_MESSAGE_CAST(message)->type)

typedef enum {
  GST_STATE_CHANGE_FAILURE    = 0,
  GST_STATE_CHANGE_SUCCESS    = 1,
  GST_STATE_CHANGE_ASYNC      = 2,
  GST_STATE_CHANGE_NO_PREROLL = 3
} GstStateChangeReturn;

typedef enum {
  GST_STATE_VOID_PENDING = 0,
  GST_STATE_NULL         = 1,
  GST_STATE_READY        = 2,
  GST_STATE_PAUSED       = 3,
  GST_STATE_PLAYING      = 4
} GstState;

/* These structs must be GObjects... supporting g_object_unref */
/* GstElement must be a GObject and support URI property, it is called as
   g_object_set(playbin, "uri", uri, NULL); */
typedef struct _GstElement GstElement;
typedef struct _GstBus GstBus;
typedef struct _GstMessage GstMessage;

struct _GstElement
{
};

struct _GstBus
{
};

struct _GstMessage
{
	GstMessageType type;
};

typedef gboolean (*GstBusFunc)(GstBus *bus, GstMessage *message, gpointer user_data);
void gst_message_parse_error(GstMessage *message, GError **gerror, gchar **debug);

void gst_init(int *argc, char **argv[]);
GstElement *gst_element_factory_make(const gchar *factoryname, const gchar *name); /* G_GNUC_MALLOC */
GstBus *gst_element_get_bus(GstElement *element);
GstStateChangeReturn gst_element_set_state(GstElement *element, GstState state);

/* Must return id usable with g_source_remove() later */
guint gst_bus_add_watch(GstBus *bus, GstBusFunc func, gpointer user_data); 

/* URI operations are better done by direct calls to actual GStreamer library... */
gboolean gst_uri_is_valid(const gchar *uri);
gchar *gst_filename_to_uri(const gchar *filename, GError **error); /* G_GNUC_MALLOC */

#endif /* __GST_H__ */