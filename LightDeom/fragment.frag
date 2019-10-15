#version 330 core

out vec4 FragColor;
in vec2 TextCoord;
//struct Material{
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//	float shininess;
//};

struct Material{
	vec3 ambient;
	sampler2D  diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;
uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform float constant;
uniform float linear;
uniform float quadratic;

//uniform vec3 lightDirU;
in vec3 Normal;
in vec3 FragPos;

void main(){
	float dist = length(lightPos - FragPos);
	float attenuation = 1.0 / (constant + linear * dist + 
                quadratic * (dist * dist));

	//Amibent
	//vec3 ambient = lightColor * material.ambient;

	//Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = lightColor * (diff * material.diffuse);
	vec3 diffuse =  diff  * texture(material.diffuse, TextCoord).rgb * lightColor;

	vec3 ambient = lightColor * texture(material.diffuse, TextCoord).rgb;

	// specular
	vec3 cameraDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * spec * texture(material.specular, TextCoord).rgb;  

	vec3 result = (diffuse + (ambient + specular) * attenuation ) * objColor;
	FragColor = vec4(result, 1.0);
	//FragColor =vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//FragColor = vec4(FragPos, 1.0f);

}