# Use the official GCC image as the base image
FROM gcc:9.3.0

USER root

RUN useradd -m user

# Set environment variables for raylib version and installation directory
ENV RAYLIB_VERSION 4.5.0
ENV RAYLIB_INSTALL_DIR /raylib

# Install necessary packages and build tools
RUN apt-get update && \
    apt-get install -y \
    git \
    cmake \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libasound2-dev \
    libxcursor-dev \
    libxinerama-dev

# Clone raylib repository from GitHub
RUN git clone https://github.com/raysan5/raylib.git /raylib-src

# Checkout the specific version of raylib
RUN cd /raylib-src && git checkout $RAYLIB_VERSION

RUN cd /raylib-src/src && make -j PLATFORM=PLATFORM_DESKTOP && make install

# Set up a working directory
WORKDIR /app
