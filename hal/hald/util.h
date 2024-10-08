/***************************************************************************
 * CVSID: $Id$
 *
 * util.h - Various utilities
 *
 * Copyright (C) 2004 David Zeuthen, <david@fubar.dk>
 * Copyright (C) 2008 Enrique Garcia, <kike+glkm@eldemonionegro.com>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 **************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include "device.h"
#include "device_store.h"

#ifndef __FUNCTION__
#define __FUNCTION__ __func__
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define HAL_NAME_MAX 256
#define HAL_PATH_MAX 512
#define HAL_BUFF_MAX 512

gboolean hal_util_remove_trailing_slash (gchar *path);

const gchar *hal_util_get_last_element (const gchar *s);

gchar *hal_util_get_parent_path (const gchar *path);

gchar *hal_util_get_normalized_path (const gchar *path1, const gchar *path2);

gboolean hal_util_get_int_from_file (const gchar *directory, const gchar *file, gint *result, gint base);

gboolean hal_util_set_int_from_file (HalDevice *d, const gchar *key, const gchar *directory, const gchar *file, gint base);

gboolean hal_util_get_uint64_from_file (const gchar *directory, const gchar *file, guint64 *result, gint base);

gboolean hal_util_set_uint64_from_file (HalDevice *d, const gchar *key, const gchar *directory, const gchar *file, gint base);

gchar *hal_util_get_string_from_file (const gchar *directory, const gchar *file);

gboolean hal_util_get_bool_from_file (const gchar *directory, const gchar *file, gboolean *retval, const char *true_val);

gboolean hal_util_set_string_from_file (HalDevice *d, const gchar *key, const gchar *directory, const gchar *file);

gboolean hal_util_set_double_from_file (HalDevice *d, const gchar *key, const gchar *directory, const gchar *file);

GSList *hal_util_get_strlist_from_file (const gchar *directory, const gchar *file);

gboolean hal_util_set_strlist_from_file (HalDevice *d, const gchar *key, const gchar *directory, const gchar *file);

void hal_util_make_udi_unique (HalDeviceStore *store, gchar *udi, gsize udisize, const char *original_udi);

void hal_util_compute_udi_valist (HalDeviceStore *store, gchar *dst, gsize dstsize, const gchar *format, va_list args);

void hal_util_compute_udi (HalDeviceStore *store, gchar *dst, gsize dstsize, const gchar *format, ...);

void hal_util_validate_udi (gchar *udi, gsize size);

gboolean hal_util_path_ascend (gchar *path);

void hal_util_grep_discard_existing_data (void);

gchar *hal_util_grep_file (const gchar *directory, const gchar *file, const gchar *linestart, gboolean reuse);
gchar *hal_util_grep_file_next_line (const gchar *directory, const gchar *file, const gchar *linestart, gboolean reuse);

gint hal_util_grep_int_elem_from_file (const gchar *directory, const gchar *file, 
				       const gchar *linestart, guint elem, guint base, gboolean reuse_file);

gchar *hal_util_grep_string_elem_from_file (const gchar *directory, const gchar *file, 
					    const gchar *linestart, guint elem, gboolean reuse_file);

gboolean hal_util_set_string_elem_from_file (HalDevice *d, const gchar *key, 
					     const gchar *directory, const gchar *file, 
					     const gchar *linestart, guint elem, gboolean reuse_file);

gboolean hal_util_set_int_elem_from_file (HalDevice *d, const gchar *key, 
					  const gchar *directory, const gchar *file, 
					  const gchar *linestart, guint elem, guint base, gboolean reuse_file);

gboolean hal_util_set_bool_elem_from_file (HalDevice *d, const gchar *key, 
					   const gchar *directory, const gchar *file, 
					   const gchar *linestart, guint elem, const gchar *expected, 
					   gboolean reuse_file);

gchar **hal_util_dup_strv_from_g_slist (GSList *strlist);

typedef void (*HalCalloutsDone) (HalDevice *d, gpointer userdata1, gpointer userdata2);

void hal_callout_device (HalDevice *d, HalCalloutsDone callback, gpointer userdata1, gpointer userdata2, 
			 char **programs, gchar **extra_env);

void hal_util_callout_device_add (HalDevice *d, HalCalloutsDone callback, gpointer userdata1, gpointer userdata2);
void hal_util_callout_device_remove (HalDevice *d, HalCalloutsDone callback, gpointer userdata1, gpointer userdata2);
void hal_util_callout_device_preprobe (HalDevice *d, HalCalloutsDone callback, gpointer userdata1, gpointer userdata2);

void hal_util_hexdump (const void *buf, unsigned int size);

gboolean hal_util_is_mounted_by_hald (const char *mount_point);

char *hal_util_readlink (const char *link);

gboolean is_valid_interface_name (const char *name);

void hal_util_decode_escape (const char* src, char* result, int maxlen);

#endif /* UTIL_H */
