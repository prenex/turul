# The target executable name
# with em++ it gets suffixed with ".html"
TARGET=main

# for gcc5.1+:
CC=g++
# for clang3.4+:
#CC=clang++
# for emscripten with JS target
#CC=em++

ifeq ($(CC),g++)
	# g++ (ver 5.1+ tested)
	CFLAGS=-c -std=c++14 -g #-Wall # sadly we are having a lot of unused functions for tests so this is undesirable...
	LDFLAGS=-lm -g # -lglut -lGLESv2 -g
else 
ifeq ($(CC),em++)
	# em++ (ver 1.3+ tested)
	# TODO: added debug symbols
	# use 1y instead of 14 here, we need the LLVM libc so that streams are copyable (or a more recent gcc toolchain than the 4.9 at my work!)
	CFLAGS=-c -stdlib=libc++ -std=c++1y -O2
	LDFLAGS=--shell-file shell_minimal.html --preload-file models -O2 -stdlib=libc++ # -lglut
else
	# clang++ (ver 3.4+ tested)
	# clang uses 1y instead of 14 here, we need the LLVM libc so that streams are copyable (or a more recent gcc toolchain than the 4.9 at my work!)
	CFLAGS=-c -stdlib=libc++ -std=c++1y -g -fsanitize=address -fno-omit-frame-pointer
	LDFLAGS=-lm -stdlib=libc++ -g -fsanitize=address -fsanitize-memory-track-origins #-lglut -lGLESv2 
endif
endif

# Directory of the make, currently the local
MK_DIR=.
# Directory of underlying source tree
SRC_DIR=components

# Non-recursive generic make from:
# --------------------------------
# 	http://abusalimov.blogspot.hu/2009/12/yet-another-implementation-of-non.html
all: $(TARGET)
include $(MK_DIR)/traverse.mk
# Clear and switch it to immediate expansion mode
# to be able to use += operator later.
OBJS_ALL:=
# This code is executed each time when per-directory makefile is processed.
define TRAVERSE_CALLBACK
	OBJS_ALL += $$(addprefix $(NODE_DIR)/,$(NODE_OBJS))
endef
# Walk the directory tree starting at $(SRC_DIR)
# and searching for node.mk in each subdirectory.
$(eval $(call TRAVERSE,$(SRC_DIR),node.mk,TRAVERSE_CALLBACK))

# DEBUG
#$(warning OBJS_ALL is $(OBJS_ALL))
#$(warning TARGET is $(TARGET))

# Process dependency files too. 
-include $(OBJS_ALL:.o=.d)
# Link all together! 
# The LDFLAGS should be after the files
# because of some lazyness in newer toolchains!
# in case of emscripten we produce html5/webgl outputs etc
$(TARGET): $(OBJS_ALL)
ifeq ($(CC),em++)
	@$(CC) -o $@.html $(OBJS_ALL) $(LDFLAGS)  #-T $(LDSCRIPT) 
else
	@$(CC) -o $@ $(OBJS_ALL) $(LDFLAGS)  #-T $(LDSCRIPT) 
endif

# Generic pattern-rule for building
# all *.o using *.cpp files using
# the below command template
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS_ALL)
	rm -f main
