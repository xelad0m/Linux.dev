#include <stdio.h>
#include "fcount.h"

int main(int argc, char * argv[]) {
    char * path = argv[1];
    int count = 0;

    if (NULL == path)
        path = ".";

    files_count(path, &count);
    printf("%d files\n", count);

    return 0;
}
