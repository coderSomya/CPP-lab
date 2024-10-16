#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void functionC() {
    printf("In function C\n");
    longjmp(env, 1); 
}

void functionB() {
    printf("In function B\n");
    functionC();  
    printf("Back in function B\n");  
}

void functionA() {
    printf("In function A\n");
    if (setjmp(env) == 0) {
        functionB();  // Calls functionB which eventually jumps back
    } else {
        printf("Error occurred, jumped back to function A\n");
    }
}

int main() {
    functionA();
    return 0;
}
