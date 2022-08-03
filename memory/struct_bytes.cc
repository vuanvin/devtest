#include <cstdio>

struct Foo {
    char ch;
    // double d __attribute__ ((packed)) ;
    int d __attribute__ (( aligned (8) ));
} __attribute__ ((aligned (32))) ;

int main() {
    printf("%ld\n", sizeof(Foo));
}