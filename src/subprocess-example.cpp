#include "subprocess.h"

#include <stdio.h>
#include <cerrno>

int main(void) {
    const char * command[] = {"/bin/ls", "-l", NULL};
    struct subprocess_s proc;
    int ret;

    ret = subprocess_create(command, subprocess_option_inherit_environment, &proc);
    if (ret != 0) {
        fprintf(stderr, "failed to create subprocess: %s\n", strerror(errno));
        return 1;
    }

    FILE * out = subprocess_stdout(&proc);
    char buf[256];
    while (fgets(buf, sizeof(buf), out)) {
        printf("%s", buf);
    }

    int exit_code;
    ret = subprocess_join(&proc, &exit_code);
    if (ret != 0) {
        fprintf(stderr, "subprocess_join failed: %s\n", strerror(errno));
        return 1;
    }

    printf("process exited with code %d\n", exit_code);

    subprocess_destroy(&proc);
    return 0;
}
