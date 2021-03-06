/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GIMP_TILE_HANDLER_VALIDATE_H__
#define __GIMP_TILE_HANDLER_VALIDATE_H__

#include <gegl-buffer-backend.h>

/***
 * GimpTileHandlerValidate is a GeglTileHandler that renders the
 * projection.
 */

G_BEGIN_DECLS

#define GIMP_TYPE_TILE_HANDLER_VALIDATE            (gimp_tile_handler_validate_get_type ())
#define GIMP_TILE_HANDLER_VALIDATE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidate))
#define GIMP_TILE_HANDLER_VALIDATE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidateClass))
#define GIMP_IS_TILE_HANDLER_VALIDATE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_HANDLER_VALIDATE))
#define GIMP_IS_TILE_HANDLER_VALIDATE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_HANDLER_VALIDATE))
#define GIMP_TILE_HANDLER_VALIDATE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidateClass))


typedef struct _GimpTileHandlerValidate      GimpTileHandlerValidate;
typedef struct _GimpTileHandlerValidateClass GimpTileHandlerValidateClass;

struct _GimpTileHandlerValidate
{
  GeglTileHandler  parent_instance;

  GeglNode        *graph;
  cairo_region_t  *dirty_region;
  const Babl      *format;
  gint             tile_width;
  gint             tile_height;
  gint             max_z;
  gboolean         whole_tile;
};

struct _GimpTileHandlerValidateClass
{
  GeglTileHandlerClass  parent_class;

  void (* validate) (GimpTileHandlerValidate *validate,
                     const GeglRectangle     *rect,
                     const Babl              *format,
                     gpointer                 dest_buf,
                     gint                     dest_stride);
};


GType                     gimp_tile_handler_validate_get_type        (void) G_GNUC_CONST;

GeglTileHandler         * gimp_tile_handler_validate_new             (GeglNode                *graph);

void                      gimp_tile_handler_validate_assign          (GimpTileHandlerValidate *validate,
                                                                      GeglBuffer              *buffer);
GimpTileHandlerValidate * gimp_tile_handler_validate_get_assigned    (GeglBuffer              *buffer);

void                      gimp_tile_handler_validate_invalidate      (GimpTileHandlerValidate *validate,
                                                                      const GeglRectangle     *rect);
void                      gimp_tile_handler_validate_undo_invalidate (GimpTileHandlerValidate *validate,
                                                                      const GeglRectangle     *rect);


G_END_DECLS

#endif /* __GIMP_TILE_HANDLER_VALIDATE_H__ */
