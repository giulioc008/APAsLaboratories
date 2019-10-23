#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main() {
    int a, b;

    fprintf(stdout, "Insert the first number: ");
    fscanf(stdin, "%d", &a);
    fprintf(stdout, "Insert the second number: ");
    fscanf(stdin, "%d", &b);
    fprintf(stdout, "The gcd of %d and %d is: %d", a, b, gcd(a, b));
    return 0;
}

int gcd(int a, int b) {
    if(a == 0) {
        return b;
    }
    if(a % 2 == 0 && b % 2 == 0) {
        return 2 * gcd(a / 2, b / 2);
    } else if(a % 2 != 0 && b % 2 != 0) {
        if( b > a) {
            a += b;
            b = a - b;
            a -= b;
        }
        return gcd((a - b) / 2, b);
    }
    if(a % 2 == 0) {
        a += b;
        b = a - b;
        a -= b;
    }
    return gcd(a, b / 2);
}