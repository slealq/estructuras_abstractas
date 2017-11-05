OBJS = busqueda.o
CC = g++
DEBUG = -g
#CFLAGS =  -c                                                                   
#LFLAGS = -Wall                                                                 
CFLAGS = -Wall -c $(DEBUG) --pedantic
LFLAGS = -Wall $(DEBUG) --pedantic
TARGET = busqueda
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)        
busqueda.o :elapsed_time.h busqueda.cpp
	$(CC) $(CFLAGS) busqueda.cpp
clean:
	\rm *.o $(TARGET)
