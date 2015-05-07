#version 440

in vec3 fNormal;
out vec4 outColor;

void main() {
  vec4 spec = vec4(0.0);
  vec3 lDir = vec3(1.0,1.0,.3);
  vec3 eye = vec3(0.0, 0.0, 0.0);
  
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
  0utColor = max(intensity * diffuse + spec, ambient);
  //outColor = vec4(0,0.3,0, 1.0);
}
