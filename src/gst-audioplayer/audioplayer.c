/* audioplayer.c: console audio player
 *
 * Copyright 2011 Stefan Kost
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
 * This file was derived from helloworld.c test/example of GStreamer framework.
 */

#include <gst/gst.h>
#include <glib.h>

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	GMainLoop *loop = (GMainLoop *) data;

	switch(GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_EOS: {
		g_print("End-of-stream\n");
		g_main_loop_quit(loop);
		break;
	}
	case GST_MESSAGE_ERROR: {
		gchar *debug;
		GError *err;

		gst_message_parse_error(msg, &err, &debug);
		g_printerr("Debugging info: %s\n", (debug) ? debug : "none");
		g_free(debug);

		g_print("Error: %s\n", err->message);
		g_error_free(err);

		g_main_loop_quit(loop);

		break;
	}
	default:
		break;
	}
	return TRUE;
}

gint main(gint argc, gchar *argv[])
{
	GstElement *playbin;
	GMainLoop *loop;
	GstBus *bus;
	guint bus_watch_id;
	gchar *uri;

	gst_init(&argc, &argv);

	if(argc < 2) {
		g_print("usage: %s <media file or uri>\n", argv[0]);
		return 1;
	}

	playbin = gst_element_factory_make("playbin", NULL);
	if(!playbin) {
		g_print("'playbin' gstreamer plugin missing\n");
		return 1;
	}

	/* take the commandline argument and ensure that it is a uri */
	if(gst_uri_is_valid(argv[1]))
		uri = g_strdup(argv[1]);
	else
		uri = gst_filename_to_uri(argv[1], NULL);
	g_object_set(playbin, "uri", uri, NULL);
	g_free(uri);

	/* create and event loop and feed gstreamer bus mesages to it */
	loop = g_main_loop_new(NULL, FALSE);

	bus = gst_element_get_bus(playbin);
	bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);
	g_object_unref(bus);

	/* start play back and listed to events */
	gst_element_set_state(playbin, GST_STATE_PLAYING);
	g_main_loop_run(loop);

	/* cleanup */
	gst_element_set_state(playbin, GST_STATE_NULL);
	g_object_unref(playbin);
	g_source_remove(bus_watch_id);
	g_main_loop_unref(loop);

	return 0;
}
