# Компилятор
CXX = clang++

# Опции компиляции
CXXFLAGS = -std=c++17 -Wall -I./general 

# Исходники и объекты
PERSONAL_CLIENT = personal/main_client.cpp personal/port_client.cpp
PERSONAL_SERVER = personal/main_server.cpp personal/port_server.cpp
OBJ_CLIENT = $(PERSONAL_CLIENT:.cpp=.o)
OBJ_SERVER = $(PERSONAL_SERVER:.cpp=.o)

# Конечные исполняемые файлы
TARGETS = client server

# Правило по умолчанию
all: $(TARGETS)

# Правила компиляции для клиента
client: $(OBJ_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правила компиляции для сервера
server: $(OBJ_SERVER)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Очистка
clean:
	rm -f client server $(OBJ_CLIENT) $(OBJ_SERVER)