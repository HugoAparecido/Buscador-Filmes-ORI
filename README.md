# 🎬 Buscador de Filmes - ORI (Movie Searcher)

Mecanismo de busca e recuperação de dados de filmes baseado em palavras-chave. Este projeto foi desenvolvido como requisito de avaliação para a disciplina de Organização e Recuperação de Informação (ORI). O sistema é estruturado com foco na otimização do acesso a disco e na leitura eficiente das características dos registros utilizando estruturas de dados avançadas.

## 👥 Equipe de Desenvolvimento
* André Luís Miyagaki Filho - 845005
* Danilo Djovano Selli Junior - 842868
* Eduardo Pereira Kobayashi - 846975
* Enzo Furquim Bonetto - 842869
* Hugo Aparecido Gregorio de Almeida - 844917

## ⚙️ Arquitetura e Estruturas de Dados

O buscador foi modularizado para garantir a separação de responsabilidades entre armazenamento, indexação em memória e interface com o usuário:

* **Armazenamento Binário (`Filme`):** Gerencia os dados com campos de tamanho fixo. Realiza a leitura e gravação direta no arquivo binário (`filmes.dat`) utilizando o RRN (*Relative Record Number*) para acesso em tempo $O(1)$.
* **Índice Secundário (`ArvoreBPlus`):** Implementa uma Árvore B+ adaptada para lidar com chaves duplicadas (armazenando listas de RRNs). Conta com a otimização de **prefixo simples**, promovendo apenas a menor substring necessária durante a divisão de nós para economizar memória.
* **Motor de Busca (`IndiceInvertido`):** Camada de recuperação de informação textual. Responsável por tokenizar as strings do dataset e processar consultas realizando a interseção dos conjuntos de RRNs retornados pela Árvore B+.
* **Controlador (`Terminal`):** Orquestra o ciclo de vida da aplicação. Gerencia o menu interativo, o *parsing* inicial da base de dados bruta (`.csv` para `.dat`) e o carregamento do índice para a memória principal.

---

## 🛠️ Guia para Colaboradores

O ambiente de desenvolvimento deste projeto é padronizado através do **Docker** para garantir que todos os membros da equipe compilem e testem o código sob as mesmas condições.

### 1. Inicializando o Ambiente (Docker)

Suba o container em segundo plano:

```bash
docker compose up -d
```

Acesse o terminal do container para compilar e testar seu código com desempenho nativo:

```bash
docker compose exec cpp-dev bash
```


### 2. Compilação e Execução (Make)

**Para Compilar:**

Build com CMake (Apertando F7) 

ou:

```Bash
make
```

Isso vai ler o Makefile, compilar apenas o que foi alterado e gerar o executável.

**Para Executar o Programa:**

Executa run.sh e acesse [text](http://localhost:8080/vnc.html)


### 3. Fluxo de Trabalho e Versionamento (Git)

Utilizamos um sistema de *branches* para garantir a estabilidade da ramificação principal (`main`). 

**Passo 1: Atualize seu repositório local**
Antes de começar a trabalhar, garanta que seu código está sincronizado com a versão mais recente do projeto:

```bash
git checkout main
git pull origin main
```


**Passo 2: Crie uma Branch para a nova função**
Sempre crie uma branch específica para o que você vai desenvolver. Use nomes claros e descritivos.

```bash
git checkout -b feature/nome-da-sua-funcao
```

**Passo 3: Faça suas alterações e prepare os Commits**
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


**Passo 4: Envie a Branch para o repositório remoto**
Agora, envie a sua nova branch com os commits para o GitHub:

```bash
git push origin feature/nome-da-sua-funcao
```

Se a branch já exixtir

```bash
git push --set-upstream origin feature/nome-da-sua-funcao
```

**Passo 5: Crie o Pull Request (PR)**
1. Acesse a página do repositório no GitHub.
2. Você verá um aviso amarelo sugerindo criar um PR para a sua branch recém-enviada. Clique em **Compare & pull request**.
3. **Título:** Dê um título claro e resumido.
4. **Descrição:** Explique o que foi alterado. Se a sua branch resolve um problema específico, mencione qual é.
5. Clique em **Create pull request**.



