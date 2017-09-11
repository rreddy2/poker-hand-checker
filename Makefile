all : poker

poker: poker.c
	gcc poker.c -o poker.exe

clean:
	rm -f poker.exe
