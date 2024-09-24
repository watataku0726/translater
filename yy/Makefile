all : target

target : 
	@bison -ra -o parser.cc parser.y
	@flex -o scanner.cc scanner.l
	@mv *.hh ../include/
	@mv *.cc ../src/

clean :
	@rm  *.output ../src/parser.cc ../src/scanner.cc ../include/location.hh ../include/parser.hh ../include/position.hh ../include/stack.hh