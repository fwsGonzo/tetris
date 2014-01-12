#version 130

#define VERTEX_PROGRAM
#define FRAGMENT_PROGRAM

#ifdef VERTEX_PROGRAM

uniform mat4 matproj;
uniform mat4 matview;


in vec3 in_vertex;
in vec3 in_normal;
in vec4 in_color;

out vec4 out_color;

void main(void)
{
	gl_Position = matproj * matview * vec4(in_vertex, 1.0);
	
	out_color = in_color;
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

