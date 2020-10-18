export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS= main.o maxrepeat.o lcp.o
MAIN=tesis

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS)  
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.cpp %.h 
lcp.o: lcp.cpp lcp.h
maxrepeat.o: maxrepeat.cpp lcp.h
main.o : maxrepeat.h lcp.h

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all