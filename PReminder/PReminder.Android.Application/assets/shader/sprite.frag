uniform sampler2D uniform_texture;
varying vec2 vary_uv;
precision lowp float;
void main() {
	gl_FragColor = texture2D(uniform_texture, vary_uv);
}