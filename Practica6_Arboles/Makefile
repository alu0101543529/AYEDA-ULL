CXX := g++
CXXFLAGS := -std=c++23
LDFLAGS := -lstdc++

SRCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.cc)
OBJ := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))
BIN := tree

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	@echo "Enlazando $^ --> $@"
	@$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo "Compilando $< --> $@"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Limpiando..."
	@rm -rf $(OBJDIR) $(BIN)