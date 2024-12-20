#version 130

#define MAX_LIGHTS 4

in vec3 position; 
in vec3 normal;
in vec2 texpos;

uniform mat4 view;
uniform mat4 model;
uniform mat4 modelView;
uniform mat4 modelViewProjection;
uniform mat3 mv_inverse_transpose;

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	int shininess;
};
uniform Material material;

//INFORMACE O SVETLECH
uniform vec4 lights[30]; // kazde tri vektory odpovidaji jednomu svetlu: pozice, difuzni, ambientni slozka; max 10 svetel
uniform int enabledLights; // pocet pouzitych svetel (naplnenych do lights)

//SOURADNICE OKA
out vec3 eyeLightPos[MAX_LIGHTS];
out vec3 eyeNormal; // normala zkomaneho bodu v prostoru OKA
out vec3 eyePosition; // pozice zkoumaneho bodu v prostoru OKA

out vec3 oPosition; //pozice vertexu

//PREDAVANI TEXTUROVACICH SOURADNIC DO FRAGMENT SHADERU
out vec2 t;


void main() {
	vec4 pos = vec4(position, 1.0);
	gl_Position = modelViewProjection * pos;
	t = texpos;
	oPosition = position;

	//transformace normaly do eyespace
	eyeNormal = normalize(mv_inverse_transpose * normal);

	//transformace zkoumaneho bodu do eyespace
	vec4 eyePosition4 = modelView * pos;
	eyePosition = eyePosition4.xyz / eyePosition4.w;

	
	////////////////////////////SVETLO /////////////////////////////////////
	// predpokladame enabledLights > 0
	for(int i =0; i < enabledLights; i++) {
		vec4 lightPosition = lights[i * 3 + 0]; // i - index svetla

		//transformace svetla z worldspace do eyespace
		vec4 lightPos4 = view * lightPosition;
		eyeLightPos[i] = lightPos4.xyz / lightPos4.w ;
	} 
}
