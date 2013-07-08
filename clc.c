#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

int main(int argc, char *argv[]) {
	WINDOW * mainwin;

	// initialize ncurses
	if((mainwin = initscr()) == NULL) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}

	mvaddstr(13, 33, "Hello, world!");
	refresh();
	sleep(3);

	/*	Clean up after ourselves  */

	delwin(mainwin);
	endwin();
	refresh();

	return EXIT_SUCCESS;
}
