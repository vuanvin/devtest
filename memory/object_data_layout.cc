struct A { virtual void f(); };
struct B : virtual public A { int i; };
struct C : virtual public A { int j; };
struct D : public B, public C {};