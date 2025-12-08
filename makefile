# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin
GPP := C:\msys64\mingw64\bin\g++.exe

SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generar los nombres de los archivos .exe en el directorio de destino
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(CPP_FILES))

# Regla para compilar cada archivo .cpp y generar el archivo .exe correspondiente
$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	$(GPP) $< -o $@ $(SFML) -Iinclude

# Regla por defecto para compilar todos los archivos .cpp
all: $(EXE_FILES)

# Reglas específicas para ejecutar programas
run00_Ventana: $(BIN_DIR)/00_Ventana.exe
	start $(BIN_DIR)/00_Ventana.exe

run01_Imagen: $(BIN_DIR)/01_Imagen.exe
	$(BIN_DIR)/01_Imagen.exe

run02_Sprite: $(BIN_DIR)/02_Sprite.exe
	$(BIN_DIR)/02_Sprite.exe

run03_0_Teclado: $(BIN_DIR)/03_0_Teclado.exe
	$(BIN_DIR)/03_0_Teclado.exe

run03_1_Pikachu: $(BIN_DIR)/03_1_Pikachu.exe
	$(BIN_DIR)/03_1_Pikachu.exe

run04_Texto: $(BIN_DIR)/04_Texto.exe
	$(BIN_DIR)/04_Texto.exe

run05_Audio: $(BIN_DIR)/05_Audio.exe
	$(BIN_DIR)/05_Audio.exe

run06_Primitivas: $(BIN_DIR)/06_Primitivas.exe
	$(BIN_DIR)/06_Primitivas.exe

run07_Fisica: $(BIN_DIR)/07_Fisica.exe
	$(BIN_DIR)/07_Fisica.exe

run08_Tron: $(BIN_DIR)/08_Tron.exe
	$(BIN_DIR)/08_Tron.exe

# Regla para limpiar los archivos generados
clean:
	rm -f $(EXE_FILES)

.PHONY: all clean run00_Ventana run01_Imagen run02_Sprite run03_0_Teclado run03_1_Pikachu run04_Texto run05_Audio run06_Primitivas run07_Fisica run08_Tron
