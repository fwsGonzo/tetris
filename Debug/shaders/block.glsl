#version 130

#define VERTEX_PROGRAM
#define FRAGMENT_PROGRAM

#ifdef VERTEX_PROGRAM

uniform mat4 matproj;
uniform mat4 matview;
uniform float time;

in vec3 in_vertex;
in vec3 in_normal;
in vec4 in_color;

out vec4 out_color;

const vec3 sun = normalize(vec3(-1, -1, 1));

void main(void)
{
	vec4 pos = vec4(in_vertex, 1.0);
	vec3 delta = vec3(sin(pos.x + time * 4), sin(pos.y + time * 4), sin(pos.z + time * 2.0));
	pos.xyz += delta * 0.1;
	
	gl_Position = matproj * matview * pos;
	
	float dotsun = 0.8 + 0.2 * dot(in_normal, sun);
	
	out_color = vec4(in_color.rgb * dotsun, in_color.a);
}

#endif
#ifdef FRAGMENT_PROGRAM

in vec4 out_color;

void main(void)
{
	vec4 color = out_color;
	
	gl_FragData[0] = color;
}

#endif

