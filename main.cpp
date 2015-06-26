#include <vector>
#include <unistd.h>
#include <iostream>

#include <GRand>

int main(int ac, char** av) {
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0.05f, 0.05f, 0.05f, 0.0f);} );
    e->addPersistantInstruction([](){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); });
    GRand::Material mat(e);
    std::vector<GRand::Mesh> mesh;

    mat.addShader(GL_FRAGMENT_SHADER, "./shaders/phongFrag.glsl");
    mat.addShader(GL_VERTEX_SHADER, "./shaders/phongVert.glsl");
    mat.link();

    if (ac > 1) {
	int i = 1;
	while (ac > i) {
	    std::cout << av[i] << std::endl;
	    mesh.emplace_back(e, &mat);
	    mesh[mesh.size() - 1].fromFile(av[i]);
	    ++i;
	}
    } else {
	mesh.emplace_back(e, &mat);
	mesh[0].fromFile("./testModels/monkey.dae");
    }

    GRand::Texture t("tex.png");
    mat.addTexture(&t);

    GRand::Controller* ctrl = mesh[0].genController();
    //ctrl->translate(Eigen::Vector3f(0,0,1.0f));
    //ctrl->rotate(1.571f, Eigen::Vector3f::UnitX());
    //ctrl->scale(Eigen::Vector3f(0.8f, 0.8f, 0.8f));
    GRand::Camera cam(e);
    cam.setPos(GRand::Camera::VectorType(0,.2,0.6));
    cam.lookAt(GRand::Camera::VectorType(0,0,1.4));

    ctrl->rotate(0, GRand::Camera::VectorType(0.0f,1.0f,0.0f));
    ctrl->translate(GRand::Camera::VectorType(0.0f,-0.5f,0.0f));
    ctrl->scale(GRand::Camera::VectorType(0.1f,0.1f,0.1f));

    while (e->getStateValidity()) { 
	usleep(10000);
	ctrl->rotate(0.01, GRand::Camera::VectorType(0.0f,1.0f,0.0f));
    }

    delete e;
    return 0;
}
