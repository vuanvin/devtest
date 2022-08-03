struct A { 
    int a;
    virtual void f() {}
};

struct B : virtual public A {
    int b;
    virtual void g() {}
};
