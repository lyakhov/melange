/* gst-dbus-stubs.c: GStreamer API stubs redirecting calls to gstd, the GStreamer D-Bus Daemon
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
#include "gst/gst.h"

void gst_message_parse_error(GstMessage *message, GError **gerror, gchar **debug)
{
}

void gst_init(int *argc, char **argv[])
{
}

GstElement *gst_element_factory_make(const gchar *factoryname, const gchar *name)
{
	return NULL;
}

GstBus *gst_element_get_bus(GstElement *element)
{
	return NULL;
}

GstStateChangeReturn gst_element_set_state(GstElement *element, GstState state)
{
	return GST_STATE_CHANGE_FAILURE;
}

guint gst_bus_add_watch(GstBus *bus, GstBusFunc func, gpointer user_data)
{
	return 0;
}

gboolean gst_uri_is_valid(const gchar *uri)
{
	return FALSE;
}

gchar *gst_filename_to_uri(const gchar *filename, GError **error)
{
	return NULL;
}
