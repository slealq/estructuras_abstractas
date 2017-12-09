OBJS = neural_network_test.cpp neural_network.o
CC = g++
DEBUG = -g
EIGEN = -I ../network/eigen/
CFLAGS = -c $(EIGEN) $(DEBUG)
LFLAGS = $(EIGEN) $(DEBUG)
TARGET = neural_network

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

neural_network.o : neural_network.h
	$(CC) $(CFLAGS) neural_network.cpp

clean-utils:
	@printf "Removing *~ *# files ... \n"
	$(RM) *~ *#

clean-exec:
	@printf "Removing executables and object files ... \n"
	$(RM) *.o $(TARGET)

clean: clean-utils clean-exec
