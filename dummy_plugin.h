#ifndef DUMMY_PLUGIN_H
#define DUMMY_PLUGIN_H

#include <gst/base/gstbasetransform.h>
#include <gst/video/video.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TYPE_DUMMY (dummy_get_type())
#define DUMMY(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_DUMMY, Dummy))
#define DUMY_CLASS(klass)                                                      \
  (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_DUMMY, DummyClass))
#define IS_dummy(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_DUMMY))
#define IS_DUMMY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_DUMMYF))
#define DUMMY_CAST(obj) ((Dummy *)obj)

typedef struct {
  GstBaseTransform parent;
  GstElement *cairo;

  GstPad *sinkpad, *srcpad;
} Dummy;

typedef struct {
  GstBaseTransformClass parent_class;
} DummyClass;

GType dummy_get_type(void);

#ifdef __cplusplus
}
#endif

#endif
