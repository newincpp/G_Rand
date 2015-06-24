#include <unistd.h>
#include <iostream>

#include <GRand>

int main(int ac, char** av){
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0.05f, 0.05f, 0.05f, 0.0f);} );
    e->addPersistantInstruction([](){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); });
    GRand::Material mat(e);
    GRand::GPUBuffer gb;
    if (ac > 1) {
	gb.loadFile(av[1]);
    } else {
	gb.loadFile("./testModels/monkey.dae");
    }

    GRand::Mesh mesh(e, &mat);
    mesh.set(gb);

    mat.addShader(GL_FRAGMENT_SHADER, "./shaders/phongFrag.glsl");
    mat.addShader(GL_VERTEX_SHADER, "./shaders/phongVert.glsl");
    mat.link();

    GRand::Texture t;//("tex.png");
    mat.addTexture(&t);

    GRand::Controller* ctrl = mesh.genController();
    //ctrl->translate(Eigen::Vector3f(0,0,1.0f));
    //ctrl->rotate(1.571f, Eigen::Vector3f::UnitX());
    //ctrl->scale(Eigen::Vector3f(0.8f, 0.8f, 0.8f));
    GRand::Camera cam(e);
    cam.setPos(Eigen::Vector3f(0,-0.4,0));
    cam.lookAt(Eigen::Vector3f(0,-0.3,1));

    //ctrl->rotate(-1.571, Eigen::Vector3f::UnitX());
    ctrl->rotate(0, Eigen::Vector3f::UnitX());
    ctrl->translate(Eigen::Vector3f(0,-0.5,0));
    ctrl->scale(Eigen::Vector3f(0.1,0.1,0.1));

    while (e->getStateValidity()) { 
	usleep(10000);
	ctrl->rotate(0.01, Eigen::Vector3f::UnitY());
    }

    delete e;
    return 0;
}
