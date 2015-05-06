#version 440

in vec3 fNormal;
in mat4 cameraLoc;
out vec4 outColor;

void main() {
    vec3 lightdir = vec3(1, 0, 1);

    // material
    vec4 diffuse = vec4(0, 0.3, 0.0, 1.0);
    vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);
    vec4 specular = vec4(0.5,0.5,0.5,0.9);
    float shininess = 0.5;

    vec3 eye = vec3(0,0,-2);


    vec4 spec = vec4(0.0);

    // normalize both input vectors
    vec3 n = normalize(fNormal);
    vec3 e = normalize(eye);

    float intensity = max(dot(n,lightdir), 0.0);

    if (intensity > 0.0) {
	// compute the half vector
	vec3 h = normalize(lightdir + e);  
	// compute the specular term into spec
	float intSpec = max(dot(h,n), 0.0);
	spec = specular * pow(intSpec,shininess);
    }
    outColor = max(intensity *  diffuse + spec, ambient);
    //outColor = vec4(0,0.3,0, 1.0);
}
