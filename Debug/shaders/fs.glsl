#version 130

#define VERTEX_PROGRAM
#define FRAGMENT_PROGRAM

#ifdef VERTEX_PROGRAM

in  vec3 in_vertex;
out vec2 texCoord;

void main(void)
{
	gl_Position = vec4(in_vertex, 1.0);
	texCoord = in_vertex.xy * 0.5 + vec2(0.5);
}

#endif
#ifdef FRAGMENT_PROGRAM

uniform sampler2D texture;

in vec2 texCoord;

void main(void)
{
	vec4 color = texture2D(texture, texCoord.st);
	
	gl_FragColor = color;
}

#endif
