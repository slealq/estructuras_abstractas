OBJS = principal.cpp arbol_avl.h
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG) 
TARGET = principal

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
arbol.o : arbol.h
	$(CC) $(CFLAGS) arbol.h
clean :
	\rm $(TARGET)
