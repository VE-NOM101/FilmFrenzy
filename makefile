FilmFrenzy : program
program : main.o loginsys.o review.o
	g++ main.o loginsys.o review.o -o filmfrenzy
main.o: main.cpp
	g++ -c main.cpp -o main.o
loginsys.o: loginsys.cpp
	g++ -c loginsys.cpp -o loginsys.o
review.o: review.cpp
	g++ -c review.cpp -o review.o
clear:
	rm *.o filmfrenzy