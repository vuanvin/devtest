
class RevealAccess:
    def __init__(self, initval=None, name='var') -> None:
        self.val = initval
        self.name = name

    def __get__(self, obj, objtype):
        print('Retrieving {}'.format(self.name))
        return self.val

    def __set__(self, obj, val):
        print('Updating {}'.format(self.name))
        self.val = val

class MyClass:
    x = RevealAccess(10, 'var x')
    y = 5

if __name__ == '__main__':
    m = MyClass()
    print(m.__dict__)
    print(MyClass.__dict__)
    m.x