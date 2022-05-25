#include <stddef.h>     // NULL
#include <stdio.h>
#include <stdlib.h>     // atoi
#include <unistd.h>     // pid_t
#include <limits.h>     // PATH_MAX
#include <fcntl.h>      // O_RDONLY
#include <dirent.h> 	// opendir, readdir, dirent
#include <string.h> 	// strcmp
#include <ctype.h>	    // isdigit
#include <stdbool.h>    // bool, true, false

/*
Разработать программу solution, которая осуществляет поиск и подсчет числа 
процессов с именем genenv в системе Linux на которой выполняется программа. 
*/


bool is_digits(char * text) {
    // Возвращает true если все символы - цифры
    bool res = false;
 
    while (*text) {
        res = isdigit(*text++);
        if (!res)                                                                                                                                                      
            break;
    }
    
    return res;
}   

const char * get_proc_name(const char * name) {
    // Возвращает имя процесса по его PID через procfs (/proc/PID/comm)

    FILE * fd = NULL;
    char filename[PATH_MAX] = {0};

    snprintf(filename, sizeof(filename), "/proc/%s/comm", name);
	
    fd = fopen(filename, "r");
    if (NULL == fd) 
        fprintf(stderr, "Error: Couldn't open [%s]\n", filename);

    static char res[PATH_MAX] = {0};    // чтобы переменная не удалялась при 
                                        // выходе из scope
    fscanf(fd, "%s", res);

    return res;
}

int scan_proc_dir(const char * target_name) {
    DIR * dir = opendir("/proc");
    struct dirent * entry;
    char * curr_name;

    int counter = 0;

    while ((entry=readdir(dir)) != NULL) {

        if (entry->d_type == DT_DIR) {
    	    curr_name = entry->d_name;
	        if ((strcmp(curr_name, ".") == 0) || (strcmp(curr_name, "..") == 0))
                // если каталог это . или ..
                continue;
            
    	    if (is_digits(curr_name)) {
                // если имя каталога состоит только из цифр
                const char * proc_name = get_proc_name(curr_name);
                if (0 == strcmp(proc_name, target_name))
                    counter++;
	    	}
        }
    }
    
    closedir(dir);
    return counter;
}


int main(int c, const char **v) {
    
    const char * target_name = "genenv";    // char is const, ptr is NOT const
    if (c == 2) {
        target_name = (char *) v[1];        // thats why its absolutely fine
    }
    
    printf("%d\n", scan_proc_dir(target_name));
   
    return 0;
}

