precision highp float;

in vec3 vWorldNormal;
in vec3 vSH0;
in vec3 vSH1;
in vec3 vSH2;
in vec3 vSH3;

out vec4 FragColor;

void main(void)
{
	// fast SH4
	vec3 ambient = vSH0 +
		vSH1 * vWorldNormal.y +
		vSH2 * vWorldNormal.z +
		vSH3 * vWorldNormal.x;
	
	FragColor = vec4(ambient * 0.9, 1.0);	// fix 0.9 for SH4
}
