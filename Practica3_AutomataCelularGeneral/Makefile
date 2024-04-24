CXX := g++
CXXFLAGS := -std=c++23
LDFLAGS := -lstdc++

SRCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.cc) $(wildcard $(SRCDIR)/border_types/*.cc)
OBJ := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))
BIN := automata_celular

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	@echo "Enlazando $^ --> $@"
	@$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo "Compilando $< --> $@"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Limpiando..."
	@rm -rf $(OBJDIR) $(BIN)

run_file:
	./automata_celular -init data/lattice.txt
