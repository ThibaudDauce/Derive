SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
CC = gcc
YACC=yacc
LEX=lex
#CFLAGS=-Wall -pedantic -g
CFLAGS=-g
LDFLAGS=-lm


INTERPRETEUR=derive
FICHIER_SRC_LEX=$(SRCDIR)/$(INTERPRETEUR).l
FICHIER_SRC_YACC= $(SRCDIR)/$(INTERPRETEUR).y

FICHIER_LEX=lex.yy
FICHIER_YACC=y.tab

OBJECTS=$(SRCDIR)/$(FICHIER_LEX).o $(SRCDIR)/$(FICHIER_YACC).o
LIB_OBJECTS=$(SRCDIR)/libExpressionMathematique.o $(SRCDIR)/ExpressionMathematique.o
LIB=ExpressionMathematique

all: derive


derive :  $(BINDIR)/derive 

$(BINDIR)/derive : $(OBJECTS) $(LIBDIR)/lib$(LIB).a
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -l$(LIB) -Llib

$(LIBDIR)/lib$(LIB).a : $(LIB_OBJECTS)
	$(AR)  r $(LIBDIR)/lib$(LIB).a  $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(LIBDIR)/%.so : $(SRCDIR)/%.c
	$(CC) -shared -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(SRCDIR)/$(FICHIER_YACC).c : $(FICHIER_SRC_YACC)
	$(YACC) -o $(SRCDIR)/$(FICHIER_YACC).c $^

$(SRCDIR)/$(FICHIER_LEX).c : $(FICHIER_SRC_LEX) $(INCLUDEDIR)/$(FICHIER_YACC).h
	$(LEX) -o $(SRCDIR)/$(FICHIER_LEX).c $<

$(INCLUDEDIR)/$(FICHIER_YACC).h : $(FICHIER_SRC_YACC)
	$(YACC) --defines=$(INCLUDEDIR)/$(FICHIER_YACC).h -o $(SRCDIR)/$(FICHIER_YACC).c $<	

clean :
	rm -f $(BINDIR)/*
	rm -f $(LIBDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/$(FICHIER_LEX).c
	rm -f $(SRCDIR)/$(FICHIER_YACC).c
	rm -f $(INCLUDEDIR)/$(FICHIER_YACC).h