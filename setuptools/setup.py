from setuptools import setup, find_packages

print(find_packages())

if __name__ == '__main__':
    setup(
        name='mytest',
        version='1.0.0',
        pakages=find_packages(),
    )