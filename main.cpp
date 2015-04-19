#include <unistd.h>
#include <iostream>
#include <GRand>

int main(void){
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    float i = 0;
    e->addPersistantInstruction([&i](){ glClearColor(i, i, .0f, 0.0f); i+= 0.001f; if(i > 1) { i = 0.0f;} });

    sleep(9);
    //while (e->getStateValidity()) {
        //e->queueIntruction([i](){ glClearColor(i, i, .0f, 0.0f); });
        //i += 0.001f;
        //if (i > 1) {
        //    i = 0.0f;
        //}
	//std::cout << i << std::endl;
    //}

    delete e;
    return 0;
}
