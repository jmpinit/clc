#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#include "le.h"

WINDOW * mainwin;
char *msg = NULL;

void cleanup() {
	free(msg);

	// ncurses
	delwin(mainwin);
	endwin();
	refresh();
}

int main(int argc, char *argv[]) {
	int cookie;
	
	double xmin, xmax;

	// error checks

	if(!le_init()) {
		printf("can't init LE\n");
		exit(1);
	}

	if(argc != 4) {
		printf("Usage: clc xmin xmax \"expression\"\n");
		exit(1);
	}

	xmin = atof(argv[1]);
	xmax = atof(argv[2]);
	
	if(xmin >= xmax) {
		printf("xmax must be greater than xmin\n");
		exit(1);
	}

	cookie = le_loadexpr(argv[3], &msg);
	if(msg) {
		printf("can't load: %s\n", msg);
		exit(1);
	}

	// initialization
	atexit(cleanup);

	// ncurses
	if((mainwin = initscr()) == NULL) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}

	int width, height;
	getmaxyx(mainwin, height, width);
	for(int col = 0; col < width; col++) {
		le_setvar("x", col);

		int y = le_eval(cookie, &msg);

		mvaddch(y, col, 'x');

		if (msg) {
			printf("can't eval: %s\n", msg);
			exit(1);
		}
	}

	refresh();
	sleep(3);

	return EXIT_SUCCESS;
}
