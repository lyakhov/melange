/* gst-bus-stub.h: Replacement of GstBus object for gst-dbus-stubs. Code file.
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

#include "gst-bus-stub.h"
#include "gst-bus-private-stub.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
enum {
	PROP_0,

	N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_bus_set_property(GObject *object,
	guint property_id,
	const GValue *value,
	GParamSpec *pspec)
{
	GstBus *self = GST_BUS(object);

	switch (property_id) {
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_bus_get_property(GObject *object,
	guint property_id,
	GValue *value,
	GParamSpec *pspec)
{
	GstBus *self = GST_BUS(object);

	switch(property_id) {
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_bus_class_init(GstBusClass *klass)
{
	g_type_class_add_private(klass, sizeof(GstBusPrivate));

	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->set_property = gst_bus_set_property;
	object_class->get_property = gst_bus_get_property;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_bus_init(GstBus *self)
{
	self->priv = GST_BUS_GET_PRIVATE(self);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void gst_bus_set_proxy(GstBus *bus, GDBusProxy *proxy)
{
	bus->priv->proxy = proxy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GDBusProxy *gst_bus_get_proxy(GstBus *bus)
{
	return bus->priv->proxy;
}

G_DEFINE_TYPE(GstBus, gst_bus, G_TYPE_OBJECT)

