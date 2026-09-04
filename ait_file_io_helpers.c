#include "ait_file_io_helpers.h"
#include <sys/stat.h>

bool ait_does_directory_exist(const char* path)
{
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) return true;

    return false;
}
