/* gstd-factory-interface.c: Interface to invoke FactoryInterface's methods of gstd.
 * Code file.
 *
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

#include "gstd-factory-interface.h"

GDBusProxy *gstd_factory_create(GBusType gstd_bus_type, GVariant *parameters)
{
	GDBusProxy *factory_proxy = NULL;
	GDBusProxy *pipeline_proxy = NULL;
	GVariant *variant = NULL;
	GError *error = NULL;
	gchar *pipeline_object_path = NULL;

	factory_proxy = g_dbus_proxy_new_for_bus_sync(gstd_bus_type,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"com.ridgerun.gstreamer.gstd",
		"/com/ridgerun/gstreamer/gstd/factory",
		"com.ridgerun.gstreamer.gstd.FactoryInterface",
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		goto free_section;
	}

	error = NULL;
	variant = g_dbus_proxy_call_sync(factory_proxy,
		"Create",
		parameters,
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_call_sync failed: %s\n", error->message);
		goto free_section;
	}

	if (!g_strcmp0(g_variant_get_type_string(variant), "(s)")) {
		GVariant *pipeline_variant = g_variant_get_child_value(variant, 0);
		pipeline_object_path = g_variant_dup_string(pipeline_variant, NULL);
	}
	else {
		g_printerr("Received invalid reply on 'Create' remote method.");
		goto free_section;
	}

	error = NULL;
	pipeline_proxy = g_dbus_proxy_new_for_bus_sync(gstd_bus_type,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"com.ridgerun.gstreamer.gstd",
		pipeline_object_path,
		"com.ridgerun.gstreamer.gstd.PipelineInterface",
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		goto free_section;
	}

free_section:
	g_object_unref(factory_proxy);
	if (pipeline_object_path)
		g_free(pipeline_object_path);
	return pipeline_proxy;
}

GVariant *gstd_factory_destroy(GBusType gstd_bus_type, const gchar *object_path)
{
	GError *error = NULL;
	GDBusProxy *factory_proxy = NULL;
	GVariant *variant = NULL;

	factory_proxy = g_dbus_proxy_new_for_bus_sync(gstd_bus_type,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"com.ridgerun.gstreamer.gstd",
		"/com/ridgerun/gstreamer/gstd/factory",
		"com.ridgerun.gstreamer.gstd.FactoryInterface",
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		goto free_section;
	}
	else {
		error = NULL;
		variant = g_dbus_proxy_call_sync(factory_proxy,
			"Destroy",
			g_variant_new("(s)", object_path),
			G_DBUS_CALL_FLAGS_NONE,
			-1,
			NULL,
			&error);
		if (error) {
			g_printerr("g_dbus_proxy_call_sync failed: %s\n", error->message);
			goto free_section;
		}
	}

free_section:
	g_object_unref(factory_proxy);
	return variant;
}

