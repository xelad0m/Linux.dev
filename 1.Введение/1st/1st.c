#include <stdio.h>

void f() {
   printf("Function f \n");
}

void g() {
   printf("Function g \n");
   f();
}

void main() {
   printf("Function main \n");
   f();
   g();
   g();
   printf("Bye \n");
}
