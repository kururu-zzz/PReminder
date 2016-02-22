/*struct vert
{
	vec3 position;
	vec4 color;
	vec3 normal;
	vec2 texel;
};
attribute vert vertex;*/
attribute vec4 position;
uniform mat4 viewportMatrix;
void main() {
	gl_Position = viewportMatrix * position;
}