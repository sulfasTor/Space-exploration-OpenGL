#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 04/02/2018
# définition des commandes utilisées
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
# CFLAGS = -Wall -O3
CFLAGS = -g -O3
CPPFLAGS = -I.
LDFLAGS = -lm
# définition des fichiers et dossiers
PROGNAME = game
VERSION = 1.0
distdir = $(PROGNAME)-$(VERSION)
HEADERS = 
SOURCES = $(wildcard src/*.c)
OBJ = $(SOURCES:.c=.o)
DOXYFILE = documentation/Doxyfile
EXTRAFILES = COPYING  
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(DOXYFILE) $(EXTRAFILES)
# Traitements automatiques pour ajout de chemins et options (ne pas modifier)
ifneq (,$(shell ls -d /usr/local/include 2>/dev/null | tail -n 1))
	CPPFLAGS += -I/usr/local/include
endif
ifneq (,$(shell ls -d $(HOME)/local/include 2>/dev/null | tail -n 1))
	CPPFLAGS += -I$(HOME)/local/include
endif
ifneq (,$(shell ls -d /usr/local/lib 2>/dev/null | tail -n 1))
	LDFLAGS += -L/usr/local/lib
endif
ifneq (,$(shell ls -d $(HOME)/local/lib 2>/dev/null | tail -n 1))
	LDFLAGS += -L$(HOME)/local/lib
endif
ifeq ($(shell uname),Darwin)
	MACOSX_DEPLOYMENT_TARGET = 10.8
        CFLAGS += -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
        LDFLAGS += -framework OpenGL -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
else
        LDFLAGS += -lGL
endif
CPPFLAGS += $(shell sdl2-config --cflags)
LDFLAGS  += -lGL4Dummies $(shell sdl2-config --libs)
all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
	@@printf "\e[33mLinking\e[90m %s\e[0m\n" $@
	@@printf "\e[34mDone!\e[0m\n"
%.o: %.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@@@printf "\e[36mCompile\e[90m %s\e[0m\n" $@
dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)
distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
doc: $(DOXYFILE)
	cat $< | sed -e "s/PROJECT_NAME *=.*/PROJECT_NAME = $(PROGNAME)/" | \
	  sed -e "s/PROJECT_NUMBER *=.*/PROJECT_NUMBER = $(VERSION)/" >> $<.new
	mv -f $<.new $<
	cd documentation && doxygen && cd ..
clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz gmon.out core.* \
	  documentation/*~ shaders/*~ documentation/html
	@@printf "\e[34mCleaning...\e[0m\n"

re: clean all
