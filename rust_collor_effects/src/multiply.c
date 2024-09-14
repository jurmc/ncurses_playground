#include<stdio.h>
#include<stdint.h>

uint32_t multiply(uint32_t a, uint32_t b) {
    printf("[C] Hello from C!\n");
    printf("[C] Input a is: %i\n", a);
    printf("[C] Input b is: %i\n", b);
    printf("[C] Multiplying and returning result to Rust!\n");

    return a * b;
}
