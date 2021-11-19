#include "dummy_plugin.h"
#include <cairo/cairo.h>
#include <gst/allocators/allocators.h>
#include <gst/gst.h>
#include <gst/gsttracerrecord.h>
#include <gst/video/video.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>

#define PACKAGE "dummy"

GST_DEBUG_CATEGORY_STATIC(dummy_debug_category);

#define GST_CAT_DEFAULT dummy_debug_category

#define DUMMY_CAPS                                                    \
    GST_VIDEO_CAPS_MAKE("{ RGB, NV12, I420, YV12, NV21, YUYV, YVYU, " \
                        "UYVY, VYUY, NV16, NV61, YUY2 }")

G_DEFINE_TYPE_WITH_CODE(Dummy,
                        dummy,
                        GST_TYPE_BIN,
                        GST_DEBUG_CATEGORY_INIT(dummy_debug_category,
                                                "dummy_plugin",
                                                0,
                                                "debug category for "
                                                "dummy element"));

static gboolean
plugin_init(GstPlugin* plugin)
{
    return gst_element_register(plugin, "dummy", GST_RANK_PRIMARY, TYPE_DUMMY);
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
                  GST_VERSION_MINOR,
                  dummy,
                  "dummy",
                  plugin_init,
                  "0",
                  "Proprietary",
                  "dummy",
                  "dummy");

static void
draw_overlay(GstElement* overlay,
             cairo_t*    cr,
             guint64     timestamp,
             guint64     duration,
             gpointer    user_data)
{

    // To clear everything that was draw
    cairo_new_path(cr);

    float xmax = 300.0F;
    float xmin = 100.0F;
    float ymin = 100.0F;
    float ymax = 300.0F;

    cairo_set_source_rgb(cr, 1.0, 1.0, 0.0);
    cairo_move_to(cr, xmin, ymin);
    cairo_line_to(cr, xmax, ymin);
    cairo_line_to(cr, xmax, ymax);
    cairo_line_to(cr, xmin, ymax);
    cairo_line_to(cr, xmin, ymin);
    cairo_stroke_preserve(cr);
}

static void
dummy_init(Dummy* box_overlay)
{

    GstBin* bin;
    GstPad* pad;

    bin = GST_BIN_CAST(box_overlay);

    box_overlay->cairo = gst_element_factory_make("cairooverlay", NULL);

    if (!box_overlay->cairo) { return; }

    gst_bin_add(bin, box_overlay->cairo);

    pad = gst_element_get_static_pad(box_overlay->cairo, "sink");
    box_overlay->sinkpad = gst_ghost_pad_new("sink", pad);
    gst_object_unref(pad);

    pad                 = gst_element_get_static_pad(box_overlay->cairo, "src");
    box_overlay->srcpad = gst_ghost_pad_new("src", pad);
    gst_object_unref(pad);

    gst_element_add_pad(GST_ELEMENT(bin), box_overlay->sinkpad);
    gst_element_add_pad(GST_ELEMENT(bin), box_overlay->srcpad);

    g_signal_connect(box_overlay->cairo,
                     "draw",
                     G_CALLBACK(draw_overlay),
                     box_overlay);
}

static void
dummy_class_init(DummyClass* klass)
{
    GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

    GstBaseTransformClass* video_transform_class =
        GST_BASE_TRANSFORM_CLASS(klass);

    gst_element_class_set_static_metadata(GST_ELEMENT_CLASS(klass),
                                          "dummy",
                                          "dummy",
                                          "dummy"
                                          "dummy"
                                          "dummy",
                                          "dummy"
                                          "dummy");

    gst_element_class_add_pad_template(
        GST_ELEMENT_CLASS(klass),
        gst_pad_template_new("sink",
                             GST_PAD_SINK,
                             GST_PAD_ALWAYS,
                             gst_caps_from_string(DUMMY_CAPS)));

    gst_element_class_add_pad_template(
        GST_ELEMENT_CLASS(klass),
        gst_pad_template_new("src",
                             GST_PAD_SRC,
                             GST_PAD_ALWAYS,
                             gst_caps_from_string(DUMMY_CAPS)));
}
