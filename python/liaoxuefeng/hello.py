def ext_hello():
    print('ext_hello')

class Hello:
    def hello(self, name='world'):
        print('Hello, %s.' % name)

    @staticmethod
    def hi(cls):
        print('hi')

    @classmethod
    def ok(cls):
        print('ok')

    dup_hello = ext_hello

    static_hello = staticmethod(hello)
    class_hello = classmethod(hello)


print(Hello.hi)
print(Hello.hi.__class__)

print(Hello.hello)
print(Hello.hello.__class__)

print(Hello.ok)
print(Hello.hello.__class__)

print(Hello.dup_hello)
print(Hello.dup_hello.__class__)

print('----------------------')

print(Hello.static_hello)
print(Hello.class_hello)