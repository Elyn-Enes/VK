#version 140

varying vec2 tex_coord0;
varying vec3 normal0;
varying vec3 position0;
varying mat4 transform0;
varying mat4 mesh_transform0;

uniform sampler2D diffuse;

uniform vec3 lightIntensities; 
uniform vec3 lightPosition;

void main() {

    mat3 normalMatrix = transpose( inverse( mat3( transform0 ) ) );
	vec3 normal = normalize( normalMatrix * normal0 );
	vec3 fragPosition = vec3( transform0 * vec4( position0, 1 ) );
	vec3 surfaceToLight = lightPosition- fragPosition;

	float brightness = dot( normal, surfaceToLight ) / length( surfaceToLight ) * length( normal0 );
	brightness = clamp(brightness, 0, 1);

	vec4 surfaceColor = texture( diffuse, tex_coord0 );

	gl_FragColor =  vec4( brightness * lightIntensities * surfaceColor.rgb, surfaceColor.a );
}





