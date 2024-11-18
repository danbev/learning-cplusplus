#include <cstdint>
#ifndef VISION_H
#define VISION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vision vision;

enum vision_type {
    VISION_GENERIC,
    VISION_CLIP
};

struct vision_hparams {
    vision_type type;
    uint32_t image_width;
};

vision*     vision_create(vision_type type);
void        vision_destroy(vision* v);

void        vision_something(const vision* v);
const char* vision_get_name(const vision* vision);

#ifdef __cplusplus
}
#endif

#endif
