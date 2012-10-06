EXEC = bank bounded resall waitfor dldetect

all: bank bounded resall waitfor dldetect

bank : 
	g++ -o bank bank.cpp

bounded:
	g++ -o bounded bounded.c -lpthread

resall:
	g++ -o resall resall.cpp

waitfor:
	g++ -o waitfor waitfor.cpp

dldetect:
	g++ -o dldetect dldetect.cpp

clean:
	rm -rf $(EXEC) *.out

