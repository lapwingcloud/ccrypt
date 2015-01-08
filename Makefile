CXX = g++
CXXFLAGS = -Wall -O2 -fopenmp -Iinclude
OBJS = build/AES.o build/Base64.o

libccrypt.a: $(OBJS)
	ar -cvq $@ $(OBJS)

test: src/main.cpp
	$(CXX) -Iinclude -L. -s -o test $? -lccrypt -lgomp

build/AES.o: src/AES.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/Base64.o: src/Base64.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

clean:
	rm -rf build/*.o test libccrypt.a

