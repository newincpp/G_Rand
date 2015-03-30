#include <iostream>
#include <GRand>

int main(void){
    tinyGL::Engine* e = tinyGL::Engine::start();
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
