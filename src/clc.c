#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "le.h"

enum { PROG, XMIN, XMAX, YMIN, YMAX, EXP } ARGS;

char *msg = NULL;

int con_width, con_height;
int pic_width, pic_height;

int8_t* picture;

int blockstart = 0x2580;	// where the block characters start
int32_t lookup[] = { 32, 0x2598, 0x259D, 0x2580, 0x2596, 0x258C, 0x259E, 0x259B, 0x2597, 0x259A, 0x2590, 0x259C, 0x2584, 0x2599, 0x259F, 0x2588 };

void cleanup() {
	free(msg);
}

void printb(int8_t block) {
	if(!(block <= 0xF)) {
		printf("invalid block #%d", block);
		exit(1);
	}

	if(block == 0) {
		printf(" ");
	} else {
		int i = 0xE29680 + lookup[block] - blockstart; //TODO lookup right block pattern
		int32_t b1 = (i>>16) | 0xFFFFFF00;
		int32_t b2 = (i>>8) | 0xFFFFFF00;
		int32_t b3 = i | 0xFFFFFF00;
		printf("%c%c%c", b1, b2, b3);
	}
}

void point(int x, int y) {
	if(x >= 0 && y >= 0 && x < pic_width && y < pic_height) {
		int cellx = x/2;
		int celly = y/2;

		int offx = x%2;
		int offy = y%2;

		int8_t block;
		if(offx == 0 && offy == 0) {
			block = 0x1;
		} else if(offx == 1 && offy == 0) {
			block = 0x2;
		} else if(offx == 0 && offy == 1) {
			block = 0x4;
		} else {
			block = 0x8;
		}

		picture[celly*pic_width/2+cellx] |= block;
	} else {
		//printf("point(%d, %d) out of bounds.\n", x, y);
	}
}

void render() {
	for(int y=0; y<pic_height/2; y++) {
		for(int x=0; x<pic_width/2; x++) {
			printb(picture[y*pic_width/2+x]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int cookie;
	
	double xmin, xmax;
	double ymin, ymax;

	// error checks

	if(!le_init()) {
		printf("can't init LE\n");
		exit(1);
	}

	if(argc != EXP + 1) {
		printf("Usage: clc xmin xmax ymin ymax \"expression\"\n");
		exit(1);
	}

	xmin = atof(argv[XMIN]);
	xmax = atof(argv[XMAX]);
	ymin = atof(argv[YMIN]);
	ymax = atof(argv[YMAX]);

	if(xmin >= xmax || ymin >= ymax) {
		printf("max must be greater than min\n");
		exit(1);
	}

	cookie = le_loadexpr(argv[EXP], &msg);
	if(msg) {
		printf("can't load: %s\n", msg);
		exit(1);
	}

	// initialization
	atexit(cleanup);

	// info
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	con_height = 8;
	con_width = w.ws_col;

	pic_width = con_width*2;
	pic_height = con_height*2;

	// draw memory
	picture = calloc(pic_width*pic_height/4, sizeof(int8_t));
	for(int i=0; i<pic_width*pic_height/4; i++) picture[i] = 0;

	double xrange = xmax - xmin;
	double yrange = ymax - ymin;
	
	double xscale = xrange / pic_width;		// px per unit
	double yscale = yrange / pic_height; 	// px per unit

	for(int px = 0; px < pic_width; px++) {
		double x = xmin + px * xscale;
		le_setvar("x", x);

		double y = le_eval(cookie, &msg);
		int py = y / yscale;

		point(px, py);

		if (msg) {
			printf("can't eval: %s\n", msg);
			exit(1);
		}
	}

	render();

	return EXIT_SUCCESS;
}
