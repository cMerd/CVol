CXX := g++
CXXFLAGS := -Wall -lraylib
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

# Clean target to remove all files in build directory
clean:
	rm -f $(BUILDDIR)/*
