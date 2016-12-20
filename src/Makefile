GXX = gcc
#GCC_FLAGS = -g -O2 -Wreorder -D_DEBUG
GCC_FLAGS = -g -O2 -Wreorder -DDEBUG -std=c++11 -fpermissive
SUFFIX = c cpp cc cxx

BINDIR = bin
TARGET = $(BINDIR)/bloomfilter
SRCS = $(wildcard *.cpp ./murmurhash/*.cpp *.c)
OBJDIR = objs
#DIR = $(notdir $(SRCS))
DIR = ${SRCS}
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(DIR))

#INC = -I ./ -I /usr/include/glib-1.2/ -I/usr/lib64/glib/include/
#LIB = -lm -lstdc++ -L/usr/lib64 -lglib

INC = -I ./ -I ./murmurhash/include/
LIB = -lm -lstdc++

all: $(TARGET)

$(OBJDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(GXX) $(GCC_FLAGS) $(INC) -c $< -o $@

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(GXX) $(GCC_FLAGS) $(OBJS) -o $@ $(LIB)

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)
