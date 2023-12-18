#include <stdio.h>

int factorial(int n) {
    int r;
    for (int i=2; i<=n; i++) {
        r = r*i;
    }
    return r;
}

int main(void) {
    printf("factorial(5)=%d\n", factorial(5));
}

