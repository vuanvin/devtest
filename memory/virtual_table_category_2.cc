struct A { 
    int a;
    virtual void f() {}
};

struct B : public A {
    int b;
    virtual void g() {}
};
