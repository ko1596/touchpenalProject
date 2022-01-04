#ifndef GSTSERVICE_H
#define GSTSERVICE_H

#include <gst/gst.h>

#define IMG_PATH "/home/root/touchPenalProject/frame.jpg"

GstElement *pipeline, *jpdec, *imgf, *source, *sink;
GstBus *bus;
GstMessage *msg;
GstStateChangeReturn ret;

int initGST(void);

int displayScreen(void);

void freeResources(void);

#endif /*GSTSERVICE_H*/