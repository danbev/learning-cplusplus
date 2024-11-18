#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vision.h"

struct vision {
    vision_type type;
    char* name;
    uint32_t image_width;

    void (*something_fn)(const struct vision*);
};

static void vision_something_impl(const vision* vision) {
    printf("%s something...\n", vision->name);
}

vision* vision_create(vision_hparams params) {
    switch(params.type) {
	    case VISION_GENERIC:
		{
		vision* v = (vision*) malloc(sizeof(vision));
		if (v) {
            v->type = params.type;
            v->image_width = params.image_width;
		    v->name = strdup("generic");
		    v->something_fn = vision_something_impl;
		}
		return v;
		}
	    case VISION_CLIP:
		{
		vision* v = (vision*) malloc(sizeof(vision));
		if (v) {
            v->type = params.type;
            v->image_width = params.image_width;
		    v->name = strdup("clip");
		    v->something_fn = vision_something_impl;
		}
		return v;
		}
	}
    return NULL;
}

void vision_destroy(vision* v) {
    if (v) {
        free(v->name);
        free(v);
    }
}

void vision_something(const vision* v) {
    v->something_fn(v);
}

const char* vision_get_name(const vision* v) {
    return v->name;
}

static void clip_something_impl(const vision* v) {
    printf("%s something...\n", v->name);
}
