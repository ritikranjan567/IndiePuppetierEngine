# OpenGL NOTES

## Vertex Data and VBO

Shapes are drawn using vertex data, which contains information like position, color, texture coordinates, normals, etc.

Passing vertex data to the GPU one by one is inefficient.

Therefore, **Vertex Buffer Objects (VBOs)** are used to store and send vertex data in batches.

### Create VBO with unique ID

```cpp
unsigned int VBO;
glGenBuffers(1, &VBO);
```

// 1 because this function can create multiple buffers at once.

### Bind it and copy data

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

- `GL_ARRAY_BUFFER`: Buffer binding target.
- `sizeof(vertices)`: Size of data in bytes.
- `vertices`: Actual vertex data.
- `GL_STATIC_DRAW`: Data is mostly set once and used many times.

---

## Vertex and Fragment Shaders

### Get vertex shader source in const char* format

### Create shader and compile

```cpp
unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

### Check compilation status

```cpp
int success;
char infoLog[512];

glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
}
```

Similarly, repeat the above steps for the fragment shader using `GL_FRAGMENT_SHADER`.

---

## Shader Program

Create a shader program to attach shaders and link them.

```cpp
unsigned int shaderProgram = glCreateProgram();

glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);

glLinkProgram(shaderProgram);

### Check for linking errors

glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
              << infoLog << std::endl;
}
```

### Use program and delete shaders

After successfully linking, shaders are no longer needed separately.

```cpp
glUseProgram(shaderProgram);

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

---

## Vertex Attributes

Map parts of the vertex data to shader attribute locations (position, color, texture, etc.).

```cpp
glVertexAttribPointer(
    attribute_index,
    number_of_components,
    data_type,
    should_normalize,
    stride_in_bytes,
    pointer_to_byte_offset
);

glEnableVertexAttribArray(0);
```

Example:

```cpp
glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE,
    3 * sizeof(float), (void*)0
);

glEnableVertexAttribArray(0);
```

---

## Vertex Array Object (VAO)

VAO stores:

- Vertex attribute configurations.
- Enabled vertex attribute states.
- References to the VBOs associated with vertex attributes.

It does NOT store actual vertex data or shader programs.

In modern OpenGL core profile, a VAO must be bound for drawing.

### Create and bind VAO

```cpp
unsigned int VAO;

glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
```

### Configure VAO

The following steps should be performed while the VAO is bound.

```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(vertices),
    vertices,
    GL_STATIC_DRAW
);

glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE,
    3 * sizeof(float), (void*)0
);

glEnableVertexAttribArray(0);
```

VAO remembers the vertex attribute configuration and associated VBO.

Switching VAOs allows us to switch between different vertex input configurations without repeating the attribute setup.

**Note:** `glVertexAttribPointer()` captures the currently bound `GL_ARRAY_BUFFER` as the buffer associated with that attribute.

---

## Draw Triangle

glUseProgram(shaderProgram);
glBindVertexArray(VAO);

glDrawArrays(GL_TRIANGLES, 0, 3);

- `GL_TRIANGLES`: Draw triangles.
- `0`: Starting vertex index.
- `3`: Number of vertices to draw.

---

## 7Overall Steps

1. Initialize GLFW or SDL and create a window.
2. Create VAO and bind it.
3. Create VBO and bind it.
4. Upload vertex data using `glBufferData`.
5. Define vertex attributes using `glVertexAttribPointer`.
6. Enable required vertex attributes using `glEnableVertexAttribArray`.
7. Load and compile vertex and fragment shaders.
8. Create shader program, attach shaders and link.
9. Use shader program when rendering.

**Note:** Steps 2–6 configure the VAO. Shader compilation and linking are independent of VAO configuration.

---

## Rendering Loop

Inside the rendering loop:

- Clear the screen.
- Perform rendering logic.
- Use shader program (`glUseProgram`).
- Bind VAO (`glBindVertexArray`).
- Draw (`glDrawArrays`).
- Swap buffers and poll events.

```cpp
while (!glfwWindowShouldClose(window))
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

## Element Buffer Object (EBO)
Suppose when render a two triangles and froming a rectangle; we need 6 vertices. However two of the vertices are shared/common in both the triangles.
These duplicates vertices data creates overhead on memory and drawning as well.

Solution is EBO, as this is a buffer like VBO and should be bound to VAO.
With this just define a indices array telling opengl how to draw two triangles with just 4 vertices.
`indices` array contains map to indices of the array `vertices`
```cpp
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
}; 
```

Creating and Binding EBO:
```cpp
unsigned int EBO;
glGenBuffers(1, &EBO);


glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// in loop
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glDrawElements(GL_TRIANGLES, 
    6, // number of vertices, 
    GL_UNSIGNED_INT, // data type of indices
    0 // offset
); // replaces glDrawArrays
```

## Good to have functions
- `glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);` to switch between wireframe `GL_LINE` and fill `GL_FILL` (default)

---
