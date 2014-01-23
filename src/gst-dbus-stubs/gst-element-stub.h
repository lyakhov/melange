/* gst-element-stub.h: Replacement of GstElement object for gst-dbus-stubs. Header file.
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

#ifndef __GST_ELEMENT_STUB_H__
#define __GST_ELEMENT_STUB_H__

#include <glib-object.h>

#define GST_TYPE_ELEMENT (gst_element_get_type())
#define GST_ELEMENT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_ELEMENT, GstElement))
#define GST_IS_ELEMENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_ELEMENT))
#define GST_ELEMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_ELEMENT,\
	GstElementClass))
#define GST_IS_ELEMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_ELEMENT))
#define GST_ELEMENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), \
	GST_TYPE_ELEMENT, GstElementClass))

typedef struct _GstElement GstElement;
typedef struct _GstElementClass GstElementClass;
typedef struct _GstElementPrivate GstElementPrivate;

struct _GstElement
{
	GObject parent_instance;

	/*< private >*/
	GstElementPrivate *priv;
};

struct _GstElementClass
{
	GObjectClass parent_class;
};

GType gst_element_get_type();

#endif /* __GST_ELEMENT_STUB_H__ */

