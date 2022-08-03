struct A { 
    int a;
    virtual void f() {}
};

struct B {
    int b;
    virtual void g() {}
};

struct C : public A, virtual public B {
    virtual void h() {}
};
