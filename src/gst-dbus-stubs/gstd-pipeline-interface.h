/* gstd-pipeline-interface.h: Interface to invoke PipelineInterface's methods of gstd.
 * Header file.
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

#ifndef __GSTD_PIPELINE_INTERFACE_H__
#define __GSTD_PIPELINE_INTERFACE_H__

#include "gst/gst.h"

#include <gio/gio.h>

GVariant *gstd_pipeline_element_set_property_string(GDBusProxy *pipeline_proxy,
	const gchar *element,
	const gchar *name,
	const gchar *value);

gchar *gstd_pipeline_element_get_property_string(GDBusProxy *pipeline_proxy,
	const gchar *element,
	const gchar *name);

GVariant *gstd_pipeline_set_state(GDBusProxy *pipeline_proxy, GstState state);

GstState gstd_pipeline_get_state(GDBusProxy *pipeline_proxy);

#endif /* __GSTD_PIPELINE_INTERFACE_H__ */
