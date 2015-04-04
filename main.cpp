#include <iostream>
#include <GRand>

int main(void){
    tinyGL::Core* e = tinyGL::Core::start();
    float i = 0;
    while (true) {
	e->queueIntruction([i](){ glClearColor(i, i, .0f, 0.0f); });
	i += 0.001f;
	if (i > 1) {
	    i = 0.0f;
	}
	std::cout << i << std::endl; 
    }

    delete e;
    return 0;
}
