/*struct vert
{
	vec3 position;
	vec4 color;
	vec3 normal;
	vec2 texel;
};
attribute vert vertex;*/
attribute vec4 position;
attribute vec2 attr_uv;
varying vec2 vary_uv;
uniform mat4 viewportMatrix;
void main() {
	gl_Position = viewportMatrix * position;
	vary_uv = attr_uv;
}