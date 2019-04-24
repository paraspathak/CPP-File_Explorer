CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: fileexplorer

test: CXXGLAGS += -g
test: test_product test_product_order test_order test_store

debug: CXXFLAGS += -g
debug: all

data.o: data.cpp *.h
	$(CXX) $(CXXFLAGS) -c data.cpp $(GTKFLAGS)

dialogs.o: dialogs.cpp *.h
	$(CXX) $(CXXFLAGS) -c dialogs.cpp $(GTKFLAGS)

main_window.o: main_window.cpp *.h
	$(CXX) $(CXXFLAGS) -c main_window.cpp $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

file.o: file.cpp *.h
	$(CXX) $(CXXFLAGS) -c file.cpp $(GTKFLAGS)

folder.o: folder.cpp *.h
	$(CXX) $(CXXFLAGS) -c folder.cpp $(GTKFLAGS)

fileexplorer: data.o folder.o file.o dialogs.o main_window.o main.o *.h 
	$(CXX) $(CXXFLAGS) -o fileexplorer data.o file.o folder.o dialogs.o main_window.o main.o $(GTKFLAGS)

clean:
	-rm -f *.gch *.o *~a.out ./fileexplorer ./a.out

rebuild: clean all
