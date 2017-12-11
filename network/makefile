OBJS = neural_network_test.cpp neural_network.o mnist_loader.o
CC = g++
INCLUDES = -I$(EIGEN)
INCLUDES += -Imnist-loader/include
DEBUG = -g
DEBUG += -O3
EIGEN = ../network/eigen/
CFLAGS = -c $(INCLUDES) $(DEBUG)
LFLAGS = $(INCLUDES) $(DEBUG)
TARGET = neural_network

all : test

compile : $(TARGET)

test: $(TARGET) data

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

neural_network.o : neural_network.h
	$(CC) $(CFLAGS) neural_network.cpp

mnist_loader.o : mnist-loader/include/mnist_loader.h
	$(CC) $(CFLAGS) mnist-loader/src/mnist_loader.cc

data:
	@if [ ! -e dataset ]; then \
	./mnist-loader/tools/mnist-download.sh; \
	fi

clean-utils:
	@printf "Removing *~ *# files ... \n"
	$(RM) *~ *#

clean-exec:
	@printf "Removing executables and object files ... \n"
	$(RM) *.o $(TARGET)

clean: clean-utils clean-exec
