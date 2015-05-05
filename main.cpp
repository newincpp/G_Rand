#include <unistd.h>
#include <iostream>

#include <GRand>

int main(void){
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0, 0, .0f, 0.0f); });
    GRand::Material mat;
    GRand::GPUBuffer gb;
    gb.loadFile("./testModels/monkey.dae");

    GRand::Mesh mesh(e, &mat);
    mesh.set(gb);

    PUSH_CORE_INSTA(e, mat, mat.addShader(GL_FRAGMENT_SHADER, "./shaders/phongFrag.glsl"); );
    PUSH_CORE_INSTA(e, mat, mat.addShader(GL_VERTEX_SHADER, "./shaders/phongVert.glsl"); );
    PUSH_CORE_INSTA(e, mat, mat.link());

    //e->queueIntruction([&mat](){ mat.addShader(GL_FRAGMENT_SHADER, "./shaders/defaultFragment.glsl"); });
    //e->queueIntruction([&mat](){ mat.addShader(GL_VERTEX_SHADER, "./shaders/defaultVertex.glsl"); });

    //sleep(5);
    GRand::Controller* ctrl = mesh.genController();
    ctrl->rotate(1.571f, Eigen::Vector3f::UnitX());
    ctrl->scale(Eigen::Vector3f(0.2f, 0.2f, 0.2f));
    while (e->getStateValidity()) { 
	ctrl->rotate(0.00001f, Eigen::Vector3f::UnitZ());
	ctrl->rotate(0.00005f, Eigen::Vector3f::UnitX());
    }

    delete e;
    return 0;
}
