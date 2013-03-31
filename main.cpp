#include <iostream>
#include <ff.h>

int foo(int a)
{
	std::cout << a<<std::endl;
	return a;
}
typedef boost::function<int ()> Func_t;
int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
	para a, b;
	a(boost::bind(foo, 5));

	b<:a:>(boost::bind(foo, 6));
    return 0;
}
