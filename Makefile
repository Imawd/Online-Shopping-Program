CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS= amazon.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o book.o movie.o clothing.o
TEST= test_file.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o book.o movie.o clothing.o
all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)
amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h  mydatastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
test_file: $(TEST)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(TEST)
test_file.o: test_file.cpp db_parser.h datastore.h product_parser.h  mydatastore.h product.h book.h movie.h clothing.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c test_file.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp product.h book.h movie.h clothing.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h book.h movie.h clothing.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h product.h user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp
book.o: book.cpp book.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
movie.o: movie.cpp movie.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp
clothing.o: clothing.cpp clothing.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp


clean:
	rm -f *.o amazon
