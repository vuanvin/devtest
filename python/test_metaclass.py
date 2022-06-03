from six import with_metaclass
import numpy as np

class Hello():
    def __init__(*args) -> None:
        print(args[0])

Hello()

Hello.__init__(1, 2)

Hi = type('Hi_Class', (Hello, ), dict())

print(Hi)
print(type(Hi))
print(Hi.__base__)

print(type.__base__)
print(object.__base__)

class Good(Hi, Hello):
    pass

print(Good.__base__)
