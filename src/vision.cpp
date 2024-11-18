#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vision.h"

struct vision {
    char* name;

    void (*something_fn)(const struct vision*);
};

static void vision_something_impl(const vision* vision) {
    printf("%s something...\n", vision->name);
}

vision* vision_create(vision_type type) {
    switch(type) {
	    case VISION_GENERIC:
		{
		vision* v = (vision*) malloc(sizeof(vision));
		if (v) {
		    v->name = strdup("generic");
		    v->something_fn = vision_something_impl;
		}
		return v;
		}
	    case VISION_CLIP:
		{
		vision* v = (vision*) malloc(sizeof(vision));
		if (v) {
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
