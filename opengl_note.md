## Opengl NOTES

Shapes are drawn from vertex data, which is stores in vertex array.
Elements of this array represents vertex info like position, color, texture, etc.

Passing these to GPU 1 by 1 is slow.

Therefore `Vertex Buffer Object` is used to manage and send vertices to the GPU in batch.  

Step 1:  
Create VBO with unique ID
```cpp
unsgined int VBO;
glGenBuffers(1, &VBO); 
// 1 because, above fuction can be used to create multiple buffers at once, with n, *vbos
```
Step 2:
Bind it
```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
```

step 3:  
Configure current VBO and copy vertices 
```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

step 4:  
Get the vertex_shader source in const char* formate




