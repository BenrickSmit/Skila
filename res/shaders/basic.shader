#shader vertex
#version 330 core  
  
in vec4 position;  
  
void main(){  
gl_Position=position;  
  
};

#shader fragment
#version 330 core  
  
out vec4 color;  
  
void main(){  
color=vec4(0.2, 0.3, 0.8, 1.0);  
  
};