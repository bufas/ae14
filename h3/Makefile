CC := clang++
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11
LIB := 
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET) bin/*

# Tests
tester: $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o build/tester.o test/tester.cpp
	$(CC) $(INC) build/tester.o $^ -o bin/test $(LIB)


# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean





# CC=clang++
# CFLAGS=-c -Wall -std=c++11
# LDFLAGS=
# EXECUTABLE=bin/test

# all: test
	
# test: build/full.o build/RSNaive.o
# 	$(CC) $(LDFLAGS) build/full.o -o $(EXECUTABLE)

# full.o: full.cpp
# 	$(CC) $(CFLAGS) full.cpp

# RSNaive.o: src/RSNaive.cpp

# clean: 
# 	rm -rf build/*