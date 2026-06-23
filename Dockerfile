# Dockerfile
FROM ubuntu:22.04

# Evita prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instala compiladores, ferramentas de build e debug
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-base-dev-tools \
    libgl1-mesa-dev \
    libxkbcommon-dev \
    libxcb-cursor0 \
    gdb \
    clang \
    valgrind \
    git \
    xvfb \
    x11vnc \
    novnc \
    websockify \
    openbox \
    && rm -rf /var/lib/apt/lists/*

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Comando padrão ao iniciar o container (mantém o container vivo para desenvolvimento)
CMD ["/bin/bash"]