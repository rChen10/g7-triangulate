all: line pixel screen matrix polygon parser main my bin
	./bin/read_poly_script build/script

pixel: include/pixel.h
	g++ -c src/pixel.cpp -o build/pixel.o

line: include/line.h
	g++ -c src/line.cpp -o build/line.o

screen: include/screen.h
	g++ -c src/screen.cpp -o build/screen.o

matrix: include/matrix.h
	g++ -c src/matrix.cpp -o build/matrix.o

polygon: include/polygon.h
	g++ -c src/polygon.cpp -o build/polygon.o

parser: include/parser.h
	g++ -c src/parser.cpp -o build/parser.o

main: include/parser.h
	g++ -c src/main.cpp -o build/main.o

my: include/my.h
	g++ -c src/my.cpp -o build/my.o

bin: build/pixel.o build/line.o build/screen.o build/matrix.o build/polygon.o build/parser.o build/main.o build/my.o
	g++ build/*.o -o bin/read_poly_script

run:
	./bin/read_poly_script build/script

clean:
	rm build/*.o -r
	rm bin/* -r

