OBJS = grammar.o \
		lexer.o \
		code_gen.o \
		main.o	\
		obj_gen.o \
		type.o \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++14
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic -L/usr/local/lib -ljsoncpp
LIBS = `$(LLVMCONFIG) --libs`

.PHONY: clean test

all: cless

%.o: %.cpp
	clang++ -c $(CPPFLAGS) -o $@ $<

cless: $(OBJS)
	clang++ $(CPPFLAGS) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

grammar.cpp: grammar.y
	bison -d -o grammar.cpp $<

grammar.hpp: grammar.cpp

lexer.cpp: lexer.l grammar.hpp
	flex -o $@ $<

test: cless test.input
	cat test.input | ./cless
	clang output.o -o test
	./test

clean:
	rm -rf cless grammar.cpp grammar.hpp lexer.cpp *.output ${OBJS} output.o