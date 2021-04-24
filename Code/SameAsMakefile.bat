g++ -c ppm.cpp -o ppm.o -std=c++11
ar rcs libppm.a ppm.o
g++ -o filter.exe main.cpp libppm.a -std=c++11