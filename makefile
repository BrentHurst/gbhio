# G BRENT HURST
# makefile for gbhio.h

CC = g++
LANGUAGE = cpp
CFLAGS = -Wall

INCLUDEDIR = $(HOME)/include
HEADERDIR = $(INCLUDEDIR)/headers

########## EDIT BELOW HERE ##########

NAME=gbhio

# libLIBRARY.a
LIBFILENAME = $(INCLUDEDIR)/lib$(NAME).a

# .h file
HEADER = $(HEADERDIR)/$(NAME).h

# list all .o files
OBJECTS = Delimited.o

########## EDIT ABOVE HERE ##########

all: $(LIBFILENAME)

$(LIBFILENAME): $(OBJECTS)
	ar -vr $(LIBFILENAME) $(OBJECTS)

%.o: %.$(LANGUAGE) $(HEADER)
	$(CC) $(CFLAGS) -c $*.$(LANGUAGE)

.PHONY: clean
clean:
	rm -f $(OBJECTS)

.PHONY: cleanall
cleanall:
	rm -f $(OBJECTS) $(LIBFILENAME)
