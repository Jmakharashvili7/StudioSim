#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aCol; // the color variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

uniform mat4 u_viewProjection;

void main()
{
    gl_Position = u_viewProjection * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(aCol, 1.0); // set the output variable to a dark-red color
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
}
