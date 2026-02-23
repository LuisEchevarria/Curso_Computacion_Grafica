#version 330 core
in vec3 ourColor;
out vec4 color;

uniform int boxType; 

void main()
{
    if(boxType == 1) {
        // Caja 1: Pastel original (RGB)
        color = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f); 
    } 
    else if(boxType == 2) {
        // Caja 2: Nuevo pastel (GBR)
        color = vec4(ourColor.g, ourColor.b, ourColor.r, 1.0f); 
    } 
    else if(boxType == 3) {
        // Caja 3: Nuevo pastel (BRG)
        color = vec4(ourColor.b, ourColor.r, ourColor.g, 1.0f); 
    } 
    else {
        // Caja 4: Nuevo pastel (RBG)
        color = vec4(ourColor.r, ourColor.b, ourColor.g, 1.0f); 
    }
}