# Makefile for Imageops program

CC = g++
CCFLAGS = -std=c++11

driver: driver.o imageops.o imageops.h
	$(CC) $(CCFLAGS) driver.o imageops.o -o imageops
	
driver.o: driver.cpp imageops.h
	$(CC) $(CCFLAGS) driver.cpp -c

imageops.o: imageops.cpp imageops.h
	$(CC) $(CCFLAGS) imageops.cpp -c

clean:
	rm *.o