from abc import ABCMeta

class MyABC(metaclass=ABCMeta):
    pass

print(MyABC.__base__)
print(MyABC.__class__)
print(type(MyABC))