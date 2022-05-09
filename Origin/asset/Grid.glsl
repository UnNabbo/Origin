#Type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;


uniform mat4 u_ProjectionView;

out vec4 v_Color;

out vec2 v_TexCoord;

flat out float v_TextureIndex;

out vec3 vertexPosition;

void main() {
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TextureIndex = a_TexIndex;
    vertexPosition = a_Position;
	gl_Position =  u_ProjectionView  * vec4(a_Position,1.0f);
}

#Type pixel
#version 460 core

layout(location = 0) out vec4 color;


in vec4 v_Color;

in vec2 v_TexCoord;

flat in float v_TextureIndex;

uniform sampler2D u_Textures[32];

in vec3 vertexPosition;
const float squareSize = 5;
const vec3 color_l1 = vec3(1,1,0);

void main() {
	
	float dXy = abs(dFdx(vertexPosition.y)) / 2.0;
    float dYy = abs(dFdy(vertexPosition.y)) / 2.0;
    float dXx = abs(dFdx(vertexPosition.x)) / 2.0;
    float dYx = abs(dFdy(vertexPosition.x)) / 2.0;

    // find and fill horizontal lines
    int roundPos = int(vertexPosition.y / squareSize);
    float remainder = vertexPosition.y - float(roundPos)*squareSize;
    float width = max(dYy, dXy) * 2.0;

    if (remainder <= width/2)
    {
        float diff = (width - remainder) / width;
        color = vec4(color_l1, diff);
        return;
    }

    if (remainder >= (squareSize - width))
    {
        float diff = (remainder - squareSize + width) / width;
        //color = vec4(color_l1, diff);
        return;
    }

    // find and fill vertical lines
    roundPos = int(vertexPosition.x / squareSize);
    remainder = vertexPosition.x - float(roundPos)*squareSize;
    width = max(dYx, dXx) * 2.0;

    if (remainder <= width)
    {
        float diff = (width - remainder) / width;
        //color = vec4(color_l1, diff);
        return;
    }

    if (remainder >= (squareSize - width))
    {
        float diff = (remainder - squareSize + width) / width;
        //color = vec4(color_l1, diff);
        return;
    }

    // fill base color
    color = vec4(0,0,0, 0);
    return;

}