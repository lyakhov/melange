/* gstd-factory-interface.h: Interface to invoke FactoryInterface's methods of gstd.
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

#ifndef __GSTD_FACTORY_INTERFACE_H__
#define __GSTD_FACTORY_INTERFACE_H__

#include <gio/gio.h>

GDBusProxy *gstd_factory_create(GBusType gstd_bus_type, GVariant *parameters);
GVariant *gstd_factory_destroy(GBusType gstd_bus_type, const gchar *object_path);

#endif /* __GSTD_FACTORY_INTERFACE_H__ */
