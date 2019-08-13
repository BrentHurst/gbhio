# G BRENT HURST
# Makefile for gbhio



OBJDIR = obj
SRCDIR = src
HEADERDIR = .
LIBDIR = .

CC = g++
LANGUAGE = cpp
CFLAGS = -Wall -Wextra -I$(LIBDIR)

########## EDIT BELOW HERE ##########

NAME = gbhio

########## EDIT ABOVE HERE ##########

LIBFILENAME = $(LIBDIR)/lib$(NAME).a
HEADERS = $(HEADERDIR)/$(NAME).h
OBJECTS = $(patsubst $(SRCDIR)/%.$(LANGUAGE),$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.$(LANGUAGE)))


all: $(LIBFILENAME)

$(LIBFILENAME): $(OBJECTS)
	ar -vr $(LIBFILENAME) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(LANGUAGE) $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir -p $(OBJDIR)


.PHONY: clean
clean:
	rm -f $(OBJECTS)

.PHONY: cleanall
cleanall:
	rm -f $(OBJECTS) $(LIBFILENAME)
