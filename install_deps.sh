#!/bin/bash

# Linux (Debian/Ubuntu)
if [ "$(uname)" = "Linux" ]; then
    sudo apt update
    sudo apt install -y build-essential cmake libglfw3-dev libsoil2-dev libgl1-mesa-dev xorg-dev
fi

# macOS
if [ "$(uname)" = "Darwin" ]; then
    brew update
    brew install glfw soil2 glm pkg-config
fi