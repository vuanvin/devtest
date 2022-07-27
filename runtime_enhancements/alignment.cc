#include <bits/stdc++.h>
using namespace std;

struct S {
    char a; // size: 1, alignment: 1
    char b; // size: 1, alignment: 1
}; // size: 2, alignment: 1
 
struct X {
    int n;  // size: 4, alignment: 4
    char c; // size: 1, alignment: 1
}; // size: 8, alignment: 4

struct Z {
    S s;
    X x;
    // double d;
    char e;
};

struct A { void f() {} };
struct B { virtual void f() {} };
struct C : public B {};
 
int main() {
    cout << sizeof(max_align_t) << endl;

    printf("sizeof(struct S) = %zu\n", sizeof(struct S));
    printf("alignof(struct S) = %zu\n", alignof(struct S));

    printf("sizeof(struct X) = %zu\n", sizeof(struct X));
    printf("alignof(struct X) = %zu\n", alignof(struct X));

    printf("sizeof(struct Z) = %zu\n", sizeof(struct Z));
    printf("alignof(struct Z) = %zu\n", alignof(struct Z));

    if (sizeof(char) != alignof(char)) cout << "char" << endl; // 1
    if (sizeof(int) != alignof(int)) cout << "int" << endl; // 4
    if (sizeof(unsigned) != alignof(unsigned)) cout << "unsigned" << endl; // 4
    if (sizeof(long) != alignof(long)) cout << "long" << endl; // 8
    if (sizeof(long long) != alignof(long long)) cout << "long long" << endl; // 8
    if (sizeof(float) != alignof(float)) cout << "float" << endl; // 4
    if (sizeof(double) != alignof(double)) cout << "double" << endl; // 8
    if (sizeof(long double) != alignof(long double)) cout << "long double" << endl; // 16
    if (sizeof(void*) != alignof(void*)) cout << "void*" << endl; // 8
    if (sizeof(A) != alignof(A)) cout << "A" << endl; // 1
    if (sizeof(B) != alignof(B)) cout << "B" << endl; // 8
    if (sizeof(C) != alignof(C)) cout << "C" << endl; // 8
}