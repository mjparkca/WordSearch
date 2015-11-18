TARGET = wordsearch

CC = gcc
LINKER = gcc -o

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET):	$(OBJECTS)
	@$(LINKER) $@ $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< -o $@

clean:
	rm -f $(BINDIR)/* $(OBJDIR)/*

new:
	make clean
	make
