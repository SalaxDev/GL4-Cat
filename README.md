# GLSL Cat Renderer

# 🐱 GLSL Cat Renderer | OpenGL 4.4 Core

![Cat Render](preview.png)

## 🔥 Features
- **lighting**: 
  - Ambient occlusion
  - Diffuse scattering
  - Specular highlights (RGB reflections)
- **Interactive controls**:
  - Rotate
  - Move
  - Flip vertically
  - resizing
- **Perspective camera**
- **Texture loading** via SOIL2
- **Matrix transformations** powered by GLM

## ⚙️ Tech Stack
| Component       | Technology     |
|-----------------|----------------|
| Graphics API    | OpenGL 4.4 Core|
| Math Library    | GLM            |
| Window/Input    | GLFW 3.3+      |
| Loader          | Glad           |
| Image Loading   | SOIL2          |
| Language        | C++17          |

## 🚀 Building & Running
```bash
# Clone with submodules
git clone https://github.com/yourusername/opengl-cat.git

# Build (CMake required)
mkdir build
cd build
cmake ..
cmake --build .

# Run the Program!
../bin/GL-Cat
```
