# Buscador-Filmes-ORI

Criação de um buscador de filmes utilizando Árvore B+ e Índice Invertido, este é um trabalho a ser apresentado para a matéria de ORI

## Para colaboradores

### Como usar

Suba o container em segundo plano:

```bash
docker compose up -d
```

Acesse o terminal do container para compilar e testar seu código com desempenho nativo:

```bash
docker compose exec cpp-dev bash
```

### Atualização de repositório

#### 1. Atualize seu repositório local

Antes de começar a trabalhar, garanta que seu código está sincronizado com a versão mais recente do projeto:

```bash
git checkout main
git pull origin main
```

#### 2. Crie uma Branch para a nova função

Sempre crie uma branch específica para o que você vai desenvolver. Use nomes claros e descritivos.

```bash
git checkout -b feature/nome-da-sua-funcao
```

#### 3. Faça suas alterações e prepare os Commits

Após escrever seu código, você precisa prepará-lo para o commit via terminal.

Para adicionar todos os arquivos modificados:

```bash
git add .
```

(Se preferir adicionar arquivos específicos, use git add nome-do-arquivo.extensão)

Crie o commit com uma mensagem clara sobre o que foi feito:

```bash
git commit -m "feat: adiciona a função X para resolver Y"
```

#### 4. Envie a Branch para o repositório remoto

Agora, envie a sua nova branch com os commits para o GitHub:

```bash
git push origin feature/nome-da-sua-funcao
```

#### 5. Crie o Pull Request (PR)

1. Acesse a página do repositório no GitHub.

2.Você verá um aviso amarelo sugerindo criar um PR para a sua branch recém-enviada. Clique em Compare & pull request.

3. Título: Dê um título claro e resumido.

4. Descrição: Explique o que foi alterado. Se a sua branch resolve um problema específico, mencione qual é.

5. Clique em Create pull request.
