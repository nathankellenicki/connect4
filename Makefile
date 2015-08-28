# g++ main.cpp src/C4CmdLine.cpp src/Connect4.cpp -I include/ -o connect4

CC := g++

SRCDIR := src
BUILDDIR := build
TARGET := bin/connect4

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -g
LIB := -pthread -L lib
INC := -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) main.cpp $^ -o $(TARGET) $(INC) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)
