#!/bin/bash

# 1. Verifica se o ecrã virtual já está a correr. Se não estiver, inicia os serviços.
if ! pgrep -x "Xvfb" > /dev/null
then
    echo "A preparar o ecrã virtual e o servidor Web..."
    # Cria o ecrã virtual
    Xvfb :0 -screen 0 1024x768x24 &
    sleep 1
    # Inicia o gestor de janelas
    openbox &
    # Inicia o servidor VNC
    x11vnc -display :0 -nopw -forever -bg > /dev/null 2>&1
    # Converte o VNC para o Navegador Web na porta 8080
    websockify --web /usr/share/novnc/ 8080 localhost:5900 > /dev/null 2>&1 &
fi

echo "================================================="
echo "Servidor Web pronto! Aceda a: http://localhost:8080"
echo "================================================="
echo "A iniciar a aplicação Qt..."

# 2. Executar a sua aplicação C++ (Ajuste o caminho se necessário)
/app/build/BuscadorFilmesGUI