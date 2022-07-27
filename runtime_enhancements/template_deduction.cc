#include <bits/stdc++.h>
using namespace std;

template<typename T>
void tunc(T& n) {
    n += 1;
}

template<typename T>
void tunc(T&& n) {
    n += 2;
}

void func(int &n) {
    n += 10;
}

void func(int &&n) {
    n += 20;
}

struct A {
    A() = default;
    A(const A& other) { cout << "copy constructor" << endl; }
    A(A&& other) { cout << "move constructor" << endl; }
    ~A() { cout << "deconstructor" << endl; }

    int data;
};

int main() {
    int n = 0;

    func(n);
    cout << n << endl;
    func(forward<int&>(n));
    cout << n << endl;

    cout << "-------------------" << endl;

    int &nref = n;
    func(nref);
    cout << n << endl;
    func(forward<int&>(nref));
    cout << n << endl;

    cout << "-------------------" << endl;

    int &&mref = 0;
    func(mref);
    cout << mref << endl;
    func(forward<int&&>(mref));
    cout << mref << endl;

    func(1000);

    cout << "-------------------" << endl;

    int& k = mref;
    k += 100;
    cout << &k << endl;
    cout << &mref << endl;

    cout << "-------------------" << endl;
    int i = move(n);
    cout << &n << " : " << &i << endl;

    int &&j = move(n);
    cout << &n << " : " << &j << endl;

    int l = move(mref);
    cout << &l << " : " << &mref << endl;

    int && dref = A().data;

    cout << dref << endl;
}