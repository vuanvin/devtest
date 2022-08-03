struct A { 
    virtual void f() {}
};

struct B : virtual public A {
    int b;
    virtual void g() {}
};
