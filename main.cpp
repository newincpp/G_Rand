#include <unistd.h>
#include <iostream>

#include <GRand>

int main(void){
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0.05f, 0.05f, 0.05f, 0.0f);} );
    e->addPersistantInstruction([](){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); });
    GRand::Material mat;
    GRand::GPUBuffer gb;
    gb.loadFile("./testModels/monkey.dae");

    GRand::Mesh mesh(e, &mat);
    mesh.set(gb);

    PUSH_CORE_INSTA(e, mat, mat.addShader(GL_FRAGMENT_SHADER, "./shaders/phongFrag.glsl"); );
    PUSH_CORE_INSTA(e, mat, mat.addShader(GL_VERTEX_SHADER, "./shaders/phongVert.glsl"); );

    //PUSH_CORE_INSTA(e, mat, mat.addShader(GL_FRAGMENT_SHADER, "./shaders/simpleFrag.glsl"); );
    //PUSH_CORE_INSTA(e, mat, mat.addShader(GL_VERTEX_SHADER, "./shaders/simpleVert.glsl"); );
    PUSH_CORE_INSTA(e, mat, mat.link());

    GRand::Controller* ctrl = mesh.genController();
    //ctrl->translate(Eigen::Vector3f(0,0,1.0f));
    //ctrl->rotate(1.571f, Eigen::Vector3f::UnitX());
    //ctrl->scale(Eigen::Vector3f(0.8f, 0.8f, 0.8f));
    GRand::Camera cam(e);

    ctrl->rotate(-1.571, Eigen::Vector3f::UnitX());
    ctrl->translate(Eigen::Vector3f(0,0,0));
    ctrl->scale(Eigen::Vector3f(0.3,0.3,0.3));
    while (e->getStateValidity()) { 
	usleep(10000);
	cam.translate(Eigen::Vector3f(0,0,0.01));
	//ctrl->rotate(0.01, Eigen::Vector3f::UnitZ());
    }

    delete e;
    return 0;
}
