ARG VARIANT=ubuntu-24.04
FROM mcr.microsoft.com/devcontainers/base:${VARIANT}

# Install prerequisites
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv \
    python3-dev \
    cmake \
    cmake-curses-gui \
    gfortran \
    && rm -rf /var/lib/apt/lists/*
