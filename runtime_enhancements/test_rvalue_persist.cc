#include <bits/stdc++.h>
using namespace std;

int f(int & val) {
    int arr[10000] = {1};
    int ret = 0;
    for (int i = 0; i < 100; i++) {
        ret += arr[i] * (val + 1);
    }

    return ret;
}

class A {
public:
    int a;
    int b;
    int c;

    void f() {
        a = b = c = 10000;
        cout << a << endl;
        g(1000);
    }

    void g(int n) {
        cout << b-- << endl;
        if (n > 0) h(n-1);
    }

    void h(int n) {
        cout << c-- << endl;
        if (n > 0) g(n-1);
    }
};

int main() {
    A a;
    auto f = bind(&A::f, &a);
    f();
}