#version 410 core

in vec2 v_TexCoord;
layout(location = 0) out vec4 color;

uniform vec4 u_Color = vec4(1.0,1.0,1.0,1.0);
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = u_Color * texColor;
}

