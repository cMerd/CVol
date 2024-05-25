CXX := g++
CXXFLAGS := -Wall -lraylib -ljsoncpp -O3
SRCDIR := src
BUILDDIR := build

# List of source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names from source file names
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Default target for Linux
$(BUILDDIR)/cvol: $(OBJS)
	$(CXX) $(CXXFLAGS) -lm -lasound $^ -o $@

# Rule to compile each source file into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create a configuration directory and a default configuration file
configure:
	mkdir ~/.config/cvol/ -p
	cp ./conf/default_conf.json ~/.config/cvol/config.json

# Move the binary to path (/usr/bin)
install:
	sudo cp ./build/cvol /usr/bin/cvol
	sudo cp ./conf/cvol.desktop /usr/share/applications/cvol.desktop

# Remove the binary from path (/usr/bin)
uninstall:
	sudo rm -f /usr/bin/cvol

# Clean target to remove all files in build directory
clean:
	rm -f $(BUILDDIR)/*
