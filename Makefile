# Nome do seu executável
TARGET = gerenciador_de_filmes

# Compilador e Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Encontra todos os .cpp da pasta
SRCS = $(wildcard *.cpp)

# Transforma a lista de .cpp em uma lista de .o
OBJS = $(SRCS:.cpp=.o)

# Regra principal: cria o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra genérica para compilar qualquer .cpp em um .o correspondente
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)