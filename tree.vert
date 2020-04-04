#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
void main()
{
    TexCoords = aTexCoords;    
	vec3 v = aPos;
	v.x+=sin(time)*(v.y*0.1);
	v.z+=cos(time*2.)*(v.y*0.03);
    gl_Position = projection * view * model * vec4(v, 1.0);
}
