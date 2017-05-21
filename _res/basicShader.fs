#version 140

uniform sampler2D texSampler;

varying vec2 fragTexCoord;
varying vec3 fragNormal;
varying mat4 fragView;

void main() {
	gl_FragColor = texture(texSampler, fragTexCoord) * clamp( dot( ( fragView *vec4( -vec3(1,1,1), 0 ) ).xyz, fragNormal ), 0.5, 1.0 );
}




