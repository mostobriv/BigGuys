CXXHEADERS = -std=c++1y -O0


all: main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

MR: MR_main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

karacuba: karacuba_main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

rabin: miller_rabin_main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

power: power_main.cpp
	${CXX} -g $^ -o main $(CXXHEADERS)

clean:
	rm *.o main
