OBJS = bloom_filter_test.cpp bloom_filter.o MurmurHash3.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)
TARGET = bloom_filter

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

bloom_filter.o : bloom_filter.h
	$(CC) $(CFLAGS) bloom_filter.cpp

MurmurHash3.o : smhasher/src/MurmurHash3.h
	$(CC) $(CFLAGS) smhasher/src/MurmurHash3.cpp

clean-utils:
	@printf "Removing *~ *# files ... \n"
	$(RM) *~ *#
clean-exec:
	@printf "Removing executables and object files ... \n"
	$(RM) *.o $(TARGET)
clean: clean-utils clean-exec
