#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int c, char ** v) {
    
    if (c != 2) { 
        printf("Usage: v[0] some.domain.name\n");
        return -1;
    }
    
    // получим структуру записи о хосте: man 3 gethostbyname
    struct hostent * h;
    h = gethostbyname(v[1]);

    if (NULL == h) {
        printf("Error\n");
    }
    
    // разбор структуры записи о хосте
    printf("Canonical name: %s\n", h->h_name);

    printf("Type = %s len=%d\n", (h->h_addrtype == AF_INET) ? "ipv4" : "ipv6",
                                 h->h_length);
    
    for (int i=0; NULL != h->h_aliases[i]; ++i) // почти ни у кого нет...
        printf("alias = %s\n", h->h_aliases[i]);
        
    int i = 0;
    while (NULL != h->h_addr_list[i]) {
        struct in_addr *a = (struct in_addr *) h->h_addr_list[i];
        printf("%s\n", inet_ntoa(*a));
        i++;
    }

    return 0;
}
