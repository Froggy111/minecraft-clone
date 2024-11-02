#version 460

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 tex_coords_v;

uniform mat4 model_transform;
uniform mat4 perspective_transform;

out vec2 tex_coords_f;

void main(void) {
  gl_Position = perspective_transform * model_transform * vertex;
  tex_coords_f = tex_coords_v;
  return;
}