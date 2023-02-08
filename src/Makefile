BD = ../build/
APP = $(BD)Maze.app

all: install

build: copy_pro
	cd $(BD); qmake Maze.pro
	make -C $(BD)

copy_pro: 
	mkdir ../build/
	cp Maze/Maze.pro $(BD)
	cp Maze/* $(BD)

install: clean build
	@rm -rf $(HOME)/Desktop/Maze/
	mkdir $(HOME)/Desktop/Maze/
	cp -rf $(APP) $(HOME)/Desktop/Maze/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/Maze/

dvi: 
	open documentation.html

dist: install
	@rm -rf $(HOME)/Desktop/Archive_Maze.tar.gz
	cp -r $(HOME)/Desktop/Maze/Maze.app .
	@tar -czvf Archive_Maze.tar.gz documentation.html ./examples Maze.app
	mv Archive_Maze.tar.gz $(HOME)/Desktop/
	make clean

tests: clean
	g++ test.cc ./Maze/cave.cc ./maze_for_tests.cc ./Maze/matrix.cc -o tests -lgtest -std=c++17
	./tests

check: tests
	cp -f ../materials/linters/.clang-format Maze/.clang-format
	clang-format -i Maze/*.cc Maze/*.h
	clang-format -n Maze/*.cc Maze/*.cpp Maze/*.h
	cppcheck --language=c++ --enable=all --suppressions-list=suppresionlist.cfg Maze/*.cpp Maze/*.cc Maze/*.h
	rm -rf Maze/.clang-format
	CK_FORK=no leaks --atExit -- ./tests

gcov_report: clean
	g++ --coverage test.cc ./maze_for_tests.cc ./Maze/cave.cc ./Maze/matrix.cc -o tests -lgtest -std=c++17
	./tests
	lcov -t "test" --no-external -o tests.info -c -d ./
	genhtml -o report tests.info
	open ./report/index.html

clean:
	rm -rf *.gcda *.gcno *.info ./tests
	rm -rf ./report rm -rf ./Maze.app
	rm -rf ../build/
