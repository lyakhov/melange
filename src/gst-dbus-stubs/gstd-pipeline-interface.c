/* gstd-pipeline-interface.c: Interface to invoke PipelineInterface's methods of gstd.
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

#include "gstd-pipeline-interface.h"


GVariant *gstd_pipeline_element_set_property_string(GDBusProxy *pipeline_proxy,
	const gchar *element,
	const gchar *name,
	const gchar *value)
{
	GError *error = NULL;
	GVariant *variant = NULL;

	variant = g_dbus_proxy_call_sync(pipeline_proxy,
		"ElementSetPropertyString",
		g_variant_new("(sss)", element, name, value),
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return NULL;
	}

	return variant;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
gchar *gstd_pipeline_element_get_property_string(GDBusProxy *pipeline_proxy,
	const gchar *element,
	const gchar *name)
{
	GError *error = NULL;
	GVariant *variant = NULL;
	gchar *property_string = NULL;

	variant = g_dbus_proxy_call_sync(pipeline_proxy,
		"ElementGetPropertyString",
		g_variant_new("(ss)", element, name),
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return NULL;
	}

	if (!g_strcmp0(g_variant_get_type_string(variant), "(sb)")) {
		GVariant *string_variant = g_variant_get_child_value(variant, 0);
		property_string = g_variant_dup_string(string_variant, NULL);
	}

	g_variant_unref(variant);
	return property_string;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GVariant *gstd_pipeline_set_state(GDBusProxy *pipeline_proxy, GstState state)
{
	GError *error = NULL;
	GVariant *variant = NULL;

	variant = g_dbus_proxy_call_sync(pipeline_proxy,
		"PipelineSetState",
		g_variant_new("(i)", state),
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return NULL;
	}

	return variant;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GstState gstd_pipeline_get_state(GDBusProxy *pipeline_proxy)
{
	GError *error = NULL;
	GVariant *variant = NULL;
	GstState state = GST_STATE_NULL;

	variant = g_dbus_proxy_call_sync(pipeline_proxy,
		"PipelineGetState",
		NULL,
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error);
	if (error) {
		g_printerr("g_dbus_proxy_new_for_bus_sync failed: %s\n", error->message);
		return GST_STATE_NULL;
	}

	if (!g_strcmp0(g_variant_get_type_string(variant), "(i)")) {
		GVariant * temp_variant = g_variant_get_child_value(variant, 0);
		state = g_variant_get_int32(temp_variant);
		g_variant_unref(temp_variant);
	}

	g_variant_unref(variant);
	return state;
}
