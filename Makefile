
#C compiler. Uses system's default compiler. You can change this to a specific compiler if you want.
CC = cc

#Compilation flags.
CFLAGS ?= -Wall -std=gnu11 -O3 -fopenmp

#Include flags.
IFLAGS = 

#Libraries
LFLAGS = 

#Executable name
EXEC = ttt

#Directory structure
SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/
DOCDIR = docs/

#Source files. Matches all .c files in the src directory.
SOURCES = $(notdir $(wildcard $(SRCDIR)*.c))
#uncomment the bottom for files in a directory in src
#SOURCES += $(subst $(SRCDIR),,$(wildcard $(SRCDIR)*/*.c))

#Object file conversion.
OBJECTS = $(SOURCES:.c=.o)

#Object files in the obj directory.
DOBJS = $(addprefix $(OBJDIR),$(OBJECTS))

#Executable in binaries directory
DEXEC = $(addprefix $(BINDIR),$(EXEC))

#The default task. Depends on the executable.
default: $(DEXEC) docs

#Job for the executable. Depends on the object files.
$(DEXEC): $(DOBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(DOBJS) -o $(DEXEC)

#Compilation of the .c files in the src directory to the corresponding .o files in the obj directory.
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: clean cleanexe cleanobj cleandocs

#Remove all compiled files
clean: cleanexe cleandocs

#Remove all object files.
cleanobj:
	@rm -f $(DOBJS)

#Remove all object files and the executable.
cleanexe: cleanobj
	@rm $(DEXEC)

#LaTeX parts

TEXSRC = $(wildcard $(DOCDIR)*.tex)

TEXPDF = $(TEXSRC:.tex=.pdf)

#DDOC = $(addprefix $(DOCDIR),$(TEXPDF))

#$(DOCDIR)%.pdf: $(DOCDIR)%.tex
#	pdflatex -output-directory=$(DOCDIR) $<

%.pdf: %.tex
	@pdflatex -output-directory=$(DOCDIR) $<

docs: $(TEXPDF)

cleandocs:
	@rm $(DOCDIR)*.aux
	@rm $(DOCDIR)*.log
	@rm $(TEXPDF)
