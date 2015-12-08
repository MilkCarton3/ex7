#makefile for COMP20010 lab 6
#This works for c compilation and latex compilation
# C stuff
CC=gcc
CFLAGS=-g -std=c99 -Wall
# uncomment next line if you need to link to math library
# LDFLAGS=-lm

# latex compilation. 
%.pdf:%.ps
	ps2pdf $<
%.ps:%.dvi
	dvips -o $@ $<
%.dvi:%.tex
	while (latex $< ;\
	grep -q "Rerun to get cross" $*.log) do true; \
	done

clean:
	rm *.dvi; rm *.aux; rm *.log