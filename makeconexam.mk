EXEC=smokers garden gardenLimited
LDFLAGS=-pthread
CPPFLAGS=-Wall

all: $(EXEC)

.phony: clean

smokers: smokers.o
	$(CXX) -o $@ $^ $(LDFLAGS)

smokers.o: smokers.cpp

garden: garden.o
	$(CXX) -o $@ $^ $(LDFLAGS)

garden.o: garden.cpp

gardenLimited: gardenLimited.o
	$(CXX) -o $@ $^ $(LDFLAGS)

gardenLimited.o: gardenLimited.cpp

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f *.*~

