//21_6_6 teapot f shader
#version 330 core

out vec4 FragColor;

struct Material
{
	float shininess;
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

struct Light
{
	vec3 position;
	vec3 position2;
	vec3 diffuse;
	vec3 diffuse2;
	vec3 specular;
	vec3 ambient;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Material material;
uniform Light light;

uniform sampler2D mytex;
uniform vec3 eyePos;
uniform bool is_quantized;
uniform bool is_textured;
uniform bool set_light2;

void main()
{
	float weight_diff, weight_diff2, weight_specu;
	vec3 result, diffuse, specular;
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 veiw_vec = normalize(eyePos - FragPos);
	
	// diffuse
	weight_diff = max(dot(Normal, lightDir), 0);

	// nonphotorealistic : quantization
	if(is_quantized)
	{
		float weight_diff_mod = int(weight_diff*100)%20;
		weight_diff -= float(weight_diff_mod)/100;
	}

	diffuse = light.diffuse * (weight_diff * material.diffuse);

	// set texture
	if(is_textured)
		diffuse *= vec3(texture(mytex, TexCoord));
	// set light2
	if(set_light2)
	{
		weight_diff2 = max(dot(light.position2, Normal), 0);
		diffuse += weight_diff2 * light.diffuse2 * material.diffuse;
	}


	// specular
	vec3 refl_vec = 2.0f * Normal * dot(Normal, lightDir) - lightDir;
	weight_specu = pow(max(dot(refl_vec, veiw_vec), 0), material.shininess);
	specular = light.specular * (weight_specu*material.specular);

	// ambient
	vec3 ambient = light.ambient*material.ambient;

	result = diffuse + specular + ambient;
	//FragColor = vec4(result, 1.0f);
	//point light source
	vec3 dist_vec = light.position-FragPos;
	FragColor = vec4(result, 1.0f)/dot(dist_vec, dist_vec);
}