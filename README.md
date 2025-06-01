# GL4-Cat

# 🐱 GLSL Cat Renderer | OpenGL 4.4 Core

![Cat Render Demo](screenshot.jpg) <!-- Add your screenshot later -->

A **trippy 2D cat** rendered with modern OpenGL 4.4 Core Profile, featuring full RGB lighting effects and camera controls. Made with C++ and pure graphics wizardry 🧙‍♂️.

## 🔥 Features
- **Physically-based lighting**: 
  - Ambient occlusion
  - Diffuse scattering
  - Specular highlights (RGB reflections)
- **Interactive controls**:
  - 🌀 Rotate cat in 3D space
  - 🚀 Move/translate freely
  - 🔁 Flip vertically/horizontally
  - 📏 Dynamic resizing
- **Perspective camera** with zoom/pan
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
git clone --recursive https://github.com/yourusername/opengl-cat.git

# Build (CMake required)
mkdir build && cd build
cmake ..
make -j4

# Run the majestic cat!
./GlowingCat
