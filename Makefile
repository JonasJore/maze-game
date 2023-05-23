CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS = -lncurses

TARGET = target
SRCDIR = src
HEADERDIR = headers
BUILDDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
    @mkdir -p $(BUILDDIR)
    $(CC) $(CFLAGS) -I $(HEADERDIR) -c $< -o $@

clean:
    rm -rf $(BUILDDIR) $(TARGET)

run:
    ./target