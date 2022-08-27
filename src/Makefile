all: check

test: clean
	g++ tests.cpp -o test -lgtest -std=c++17
	./test

gcov_report: clean
	g++ --coverage tests.cpp -o test -lgtest -std=c++17
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check: test
	cp -f ../linters/CPPLINT.cfg CPPLINT.cfg	
	python3 ../linters/cpplint.py --extensions=cpp *.cpp *.h tests/*.cpp
	cppcheck --enable=all --suppress=unmatchedSuppression --suppress=missingIncludeSystem --suppress=knownConditionTrueFalse --language=c++ --std=c++17 *.cpp *.h tests/*.cpp
	rm -rf CPPLINT.cfg
	leaks -atExit -- ./test
	
clean: 
	# rm -rf *.o && 	rm -rf *.a 
	rm -rf *.gcno && rm -rf *.gcda
	rm -rf *.info && rm -rf ./test 
	rm -rf ./report
	