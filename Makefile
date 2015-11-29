
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

GTKMM_CFLAGS = $(shell pkg-config --cflags gtkmm-3.0)
GTKMM_LIBS   = $(shell pkg-config --libs gtkmm-3.0)

INCLUDES=\
	$(GTKMM_CFLAGS) \
	-I./src

OBJS = \
    .obj/hello_world.o

all: \
     compileStats \
     .obj \
     bin \
     $(OBJS) \
     bin/hello_world_test \
     bin/imgAPO_GUI

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
.obj/hello_world.o: hello_world.cpp hello_world.h
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

# compile bin objs 
.obj/hello_world_test.o: hello_world_test.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

.obj/imgAPO_GUI.o: imgAPO_GUI.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

# link bins
bin/hello_world_test: .obj/hello_world_test.o
	$(LD) -o $@ .obj/hello_world_test.o $(OBJS) $(LDFLAGS) $(GTKMM_LIBS)

bin/imgAPO_GUI: .obj/imgAPO_GUI.o
	$(LD) -o $@ .obj/imgAPO_GUI.o $(OBJS) $(LDFLAGS) $(GTKMM_LIBS)

.obj:
	$(MKDIR) .obj
bin:
	$(MKDIR) bin
