#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 normal;
in vec4 pos;
uniform sampler2D tex;

void main()
{    
	vec3 N = normalize(normal.xyz);
	vec3 P = vec3(pos.xyz);
	vec3 V = normalize(-P);
	vec4 rim = pow(
smoothstep(0.0, 1.0, 1.0 - dot(N, V)),
1.25) * vec4(1.0);
    FragColor =vec4(N,1.0);
    //FragColor = vec4(TexCoords,0.5,1.0);
}