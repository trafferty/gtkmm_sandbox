
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
    .obj/imgAPO_GUI.o

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

# compile bin objs 
.obj/imgAPO_test.o: imgAPO_test.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES)

# link bins
bin/imgAPO_test: .obj/imgAPO_test.o
	$(LD) -o $@ .obj/imgAPO_test.o $(OBJS) $(LDFLAGS) $(GTKMM_LIBS) -lpthread 

.obj:
	$(MKDIR) .obj
bin:
	$(MKDIR) bin
