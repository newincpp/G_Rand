#version 440

layout(location = 8)uniform int textureAmount;

in vec3 fNormal;
in vec2 fUVCoord;
in vec3 eye;

out vec4 outColor;

uniform sampler2D tex[8];


vec4 lighting() {
    vec4 spec = vec4(0.0);
    vec3 lDir = vec3(1.0,1.0,.3);

    vec4 diffuse = vec4(0.8,0.8,0.8,1);
    vec4 ambient = vec4(0.,0.,0.,1);
    vec4 specular = vec4(0.1,0.1,0.1,1);
    float shininess = 0.7;

    float intensity = max(dot(fNormal, lDir), 0.0);

    if (intensity > 0.0) {
	vec3 h = normalize(lDir + eye);
	float intSpec = max(dot(h,fNormal),0.0);
	spec = specular * pow(intSpec, shininess);
    }
    return max(intensity * diffuse + spec, ambient);
}

void main() {
  outColor = texture(tex[0], fUVCoord) * lighting();
  //while (i < textureAmount) {
  //    outColor *= texture(tex[i], fUVCoord);
  //}
}
