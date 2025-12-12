.SUFFIXES:
.PHONY: all clean run info

CXX := g++
CXXFLAGS := -std=c++17 -I include
LDFLAGS := -L lib -lsfml-graphics -lsfml-window -lsfml-system
TARGET := bin/FuegoYAgua.exe
SOURCES := src/main.cpp src/Menu.cpp src/LevelSelector.cpp src/PauseMenu.cpp src/WinMenu.cpp src/Level.cpp src/game.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	@echo ""
	@echo "========================================"
	@echo "  Compilando Fuego y Agua..."
	@echo "========================================"
	@echo ""
	@mkdir -p bin
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@echo ""
	@echo "========================================"
	@echo "  Compilacion exitosa!"
	@echo "  Ejecuta: make run"
	@echo "========================================"
	@echo ""

clean:
	@echo "Limpiando archivos..."
	@rm -f $(TARGET) 2>/dev/null || true
	@echo "Limpieza completada"

run: $(TARGET)
	@echo ""
	@echo "========================================"
	@echo "  Ejecutando Fuego y Agua..."
	@echo "========================================"
	@echo ""
	@.\$(TARGET)

info:
	@echo "========================================"
	@echo "  Informacion del proyecto"
	@echo "========================================"
	@echo "Archivos a compilar:"
	@echo "  - src/main.cpp"
	@echo "  - src/Menu.cpp"
	@echo "  - src/LevelSelector.cpp"
	@echo "  - src/PauseMenu.cpp"
	@echo "  - src/WinMenu.cpp"
	@echo "  - src/Level.cpp"
	@echo "  - src/game.cpp"
	@echo ""
	@echo "Compilador: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Librerias: $(LDFLAGS)"
	@echo ""
