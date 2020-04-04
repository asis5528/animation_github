#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{    
    FragColor = texture(tex, TexCoords)*vec4(1.,1.,0.,1.);
    //FragColor = vec4(TexCoords,0.5,1.0);
}