#version 140

varying vec2 tex_coord0;
varying vec3 normal0;
varying vec3 position0;
varying mat4 transform0;
varying mat4 mesh_transform0;

attribute vec3 position; 
attribute vec2 tex_coord;
attribute vec3 normal; 

uniform mat4 transform;
uniform mat4 mesh_transform;

varying mat4 final_transform;

void main() {
	final_transform = transform * mesh_transform;
	gl_Position = final_transform * vec4( position, 1.0 );
	tex_coord0 = tex_coord;
	position0 = position;
	transform0 = transform;
	mesh_transform0 = mesh_transform;
	normal0 = ( final_transform * vec4( normal, 0.0 ) ).xyz;
}	