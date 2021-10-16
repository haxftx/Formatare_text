CC = gcc
CFLAGS = -g -Wall
HEADERS = functii.h  
OBJECTS = format_text.o
EXEC = format_text


build: format_text

%.o: %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC) ${ARGS}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
