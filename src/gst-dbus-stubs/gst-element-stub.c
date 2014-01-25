/* gst-element-stub.c: Replacement of GstElement object for gst-dbus-stubs. Code file.
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

#include "gst-element-stub.h"
#include "gst-element-private-stub.h"
#include "gstd-factory-interface.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
enum {
	PROP_0,

	PROP_URI,

	N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

G_DEFINE_TYPE(GstElement, gst_element, G_TYPE_OBJECT)

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_set_property(GObject *object,
	guint property_id,
	const GValue *value,
	GParamSpec *pspec)
{
	GstElement *self = GST_ELEMENT(object);

	switch (property_id) {
		case PROP_URI:
			g_free(self->priv->uri);
			self->priv->uri = g_value_dup_string(value);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_get_property(GObject *object,
	guint property_id,
	GValue *value,
	GParamSpec *pspec)
{
	GstElement *self = GST_ELEMENT(object);

	switch(property_id) {
		case PROP_URI:
			g_value_set_string(value, self->priv->uri);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_class_init(GstElementClass *klass)
{
	g_type_class_add_private(klass, sizeof(GstElementPrivate));

	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->set_property = gst_element_set_property;
	object_class->get_property = gst_element_get_property;

	obj_properties[PROP_URI] = g_param_spec_string("uri",
		"GstElement URI",
		"Set GstElement's uri property",
		"",
		G_PARAM_READWRITE);

	g_object_class_install_properties(object_class,
		N_PROPERTIES,
		obj_properties);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_init(GstElement *self)
{
	self->priv = GST_ELEMENT_GET_PRIVATE(self);
	self->priv->uri = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_dispose(GObject *object)
{
	GstElement *self = GST_ELEMENT(object);

	if (self->priv->proxy)
	{
		GVariant *variant = gstd_factory_destroy(G_BUS_TYPE_SESSION,
			g_dbus_proxy_get_object_path(self->priv->proxy));

		g_variant_unref(variant);
		g_object_unref(self->priv->proxy);
		self->priv->proxy = NULL;
	}

	G_OBJECT_CLASS(gst_element_parent_class)->dispose(object);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void gst_element_finalize(GObject *object)
{
	GstElement *self = GST_ELEMENT(object);

	g_free(self->priv->uri);

	G_OBJECT_CLASS(gst_element_parent_class)->finalize(object);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void gst_element_set_proxy(GstElement *element, GDBusProxy *proxy)
{
	element->priv->proxy = g_object_ref(proxy);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GDBusProxy *gst_element_get_proxy(GstElement *element)
{
	return g_object_ref(element->priv->proxy);
}
