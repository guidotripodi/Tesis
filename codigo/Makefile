export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o
OBJS1 = suffix.o 
MAIN=tesis
SUFFIX = suffix
ENTRADA = entrada

.PHONY: all
all: $(MAIN) $(SUFFIX) $(ENTRADA)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(SUFFIX): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(ENTRADA): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tesis: main.o
suffix: suffix.o
entrada: entrada.o

main.o: main.cpp 
suffix.o: suffix.cpp
entrada.o: entrada.cpp

.PHONY: clean
clean:
	rm -f $(OBJS) $(MAIN) $(OBJS1) $(SUFFIX) $(ENTRADA) $(OBJS2)

.PHONY: new
new: clean all