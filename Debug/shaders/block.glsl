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
out vec3 vpos;

const vec3 sun = normalize(vec3(-0.5, -0.5, 1));

void main(void)
{
	vec4 pos = vec4(in_vertex, 1.0);
	vec3 delta = vec3(sin(pos.x + time * 4), sin(pos.y + time * 4), sin(pos.z + time * 2.0));
	pos.xyz += delta * 0.1;
	
	gl_Position = matproj * matview * pos;
	
	float dotsun = 0.7 + 0.3 * dot(in_normal, sun);
	
	out_color = vec4(in_color.rgb * dotsun, in_color.a);
	vpos = in_vertex;
}

#endif
#ifdef FRAGMENT_PROGRAM

in vec4 out_color;
in vec3 vpos;

const float PI = 3.14159265357989;

void main(void)
{
	vec3 pos = abs(fract(vpos) - vec3(0.5));
	
	const float N = 4.0;
	vec3 fxd = pow(pos, vec3(N));
	float dist = 1.0 - pow(fxd.x + fxd.y + fxd.z, 1.0 / N);
	
	vec4 color = out_color;
	color.rgb *= dist;
	
	gl_FragData[0] = color;
}

#endif

