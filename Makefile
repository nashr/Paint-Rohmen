CC = g++
CFLAGS = -m32 -std=c++11 -Wall -Iopenbgi

OBJS = main.o app.o canvas.o

rohmen: lib/libopenbgi.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o rohmen -O2 -Llib -lopenbgi -lgdi32

lib/libopenbgi.a:
	mingw32-make -C openbgi
	copy openbgi\openbgi.a lib\libopenbgi.a
	mingw32-make -C openbgi clean

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	del /s *.exe *.o