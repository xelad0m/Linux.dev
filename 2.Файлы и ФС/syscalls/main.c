#include <stdio.h>

int main()
{
    char name[100];
    printf("What is your name? __");
    gets(name); // man gets ОПИСАНИЕ Никогда не используйте эту функцию.
    return printf("Hello %s\n",name);
}

