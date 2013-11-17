/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * hwp-page.h
 *
 * Copyright (C) 2012-2013 Hodong Kim <cogniti@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GHWP_PAGE_H__
#define __GHWP_PAGE_H__

#include <glib-object.h>
#include <cairo.h>
#include <pango/pango-layout.h>

#include "hwp-enums.h"

G_BEGIN_DECLS

#define GHWP_TYPE_PAGE             (hwp_page_get_type ())
#define GHWP_PAGE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GHWP_TYPE_PAGE, GHWPPage))
#define GHWP_PAGE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GHWP_TYPE_PAGE, GHWPPageClass))
#define GHWP_IS_PAGE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GHWP_TYPE_PAGE))
#define GHWP_IS_PAGE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GHWP_TYPE_PAGE))
#define GHWP_PAGE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GHWP_TYPE_PAGE, GHWPPageClass))

typedef struct _GHWPPage        GHWPPage;
typedef struct _GHWPPageClass   GHWPPageClass;

struct _GHWPPage {
    GObject  parent_instance;
    GArray  *paragraphs;
    GArray  *layouts;
};

struct _GHWPPageClass {
    GObjectClass parent_class;
};

typedef struct _GHWPColor GHWPColor;

/**
 * Since: 0.2
 */
struct _GHWPColor {
    guint16 red;
    guint16 green;
    guint16 blue;
};

typedef struct _GHWPRectangle GHWPRectangle;
/**
 * Since: 0.2
 */
struct _GHWPRectangle {
    gdouble x1;
    gdouble y1;
    gdouble x2;
    gdouble y2;
};

typedef struct _GHWPLayout GHWPLayout;
/**
 * Since: TODO
 */
struct _GHWPLayout {
    gdouble x;
    gdouble y;
    PangoLayout *pango_layout;
};

GType     hwp_page_get_type   (void) G_GNUC_CONST;
GHWPPage *hwp_page_new        (void);
void      hwp_page_get_size   (GHWPPage *page,
                                gdouble  *width,
                                gdouble  *height);
gboolean  hwp_page_render     (GHWPPage *page, cairo_t *cr);
/* experimental */
void
hwp_page_render_selection     (GHWPPage           *page,
                                cairo_t            *cr,
                                GHWPRectangle      *selection,
                                GHWPRectangle      *old_selection,
                                GHWPSelectionStyle  style, 
                                GHWPColor          *glyph_color,
                                GHWPColor          *background_color);
char *
hwp_page_get_selected_text    (GHWPPage          *page,
                                GHWPSelectionStyle style,
                                GHWPRectangle     *selection);
cairo_region_t *
hwp_page_get_selection_region (GHWPPage          *page,
                                gdouble            scale,
                                GHWPSelectionStyle style,
                                GHWPRectangle     *selection);
void hwp_rectangle_free       (GHWPRectangle     *rectangle);

G_END_DECLS

#endif /* __GHWP_PAGE_H__ */