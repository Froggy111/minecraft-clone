#version 460

in vec2 tex_coords_f;

uniform sampler2D texture_f;

out vec4 colour_f;

void main(void) {
  colour_f = texture(texture_f, tex_coords_f);
  return;
}   