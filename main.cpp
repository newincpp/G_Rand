#include <vector>
#include <unistd.h>
#include <iostream>

#include <GRand>

int main(int ac, char**) {
    GRand::Core::Config cfg;
    GRand::Core::Config::autoConf(cfg);
    GRand::Core* e = GRand::Core::start(cfg);
    e->addPersistantInstruction([](){ glClearColor(0.1f, 0.1f, 0.1f, 0.0f);} );
    e->addPersistantInstruction([](){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); });
    GRand::Material mat(e);
    std::vector<GRand::Mesh> mesh;

    mat.addShader(GL_FRAGMENT_SHADER, "./shaders/phongFrag.glsl");
    mat.addShader(GL_VERTEX_SHADER, "./shaders/phongVert.glsl");
    mat.link();

    GRand::Controller* ctrl;
    if (ac == 1) {
	mesh.emplace_back(e, mat);
	mesh[0].fromFile("./testModels/monkey.dae");
    }
    ctrl = mesh[0].genController();
    ctrl->translate(GRand::Camera::VectorType(0.5,0.7,0.0f));
    ctrl->scale(GRand::Camera::VectorType(0.5f,0.5f,0.0f));

    GRand::Texture t("tex.png");
    mat.addTexture(&t);

    GRand::Camera cam(e);
    cam.setPos(GRand::Camera::VectorType(0,.2,1.1));
    cam.lookAt(GRand::Camera::VectorType(0,0,1.4));

    e->noPostProcess(true);

    //e->setMaterialPostProcess(postProcessMat);

    unsigned int i = 1;
    for (std::string line; std::getline(std::cin, line);) {
        mesh.emplace_back(e, mat);
	std::cout << mesh.size() << std::endl;
        mesh[mesh.size() - 1].fromFile(line);
        mesh[mesh.size() - 1].setMaterial(mat);
        mesh[mesh.size() - 1].setExistantController(ctrl);
    }
    std::cout << "run" << std::endl;

    while (e->getStateValidity()) { 
	usleep(10000);
	ctrl->rotate(TO_SECOND(e->getRenderTime()), GRand::Camera::VectorType(0.0f,1.0f,0.0f));
	//std::cout << "avg: " << avg << " " << TO_SECOND(avg) << std::endl;
	std::cout << e->getRenderTime() << " ns\t-\t"; // 677857
	std::cout << 1 / (TO_SECOND(e->getRenderTime())) << " FPS" << std::endl; // 677857
    }

    std::cout << "shutdown" << std::endl;

    delete e;
    return 0;
}
