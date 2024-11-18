#include <stdio.h>
#include "vision.h"

int main(int argc, char** argv) {
    vision_hparams g_params = {VISION_GENERIC, 640, 480};
    vision* generic = vision_create(g_params);
    printf("Vision name: %s\n", vision_get_name(generic));

    vision_hparams c_params = {VISION_CLIP, 1280, 720};
    vision* clip = vision_create(c_params);
    printf("Vision name: %s\n", vision_get_name(clip));
    
    vision_something(generic);
    vision_something(clip);
    
    vision_destroy(generic);
    vision_destroy(clip);
    
    return 0;
}
