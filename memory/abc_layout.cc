struct A { virtual void f(); };
struct B { virtual void g(); };
struct C : public A, public B {};