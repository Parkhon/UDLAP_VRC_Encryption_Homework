OBJS = easy_bit_object_exe
CC = g++
CFLAGS = -x c -Wall -std=c++11 -x c++ -I headers -I source_files

all: easy_bit_object_exe

easy_bit_object_exe:
	$(CC) $(CFLAGS) ./source_files/main.cpp ./source_files/EBObj.cpp ./source_files/arc4KSA.cpp ./source_files/arc4PRGA.cpp ./source_files/Vignere.cpp -o ../binaries/EBObj_demo

clean:
	rm -rf ../binaries/$(OBJS)
