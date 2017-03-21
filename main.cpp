#include "Game.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include "Functions.h"

using namespace std;

/**
Allora tutte le stringhe che vengono stampate
devono essere stampate con la funzione print(WINDOW*, string). Il programma ora fa
più ampio uso della libreria Ncurses.h che facilita e migliora l'output a video dei
messaggi, nel mentre sto pensando a una funzione che sostituisca il cin e permetta
di acquisire dati dall'utente.

Per stampare le funzioni della libreria necessitano di un puntatore a finestra
che nel programma ho chiamato outwin, tale puntatore è presente nelle classi Game,
Player e Ship ma viene inizializzato solo nella classe Game; i puntatori delle altre
due classi sono poi uguagliati al primo.
**/

/**
Rimosso funzione askname() dalla classe game. Veniva usata una volta sola e dà qualche
problema per via che viene passato un char* etc etc ....

La funzione getch() acquisisce un carattere inserito dall'utente, ma scrivere '1' e 1 sono
due cose diverse. Ho fatto un po' di test e continuava a dirmi start point out-of-grid
questo perche '1'=49. così dobbiamo porre x-'A' per dire al programma che il char A è il punto
di zero delle x, dobbiamo anche però mettere y-'1' per dire che il char 1 è lo zero delle y.

Inserito parentesi doppie negli if che controllano le stringhe es: if((dir=="down")).
Non so perchè ma non sembra funzionare altrimenti.

Aggiunta funzione shipDeath() da chiamare a fine turno. controlla quale nave è morta nel turno
e segnala i giocatori del fatto.

Nelle funzioni acquire() ho messo delle stringhe fisse per far riconoscere al programma se
l'utente ha inserito una lettera maiscola, minuscola o un numero. Così facendo la funzione
acquire converte subito l'input da char a intero. Non è più necessario scrivere x-'A' nelle
funzioni successive.
**/

bool Game::AIactive=false;
bool Game::newgame=false;

WINDOW* title;
WINDOW* welcome;
WINDOW* attackg;
WINDOW* defenseg;
WINDOW* outwin;
WINDOW* closing;
WINDOW* turn;

int colours[] = { //vector containing colour codes
	-1,
	COLOR_BLACK,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_WHITE,
};

int main()
{
	if(!initscr()) {
		printf("Error initializing screen.\n");
	    return -1;
	}
	if(!has_colors()) {
		printf("This terminal does not support colours.\n");
		return -1;
	}

	//Setting up library colors and input
	start_color();
	use_default_colors();
	cbreak();
	echo();

	int col=getmaxx(stdscr);

	do
	{
		welcome=newwin(15,75,4,0);
		title=newwin(4,26,0,30);

		wmove(title,0,0);
		print(title,"--------------------------");
		print(title,"|  Battaglia navale !!!  |");
		print(title,"--------------------------");
		do
		{
			if(col<100)
			{
				wmove(welcome,0,0);
				print(welcome,"Nota: questo programma e' ottimizzato per la visualizzazione con terminale a schermo intero");
			}
			wmove(welcome,3,0);
			print(welcome,"Vuoi giocare contro una AI? [y/n]");
			int ai=wgetch(welcome);
			if(ai=='y'||ai=='Y'){Game::AIactive=true;wclear(welcome);break;}
			else if(ai=='n'||ai=='N'){Game::AIactive=false;wclear(welcome);break;}
			else{cReturn(welcome);print(welcome,"Comando non riconosciuto");mySleep(2.5);}
		}while(true);

		Game partita;

		partita.initNames();

		//clearing windows
		wclear(title);
		wclear(welcome);
		wrefresh(title);
		wrefresh(welcome);
		//setting up windows location and deleting old ones
		delwin(title);
		delwin(welcome);

		defenseg=newwin(12,23,2,2);
		attackg=newwin(12,23,2,30);
		outwin=newwin(20,60,2,60);
		turn=newwin(2,60,0,9);

		partita.initGame();

		partita.playGame();

	}while(Game::newgame);

	wclear(closing);
	wrefresh(closing);
	wmove(closing,4,0);
	print(closing,"The only winning move is not to play");
	wmove(closing,6,0);
	print(closing,"thank you for playing");
	mySleep(4);
	delwin(closing);

	endwin();

	return 0;
}

