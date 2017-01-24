SHELL = /bin/bash

## OPTIONS  ##
OPT     += -DSAVE_WVT_STEPS         # write IC file for every WVT step
#OPT     += -DSPH_CUBIC_SPLINE      # for use with Gadget2
OPT     += -DREJECTION_SAMPLING      # use von Neumann rejection sampling to improve initial random positions
OPT     += -DEAT_PNG                 # Eat density profile from a png file



ifndef SYSTYPE
    SYSTYPE := $(shell hostname)
endif

OPTIMIZE = -Wall -fast
GSL_INCL = $(CPPFLAGS)
GSL_LIBS = $(LD_LIBRARY_FLAGS)
PNG_LIBS = -L/usr/local/Cellar/libpng/1.6.21/lib -lpng -lz
PNG_INCL = -I/usr/local/Cellar/libpng/1.6.21/include


## TARGET ##

EXEC = WVTICs

## FILES ##

SRCDIR    = src/

SRCFILES := ${shell find $(SRCDIR) -name \*.c -print} # all .c files in SRCDIR
OBJFILES = $(SRCFILES:.c=.o)

INCLFILES := ${shell find src -name \*.h -print} # all .h files in SRCDIR
INCLFILES += Makefile

CFLAGS  = -std=c99 -fopenmp $(OPTIMIZE) $(OPT) $(GSL_INCL) $(PNG_INCL)

LINK    = $(GSL_LIBS) -lm -lgsl -lgslcblas $(PNG_LIBS)

## RULES ##

%.o : %.c
	@echo [CC] $@
	@$(CC) $(CFLAGS)  -o $@ -c $<

$(EXEC) : $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LINK) -o $(EXEC)
	@ctags -w $(SRCFILES) $(INCLFILES)

$(OBJFILES) : $(INCLFILES) $(SRCFILES)

clean : 
	rm $(OBJFILES) $(EXEC)
