#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 normal;
out vec4 pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
	//vec3 v = aPos;
	normal = model*vec4(aNormal,1.0);
	vec4 viewmodel = view*model  * vec4(aPos, 1.0);
	pos = viewmodel;
    gl_Position = projection *viewmodel ;
}
