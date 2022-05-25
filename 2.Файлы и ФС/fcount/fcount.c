#include <stddef.h> // NULL
#include <dirent.h> // opendir, readdir, dirent
#include <string.h> // strcmp
#include <stdio.h>

void files_count(const char * dirname, int * count) {
    DIR * dir = opendir(dirname);
    struct dirent * entry;
    char * curr_name;
    while ((entry=readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG)
            (*count)++;
        else if (entry->d_type == DT_DIR) {
            curr_name = entry->d_name;
            if ((strcmp(curr_name, ".") == 0) || (strcmp(curr_name, "..") == 0))
                continue;
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", dirname, curr_name);
            
            printf("%s\n", path);
            files_count(path, count);
        }
    }
    
    closedir(dir);

}
