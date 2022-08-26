FLAGS= -c -Wall -ansi -pedantic -g

./src = command.c die_test.c die.c game_loop.c game_reader.c game.c game_test.c graphic_engine.c inventory.c inventory_test.c link_test.c link.c object.c object_test.c player.c screen.c set.c space.c space_test.c

./include = command.h die.h game_reader.h game.h graphic_engine.h inventory.h link.h object.h player.h screen.h set.h space.h types.h

./obj = command.o game.o graphic_engine.o space.o screen.o game_loop.o game_reader.o object.o player.o set.o die.o inventory.o link.o

./test = inventory_test die_test link_test game_test object_test space_test

./testo = die_test.o game_test.o inventory_test.o link_test.o object_test.o space_test.o

./doc = Doxyfile Doxyfile.back 

all: compile goose $(./test)

compile: $(./include) $(./src)
	gcc $(FLAGS) $(./src)

goose: $(./obj) $(./include)
	gcc $(./obj) -o goose

doxygen:
	doxygen -g
	doxygen Doxyfile

die_test: die_test.o die.o
	gcc die.o die_test.o -o die_test

link_test: link_test.o link.o space.o set.o types.h
	gcc set.o object.o space.o link.o link_test.o -o link_test

space_test: space_test.o
	gcc space_test.o space.o link.o set.o object.o -o space_test

object_test: object_test.o
	gcc object_test.o object.o -o object_test

inventory_test: inventory_test.o
	gcc inventory_test.o inventory.o set.o object.o -o inventory_test

game_test: game_test.o
	gcc game_test.o game.o player.o object.o link.o space.o inventory.o set.o die.o game_reader.o command.o graphic_engine.o screen.o -o game_test

clean:
	rm -f *$(./obj)
	rm -f $(./testo)
	rm -f $(./doc) 
	rm -f goose
	rm -f $(./test)