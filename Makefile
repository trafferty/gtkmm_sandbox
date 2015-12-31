
#commands
CC=gcc
CPP=g++
LD=g++
RM = /bin/rm -f
MKDIR=/bin/mkdir -p
CPDIR=/bin/cp -r
CPFILE=/bin/cp
AR=/usr/bin/ar

#Compiler flags
DFLAGS = -O3
CFLAGS = $(DFLAGS) -W -Wall -Wextra -fPIC -std=c++11

#Linker flags
LDFLAGS =-rdynamic -Wl,--export-dynamic,--no-as-needed

GTK_PKGS=gtk+-3.0 glib-2.0 gmodule-2.0 gmodule-export-2.0
GTK_CFLAGS=-g3 `pkg-config --cflags $(GTK_PKGS)`
GTK_LDLIBS=`pkg-config --libs $(GTK_PKGS)`

GTKMM_CFLAGS = $(shell pkg-config --cflags gtkmm-3.0)
GTKMM_LIBS   = $(shell pkg-config --libs gtkmm-3.0)

INCLUDES=\
	$(GTKMM_CFLAGS) \
	-I./src

OBJS = \
    .obj/imgAPO_GUI.o \
	 .obj/gtk_utils.o \
	 .obj/callbacks.o

all: \
     compileStats \
     .obj \
     bin \
     $(OBJS) \
     bin/imgAPO_test

debug: DFLAGS = -ggdb -g3 -DDEBUG
debug: all

clean:
	$(RM) compileStats.h
	$(RM) -r .obj
	$(RM) -r bin

compileStats:
	echo "extern \"C\" {" > compileStats.h;
	git rev-parse HEAD | awk '{print "  const char *compiled_git_sha = \"" $$0"\";"}' >> compileStats.h;
	(git symbolic-ref HEAD || echo "no branch") | sed 's/refs\/heads\///g' | awk '{print "  const char *compiled_git_branch = \"" $$0"\";"}'	 >> compileStats.h;
	echo "  const char *compiled_host = \"$$HOSTNAME\";" >> compileStats.h;
	echo "  const char *compiled_user = \"$$USER\";" >> compileStats.h;
	date +"%a %b %d %T %Z %Y" |  awk '{print "  const char *compiled_date = \"" $$0"\";"}' >> compileStats.h;
	uname -a |  awk '{print "  const char *compiled_note = \"" $$0"\";"}' >> compileStats.h;
	echo "}" >> compileStats.h

# compile objs
.obj/imgAPO_GUI.o: imgAPO_GUI.cpp imgAPO_GUI.h
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

.obj/gtk_utils.o: gtk_utils.c gtk_utils.h
	$(CPP) -c $< -o $@ $(CFLAGS) $(GTK_CFLAGS)

.obj/callbacks.o: callbacks.c
	$(CPP) -c $< -o $@ $(CFLAGS) $(GTK_CFLAGS)

# compile bin objs
.obj/imgAPO_test.o: imgAPO_test.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

.obj/imgAPO_test2.o: imgAPO_test2.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(GTK_CFLAGS)

# link bins
bin/imgAPO_test: .obj/imgAPO_test.o
	$(LD) -o $@ .obj/imgAPO_test.o $(OBJS) $(LDFLAGS) $(GTK_LDLIBS) $(GTKMM_LIBS) -lpthread

bin/imgAPO_test2: .obj/imgAPO_test2.o .obj/callbacks.o .obj/gtk_utils.o
	$(CPP) -o $@ $^ $(GTK_LDLIBS)


.obj:
	$(MKDIR) .obj
bin:
	$(MKDIR) bin
