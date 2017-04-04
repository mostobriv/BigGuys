CXXHEADERS = -std=c++1y -O3

all: main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

clean:
	rm *.o main
