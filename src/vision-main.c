#include <stdio.h>
#include "vision.h"

int main(int argc, char** argv) {
    vision* generic = vision_create(VISION_GENERIC);
    printf("Vision name: %s\n", vision_get_name(generic));
    vision* clip = vision_create(VISION_CLIP);
    printf("Vision name: %s\n", vision_get_name(clip));
    
    vision_something(generic);
    vision_something(clip);
    
    vision_destroy(generic);
    vision_destroy(clip);
    
    return 0;
}
