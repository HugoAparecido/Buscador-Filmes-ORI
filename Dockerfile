# Dockerfile
FROM ubuntu:22.04

# Evita prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instala compiladores, ferramentas de build e debug
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    clang \
    valgrind \
    git \
    && rm -rf /var/lib/apt/lists/*

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Comando padrão ao iniciar o container (mantém o container vivo para desenvolvimento)
CMD ["/bin/bash"]