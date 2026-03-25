#version 330 core

// Estructura del material
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Estructura de la luz
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Entradas desde el Vertex Shader
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Salida de color
out vec4 color;

// Variables Uniformes (recibidas desde C++)
uniform vec3 viewPos;
uniform Material material;
uniform Light light;    // Tu luz original
uniform Light light2;   // Tu nueva luz

// Textura del modelo
uniform sampler2D texture_diffuse1; 

void main()
{
    // Extraemos el color de la textura
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    
    // Un pequeño truco: si el modelo no tiene textura, texColor será negro (0,0,0). 
    // En ese caso, usamos el color difuso del material (ideal para tu perro rojo si no usa textura).
    vec3 baseColor = texColor.rgb;
    if(length(baseColor) < 0.1) {
        baseColor = material.diffuse;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // ==========================================
    // CÁLCULO DE LA LUZ 1 (Luz Original)
    // ==========================================
    vec3 ambient1 = light.ambient * material.ambient * baseColor;
    
    vec3 lightDir1 = normalize(light.position - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 diffuse1 = light.diffuse * (diff1 * baseColor);
    
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), material.shininess);
    vec3 specular1 = light.specular * (spec1 * material.specular);
    
    // ==========================================
    // CÁLCULO DE LA LUZ 2 (Nueva Luz)
    // ==========================================
    vec3 ambient2 = light2.ambient * material.ambient * baseColor;
    
    vec3 lightDir2 = normalize(light2.position - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = light2.diffuse * (diff2 * baseColor);
    
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material.shininess);
    vec3 specular2 = light2.specular * (spec2 * material.specular);
    
    // ==========================================
    // RESULTADO FINAL
    // ==========================================
    // Sumamos la contribución de ambas luces
    vec3 result = (ambient1 + diffuse1 + specular1) + (ambient2 + diffuse2 + specular2);
    
    color = vec4(result, 1.0);
}