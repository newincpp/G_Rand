#include <iostream>
#include <GRand>

int main(void){
    tinyGL::Core::Config cfg;
    tinyGL::Core::Config::autoConf(cfg);
    tinyGL::Core* e = tinyGL::Core::start(cfg);
    float i = 0;
    while (e->getStateValidity()) {
	e->queueIntruction([i](){ glClearColor(i, i, .0f, 0.0f); });
	i += 0.001f;
	if (i > 1) {
	    i = 0.0f;
	}
    }

    delete e;
    return 0;
}
