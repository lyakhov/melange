/* gst-element-private-stub.h: Private structure for GstElement object
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

#ifndef __GST_ELEMENT_PRIVATE_STUB_H__
#define __GST_ELEMENT_PRIVATE_STUB_H__

#include <glib.h>

#define GST_ELEMENT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),\
	GST_TYPE_ELEMENT, GstElementPrivate))

struct _GstElementPrivate
{
	gchar *uri;
};

#endif /* __GST_ELEMENT_PRIVATE_STUB_H__ */
