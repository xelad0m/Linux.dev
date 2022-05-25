#include <stdio.h>
#include <ctype.h>      // isdigit
#include <stdbool.h>    // true, false

bool is_digits(char * text) {
    bool res = false;

    while (*text) {
        res = isdigit(*text++);
        if (!res)
            break;
    }

    return res;
}


int main(void) {
    char digits[100] = "1234123346757698";
    char name[100] = "some123 test texxt";
    char digs[100] = "1234123346757698a";

    printf("%d\n", is_digits( (char*) &digits ));
    printf("%d\n", is_digits( (char*) &name ));
    printf("%d\n", is_digits( (char*) &digs ));
}
