# Simple Makefile for 6.837 assignment 0
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.c \
		  matrix.c \
		  image.c \
		  ifs.c

# ===============================================================

LIBS            = -lm 
CC		= g++
INCLUDE 	= -I/usr/include 
EXE 	  	= ifs
OBJS =  $(SRCS:.c=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE) 

depend:
	$(CC) -E -M $(INCLUDE) $(SRCS) > Makefile.depend

clean: 
	rm -f *~ *bak *.o  $(EXE) Makefile.depend

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $< -c -o $@

# ===============================================================

-include Makefile.depend

# DO NOT DELETE