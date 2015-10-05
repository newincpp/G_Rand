#pragma once

#include "material.hh"
#include "renderTexture.hh"

namespace GRand {
    class ppMaterial : public Material {
	public:
	    explicit ppMaterial(Core*, RenderTexture* rt_);
	    ~ppMaterial();
    };
}
