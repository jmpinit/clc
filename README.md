Command Line (graphing) Calculator
==================================

clc takes a Lua expression and graphs its output in the terminal using ncurses. I often want machine help visualizing a bit of math, but don't want to wait tens of seconds to fire up a heavy-weight tool like Matlab or Processing. This utility is instant but basic.

	./bin/clc 0 6.28 0 2 "1+math.sin(x)"
																								 ▄▄▄▄▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▚▄▄▄▄▖                   
																						 ▗▄▄▄▀▀▀▀                                 ▝▀▀▀▚▄▄▄            
																				   ▄▄▄▀▀▀▘                                                ▀▀▀▚▄▄▖     
																			 ▗▄▄▀▀▀                                                             ▝▀▀▚▄▄
	▀▀▀▄▄▄                                                             ▗▄▄▞▀▀▘                                                                        
		  ▀▀▀▄▄▄▖                                                ▄▄▄▞▀▀▘                                                                              
				▝▀▀▀▄▄▄▄                                 ▗▄▄▄▞▀▀▀                                                                                     
						▀▀▀▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▞▀▀▀▀▘                                                                                            

Credits
-------

* _[SO user RBerteig](http://stackoverflow.com/users/68204/rberteig)_ [for great example code](http://stackoverflow.com/a/1152648) to evaluate Lua expressions.
