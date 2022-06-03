from typing import SupportsRound
from six import with_metaclass

class A(metaclass=type):
    def __init__(self, *args):
        pass

class B:
    pass

class C(B, with_metaclass(A)):
    pass

print(B.__class__)

print(C.__class__)
print(C.__dict__)

print(type.__base__)

class Base:
    pass

a = Base()
b = super(Base, a)
print(b.__class__)

sp = b.__class__
print(dir(super))

