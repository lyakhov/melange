/* gst-bus-stub.h: Replacement of GstBus object for gst-dbus-stubs. Header file.
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

#ifndef __GST_BUS_STUB_H__
#define __GST_BUS_STUB_H__

#include <glib-object.h>

#define GST_TYPE_BUS (gst_bus_get_type())
#define GST_BUS(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_BUS, GstBus))
#define GST_IS_BUS(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_BUS))
#define GST_BUS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_BUS,\
	GstBusClass))
#define GST_IS_BUS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_BUS))
#define GST_BUS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), \
	GST_TYPE_BUS, GstBusClass))

typedef struct _GstBus GstBus;
typedef struct _GstBusClass GstBusClass;
typedef struct _GstBusPrivate GstBusPrivate;

struct _GstBus
{
	GObject parent_instance;

	/*< private >*/
	GstBusPrivate *priv;
};

struct _GstBusClass
{
	GObjectClass parent_class;
};

GType gst_bus_get_type();

#endif /* __GST_BUS_STUB_H__ */

