//plik główny programu ANIMACJI ASCII Jakub Szymański E102 300387
//kompilacja gcc -Wall -o grafika main.c boisko.c ruch.c -lm -lncurses
// ./grafika
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<math.h>  //dołączenie standardowych bibliotek potrzebnych do działania programu oraz ncurses

#include"boisko.h" //dołączenie pliku nagłówkowego "boisko.h" w którym znajdują się funkcje do wyrysowania boiska
#include"ruch.h" //dołączenie pliku nagłówkowego "ruch.h" w którym znajdują się funckje ruchu animacji

#define A 9 //stała do równania parametrycznego y = A*sqrt(x);

int main(void)
{	
	printf("\e[?25l");	//wyłączenie kursora

	initscr(); //rozpoczecie pracy ncurses
	raw();
	noecho(); 

	int wysokosc = 0; //zmienna potrzebna do wypisywania komunikatów w win2
	int x, y; //parametry okna otwartego 
	int height, width, start1_y, start1_x, start2_x, start2_y; //parametry okien win1 i win2

 	getmaxyx(stdscr, y, x);
 	clear();
 	
	height  = y;
	width = x/2;
	start1_x = start1_y = 0; //win1 zaczyna się w punkcie 0, 0
	start2_x = x/2;
	start2_y = 0; //win2 zaczyna się w punkcie x/2, 0

	WINDOW * win1= newwin(height, width, start1_y, start1_x);
	WINDOW * win2= newwin(height, width, start2_y, start2_x); //inicjalizacja okien

	refresh();
 	box(win1, 0, 0);
 	box(win2, 0, 0); //wyrysowanie ram win1 i win2

 	wrefresh(win1);
 	wrefresh(win2); //odświezenie win1 i win2

 	boisko(&wysokosc, height, width, win1, win2); //wyrysowanie boiska i zawodnika
 	
 	wrefresh(win1);
 	wrefresh(win2);
 	getch(); //odswiezenie i oczekiwanie na start 

 	drybling(&wysokosc, height, width, start1_x, start1_y, win1, win2); //dryblowanie zawodnika

 	powrot(&wysokosc, height, width, start1_x, start1_y, win1, win2);//powrot do pozycji rzutowej zawodnika

 	rzut(&wysokosc, height, width, start1_x, start1_y, win1, win2);//rzut zawodnika

 	punkt(&wysokosc, height, width, start1_x, start1_y, win1, win2); //komunikat o trafieniu 

	wrefresh(win1);
	wrefresh(win2);
	refresh(); //odświeżenie okien
	getch();
	getch();
	endwin();//zakończenie pracy okien ncurses

	return 0; //koniec programu
}	