/* gst-dbus-stubs.c: GStreamer API stubs redirecting calls to gstd, the GStreamer D-Bus Daemon
 *
 * Copyright 2014 Fedor Lyakhov <fedor.lyakhov@gmail.com>
 * Copyright (C) 1999,2000 Erik Walthinsen <omega@cse.ogi.edu>
 *                    2000 Wim Taymans <wtay@chello.be>
 * Copyright (C) 2011 Tim-Philipp MÃ¼ller <tim centricular net>
 * Copyright 2014 Alexey Kuzin <amkuzink@gmail.com>
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
 */

#include "gst/gst.h"
#include "gst-element-private-stub.h"
#include "gst-bus-private-stub.h"
#include "gstd-factory-interface.h"
#include "gstd-pipeline-interface.h"

#include <gio/gio.h>
#include <string.h>


static void on_pipeline_proxy_signal(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name,
	GVariant *parameters, gpointer user_data)
{
	GstBus *bus = GST_BUS(user_data);

	g_print("Sender name: %s\n", sender_name);
	g_print("signal name: %s\n", signal_name);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_set_remote_property(GObject *object, GParamSpec *pspec, gpointer user_data)
{
	GVariant *variant = NULL;
	GValue new_uri_value = G_VALUE_INIT;
	gchar *new_uri_string = NULL;
	GDBusProxy *proxy = gst_element_get_proxy(GST_ELEMENT(object));

	if (strcmp(g_param_spec_get_name(pspec), "uri")) {
		return;
	}

	g_value_init(&new_uri_value, G_TYPE_STRING);
	g_object_get_property(object, "uri", &new_uri_value);
	new_uri_string = g_value_dup_string(&new_uri_value);

	variant = gstd_pipeline_element_set_property_string(proxy, "plbn", "uri", new_uri_string);

	g_value_unset(&new_uri_value);
	g_variant_unref(variant);
	g_object_unref(proxy);
	g_free(new_uri_string);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void gst_message_parse_error(GstMessage *message, GError **gerror, gchar **debug)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void gst_init(int *argc, char **argv[])
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GstElement *gst_element_factory_make(const gchar *factoryname, const gchar *name)
{
	GDBusProxy *pipeline_proxy = NULL;

	pipeline_proxy = gstd_factory_create(G_BUS_TYPE_SESSION,
		g_variant_new("(s)", "( playbin name=plbn )"));

	GstElement *element = g_object_new(GST_TYPE_ELEMENT, NULL);
	gst_element_set_proxy(element, pipeline_proxy);

	g_signal_connect(element,
		"notify",
		G_CALLBACK(gst_element_set_remote_property),
		NULL);

	g_object_unref(pipeline_proxy);
	return element;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GstBus *gst_element_get_bus(GstElement *element)
{
	GstBus *bus = g_object_new(GST_TYPE_BUS, NULL);
	GDBusProxy *proxy = gst_element_get_proxy(element);
	gst_bus_set_proxy(bus, proxy);

	g_object_unref(proxy);
	return bus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GstStateChangeReturn gst_element_set_state(GstElement *element, GstState state)
{
	GVariant *variant = NULL;
	GDBusProxy *proxy = gst_element_get_proxy(element);
	GstStateChangeReturn return_state = GST_STATE_CHANGE_FAILURE;

	variant = gstd_pipeline_set_state(proxy, state);

	if (variant) {
		g_variant_unref(variant);
		return_state = GST_STATE_CHANGE_SUCCESS;
	}

	g_object_unref(proxy);
	return return_state;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
guint gst_bus_add_watch(GstBus *bus, GstBusFunc func, gpointer user_data)
{
	GDBusProxy *proxy = gst_bus_get_proxy(bus);

	// This is temporary solution
	bus->priv->bus_func = func;
	bus->priv->user_data = user_data;

	g_signal_connect(proxy,
		"g-signal",
		G_CALLBACK(on_pipeline_proxy_signal),
		g_object_ref(bus));

	g_object_unref(proxy);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// The following functions were copied from 'gst/gsturi.c' file of GStreamer
gboolean gst_uri_is_valid(const gchar *uri)
{
	gchar *endptr;

	g_return_val_if_fail(uri != NULL, FALSE);

	gchar *check = (gchar *)uri;

	g_assert(uri != NULL);
	g_assert(&endptr != NULL);

	if (g_ascii_isalpha (*check))
	{
		check++;
		while (g_ascii_isalnum (*check) || *check == '+'
			|| *check == '-' || *check == '.')
			check++;
	}
	endptr = check;

	return *endptr == ':';
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static gboolean file_path_contains_relatives(const gchar * path)
{
	return (strstr(path, "/./") != NULL || strstr(path, "/../") != NULL ||
		strstr(path, G_DIR_SEPARATOR_S "." G_DIR_SEPARATOR_S) != NULL ||
		strstr(path, G_DIR_SEPARATOR_S ".." G_DIR_SEPARATOR_S) != NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static gchar *gst_file_utils_canonicalise_path(const gchar * path)
{
	gchar **parts, **p, *clean_path;

	parts = g_strsplit (path, "/", -1);

	p = parts;
	while (*p != NULL) {
		if (strcmp (*p, ".") == 0) {
			/* just move all following parts on top of this, incl. NUL terminator */
			g_free (*p);
			g_memmove (p, p + 1, (g_strv_length (p + 1) + 1) * sizeof (gchar *));
			/* re-check the new current part again in the next iteration */
			continue;
		} else if (strcmp (*p, "..") == 0 && p > parts) {
			/* just move all following parts on top of the previous part, incl.
			 * NUL terminator */
			g_free (*(p - 1));
			g_free (*p);
			g_memmove (p - 1, p + 1, (g_strv_length (p + 1) + 1) * sizeof (gchar *));
			/* re-check the new current part again in the next iteration */
			--p;
			continue;
		}
		++p;
	}
	if (*path == '/') {
		guint num_parts;

		num_parts = g_strv_length (parts) + 1;      /* incl. terminator */
		parts = g_renew (gchar *, parts, num_parts + 1);
		g_memmove (parts + 1, parts, num_parts * sizeof (gchar *));
		parts[0] = g_strdup ("/");
	}

	clean_path = g_build_filenamev (parts);
	g_strfreev (parts);
	return clean_path;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
gchar *gst_filename_to_uri(const gchar *filename, GError **error)
{
	gchar *abs_location = NULL;
	gchar *uri, *abs_clean;

	g_return_val_if_fail (filename != NULL, NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	if (g_path_is_absolute (filename)) {
		if (!file_path_contains_relatives (filename)) {
			uri = g_filename_to_uri (filename, NULL, error);
			goto beach;
		}

		abs_location = g_strdup (filename);
	} else {
		gchar *cwd;

		cwd = g_get_current_dir ();
		abs_location = g_build_filename (cwd, filename, NULL);
		g_free (cwd);

		if (!file_path_contains_relatives (abs_location)) {
			uri = g_filename_to_uri (abs_location, NULL, error);
			goto beach;
		}
	}

	/* path is now absolute, but contains '.' or '..' */
	abs_clean = gst_file_utils_canonicalise_path (abs_location);
	g_print ("'%s' -> '%s' -> '%s'", filename, abs_location, abs_clean);
	uri = g_filename_to_uri (abs_clean, NULL, error);
	g_free (abs_clean);

beach:
	g_free (abs_location);
	g_print ("'%s' -> '%s'", filename, uri);
	return uri;
}
