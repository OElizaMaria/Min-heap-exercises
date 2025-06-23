CC = gcc
CFLAGS = -Wall -Wextra
TARGET = tema2
SRCS = tema2.c

#BUILD
build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
#RUN 
run: build
	./$(TARGET) $(ARGS)
#CLEAN
	rm -f $(TARGET)
