#include <vector>
#include <unistd.h>
#include <iostream>

#include <GRand>

int main(int ac, char** av) {
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

    if (ac > 1) {
	int i = 1;
	while (ac > i) {
	    mesh.emplace_back(e, mat);
	    mesh[mesh.size() - 1].fromFile(av[i]);
	    std::cout << "generated: " << av[i] << std::endl;
	    ++i;
	}
    } else {
	mesh.emplace_back(e, mat);
	mesh[0].fromFile("./testModels/monkey.dae");
    }

    GRand::Texture t;
    mat.addTexture(&t);

    GRand::Controller* ctrl = mesh[0].genController();
    GRand::Camera cam(e);
    cam.setPos(GRand::Camera::VectorType(0,.2,1.1));
    cam.lookAt(GRand::Camera::VectorType(0,0,1.4));

    ctrl->translate(GRand::Camera::VectorType(0.5,0.7,0.0f));
    ctrl->scale(GRand::Camera::VectorType(0.5f,0.5f,0.0f));

    e->noPostProcess(true);

    //e->setMaterialPostProcess(postProcessMat);

    float fps_Sample[10000];
    unsigned int i = 0;
    float avg = 0;
    while (e->getStateValidity()) { 
	ctrl->rotate(0.00001 * TO_SECOND(avg), GRand::Camera::VectorType(0.0f,1.0f,0.0f));
	//std::cout << "avg: " << avg << " " << TO_SECOND(avg) << std::endl;
	fps_Sample[i] = e->getRenderTime();
	if (i == (10000 - 1)) {
	    for (float sample : fps_Sample) {
		avg += sample;
	    }
	    avg = avg / 10000;
	    //std::cout << avg << " ns = " << 1 / (e->getRenderTime() / 1000000000) << "fps" << std::endl;
	    //std::cout <<  TO_SECOND(avg) << " ns = " << 1 / (e->getRenderTime() / 1000000000) << "fps\r";
	    i = 0;
	}
	++i;
    }

    delete e;
    return 0;
}
