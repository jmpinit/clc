#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#include "le.h"

int main(int argc, char *argv[]) {
	int cookie;
	int i;
	char *msg = NULL;

	if (!le_init()) {
		printf("can't init LE\n");
		return 1;
	}
	if (argc<2) {
		printf("Usage: t-le \"expression\"\n");
		return 1;
	}
	cookie = le_loadexpr(argv[1], &msg);
	if (msg) {
		printf("can't load: %s\n", msg);
		free(msg);
		return 1;
	}
	printf("  x    %s\n"
			"------ --------\n", argv[1]);
	for (i=0; i<11; ++i) {
		double x = i/10.;
		double y;

		le_setvar("x",x);
		y = le_eval(cookie, &msg);
		if (msg) {
			printf("can't eval: %s\n", msg);
			free(msg);
			return 1;
		}
		printf("%6.2f %.3f\n", x,y);
	}

/*
	WINDOW * mainwin;

	// initialize ncurses
	if((mainwin = initscr()) == NULL) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}

	mvaddstr(13, 33, "Hello, world!");
	refresh();
	sleep(3);

	delwin(mainwin);
	endwin();
	refresh();
*/

	return EXIT_SUCCESS;
}
