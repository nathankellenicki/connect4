# g++ main.cpp src/C4CmdLine.cpp src/Connect4.cpp -I include/ -o connect4

CC := g++

SRCDIR := app/src
BUILDDIR := build
TARGETDIR := bin

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -g -pthread
LIBPATHS := -Llib/libuv/build/Release
LIB := -luv
INC := -Iinclude -Ilib/libuv/include

all: connect4 connect4_server

connect4: $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	$(CC) app/connect4.cpp $^ -o $(TARGETDIR)/connect4 $(INC) $(LIBPATHS) $(LIB)

connect4_server: $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	$(CC) app/connect4_server.cpp $^ -o $(TARGETDIR)/connect4_server $(INC) $(LIBPATHS) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGETDIR)
