Command Line (graphing) Calculator
==================================

clc takes a Lua expression and graphs its output in the terminal using ncurses. I often want machine help visualizing a bit of math, but don't want to wait tens of seconds to fire up a heavy-weight tool like Matlab or Processing. This utility is instant but basic.

	bin/clc 0 1 0 1 "2*math.sin(x)+3"

		xx    xxx    xx    xx    xx     xx    xx    xx    xxx    xx    xx    xx     xx    xx
		  x         x     x  x     x   x     x        x         x     x  x     x   x     x
	x  x     x   x     x        x         x     x  x     x   x     x        x         x     x
	 xx    xx     xx    xx    xx    xxx    xx    xx    xx     xx    xx    xx    xxx    xx    xx

Credits
-------
[SO user RBerteig](http://stackoverflow.com/users/68204/rberteig) [for great example code](http://stackoverflow.com/a/1152648) to evaluate Lua expressions.
