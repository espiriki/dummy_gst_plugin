#include "dummy_plugin.h"
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

#define DUMMY_CAPS                                                             \
  GST_VIDEO_CAPS_MAKE("{ RGB, NV12, I420, YV12, NV21, YUYV, YVYU, "            \
                      "UYVY, VYUY, NV16, NV61, YUY2 }")

G_DEFINE_TYPE_WITH_CODE(Dummy, dummy, GST_TYPE_BASE_TRANSFORM,
                        GST_DEBUG_CATEGORY_INIT(dummy_debug_category,
                                                "dummy_plugin", 0,
                                                "debug category for "
                                                "dummy element"));

static gboolean plugin_init(GstPlugin *plugin) {
  return gst_element_register(plugin, "dummy", GST_RANK_PRIMARY, TYPE_DUMMY);
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR, GST_VERSION_MINOR, dummy, "dummy",
                  plugin_init, "0", "Proprietary", "dummy", "dummy")

static void dummy_init(Dummy *dummy) {}

static void dummy_class_init(DummyClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

  GstBaseTransformClass *video_transform_class =
      GST_BASE_TRANSFORM_CLASS(klass);

  gst_element_class_set_static_metadata(GST_ELEMENT_CLASS(klass), "dummy",
                                        "dummy",
                                        "dummy"
                                        "dummy"
                                        "dummy",
                                        "dummy"
                                        "dummy");

  gst_element_class_add_pad_template(
      GST_ELEMENT_CLASS(klass),
      gst_pad_template_new("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
                           gst_caps_from_string(DUMMY_CAPS)));

  gst_element_class_add_pad_template(
      GST_ELEMENT_CLASS(klass),
      gst_pad_template_new("src", GST_PAD_SRC, GST_PAD_ALWAYS,
                           gst_caps_from_string(DUMMY_CAPS)));
}
