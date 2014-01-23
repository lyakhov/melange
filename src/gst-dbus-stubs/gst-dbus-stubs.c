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

#include <gio/gio.h>
#include <string.h>

void gst_message_parse_error(GstMessage *message, GError **gerror, gchar **debug)
{
}

void gst_init(int *argc, char **argv[])
{
}

GstElement *gst_element_factory_make(const gchar *factoryname, const gchar *name)
{
	GDBusProxy *proxy = NULL;
	GVariant *variant = NULL;
	GError *error = NULL;
	gchar *pipeline_object_path = NULL;

	proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"com.ridgerun.gstreamer.gstd",
		"/com/ridgerun/gstreamer/gstd/factory",
		"com.ridgerun.gstreamer.gstd.FactoryInterface",
		NULL,
		&error);

	if (error)
	{
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return NULL;
	}

	variant = NULL;
	variant = g_dbus_proxy_call_sync(proxy,
		"Create",
		g_variant_new("(s)", "playbin"),
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);

	if (proxy)
		g_object_unref(proxy);
	if (error)
	{
		g_printerr("g_dbus_proxy_call_sync failed: %s\n", error->message);
		return NULL;
	}

	if (g_variant_is_container(variant) && (g_variant_n_children(variant) == 1))
	{
		GVariant *pipeline_variant = g_variant_get_child_value(variant, 0);
		pipeline_object_path = g_variant_dup_string(pipeline_variant, NULL);
	}

	error = NULL;
	proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"com.ridgerun.gstreamer.gstd",
		pipeline_object_path,
		"com.ridgerun.gstreamer.gstd.PipelineInterface",
		NULL,
		&error);
	if (error)
	{
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return NULL;
	}

	GstElement *element = g_object_new(GST_TYPE_ELEMENT, NULL);

	if (pipeline_object_path)
		g_free(pipeline_object_path);
	return element;
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

static gboolean
file_path_contains_relatives (const gchar * path)
{
	return (strstr(path, "/./") != NULL || strstr(path, "/../") != NULL ||
		strstr(path, G_DIR_SEPARATOR_S "." G_DIR_SEPARATOR_S) != NULL ||
		strstr(path, G_DIR_SEPARATOR_S ".." G_DIR_SEPARATOR_S) != NULL);
}

static gchar *
gst_file_utils_canonicalise_path (const gchar * path)
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
