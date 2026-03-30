#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texLight;

void main()
{
    vec4 texColor = texture(texLight, TexCoords);
    
    // Si el pixel es transparente, lo descartamos (evita errores visuales en 3D)
    if(texColor.a < 0.1)
        discard;
        
    color = texColor;
}