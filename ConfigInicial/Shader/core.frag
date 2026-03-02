#version 330 core
out vec4 color;

// Esta es la variable nueva que recibirá el color sólido
uniform vec3 objectColor;

void main() {
    color = vec4(objectColor, 1.0f);
}