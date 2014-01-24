/* gst-bus-private-stub.h: Private structure for GstBus object
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

#ifndef __GST_BUS_PRIVATE_STUB_H__
#define __GST_BUS_PRIVATE_STUB_H__

#include <gio/gio.h>

#define GST_BUS_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),\
	GST_TYPE_BUS, GstBusPrivate))

struct _GstBusPrivate
{
	GDBusProxy *proxy;
};

void gst_bus_set_proxy(GstBus *bus, GDBusProxy *proxy);
GDBusProxy *gst_bus_get_proxy(GstBus *bus);

#endif /* __GST_BUS_PRIVATE_STUB_H__ */
