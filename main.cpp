#include <unistd.h>
#include <iostream>

#include <GRand>

int main(void){
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0, 0, .0f, 0.0f); });
    GRand::Material mat;
    GRand::Mesh mesh(e, &mat);
    //e->queueIntruction([&mat](){ mat.addShader(GL_FRAGMENT_SHADER, "./shaders/defaultFragment.glsl"); });
    //e->queueIntruction([&mat](){ mat.addShader(GL_VERTEX_SHADER, "./shaders/defaultVertex.glsl"); });

    e->queueIntruction([&mat](){ mat.addShader(GL_FRAGMENT_SHADER, "./shaders/simpleFrag.glsl"); });
    e->queueIntruction([&mat](){ mat.addShader(GL_VERTEX_SHADER, "./shaders/simpleVert.glsl"); });

    e->queueIntruction([&mat](){ mat.link(); });
    e->queueIntruction([&mesh](){ mesh.set(GRand::GPUBuffer()); });


    //sleep(5);
    while (e->getStateValidity()) { }

    delete e;
    return 0;
}
