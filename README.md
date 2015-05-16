# G_Rand
G_Rand is a tiny portable OpenGL based engine with minimal dependency at execution.
G_Rand is using OpenGL for now for rendering but it is written with Vulkan in mind (openGL will be dropped when Vulkan will be released).
This engine is purely public which imply:
-you can download it modity it as you want without any obligation (you don't even need to ask me to copy it)
-I will accept most of pull request
-this engine will be free for all and forever
-this engine do not include any library that imply restrictive licence


*what does G_Rand support now*
easy mesh loading with assimp with element buffer and normals
easy glsl sader architecture
thead separated rendring
simple direct phong shading
remote-style transformation (see controller class example)
easy display configuration
easy/casi-invisible Uniform values

*what does still not work properly*
MVP matrix has some bugs
persistant instruction cannot be deleted at all
_a lot_ of features in the mesh are ignored
light are static to the shader for now (for test purpuse)

*what is planed soon*
textures (every types in the generic way)
framebuffer rendering
multipass shader
dynamic lights

*what I like to implement but not sure if I will have time* (I will be very happy to see pull request about that)
animation system with interpolation
BVH support
mesh deform target
GPU sprites particle
Vectorfield for GPU sprite particle

*what I would like to add but I have no idea how it work yet* (if you know how it work I will be happy to ear your explanation)
SSAO
volume light propagation
physically based shading model
diffraction/relfection (using volume capture ?)


I know this is still a few features, if you want to add one just say me (pull request, issue...) =)

you can talk to me directly using twitter-> @newincpp
