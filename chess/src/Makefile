#Makefile:
CC     = gcc -lSDL
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall
LFLAGS = -ansi -Wall  -c
SDLFLAGS = -lSDL
BDIR = ../bin

all: Chess

test: 
	@echo "test"

Chess: Chess.o board.o ChessUI.o Move.o MoveList.o RuleSet.o log.o AIaid.o AI1.o BoardList.o test.o Node.o AIextra.o
	$(CC) $(DEBUG)  Chess.o board.o ChessUI.o Move.o MoveList.o RuleSet.o log.o AIaid.o AI1.o BoardList.o test.o Node.o AIextra.o -o Chess
	@cp $@ $(BDIR)/$@


########### generate object files ###########

Chess.o: Chess.c board.h ChessUI.h Move.h MoveList.h RuleSet.h log.h AI.h test.h
	$(CC) $(LFLAGS) -lSDL  Chess.c -o Chess.o -g 

RuleSet.o: RuleSet.c RuleSet.h MoveList.h Move.h board.h
	$(CC) $(LFLAGS) RuleSet.c -o RuleSet.o -g

ChessUI.o: ChessUI.c ChessUI.h
	$(CC) $(LFLAGS) ChessUI.c -o ChessUI.o -g

board.o: board.c board.h
	$(CC) $(LFLAGS)	board.c -o board.o -g

Move.o: Move.c Move.h
	$(CC) $(LFLAGS) Move.c -o Move.o -g

MoveList.o: MoveList.c MoveList.h
	$(CC) $(LFLAGS) MoveList.c -o MoveList.o -g

log.o: log.c log.h
	$(CC) $(LFLAGS) $(DEBUG) log.c -o log.o -g

#AI.o: AI.c AI.h AIaid.h MoveList.h Move.h board.h
	#$(CC) $(DEBUG) $(LFLAGS) AI.c -o AI.o
	
AI1.o: AI1.c AI.h AIaid.h MoveList.h Move.h board.h Node.h AIextra.h
	$(CC) $(DEBUG) $(LFLAGS) AI1.c -o AI1.o -g

Node.o: Node.c Node.h MoveList.h Move.h board.h
	$(CC) $(DEBUG) $(LFLAGS) Node.c -o Node.o -g

AIaid.o: AIaid.c AIaid.h RuleSet.h Move.h MoveList.h board.h
	$(CC) $(LFLAGS) AIaid.c -o AIaid.o -g

AIextra.o: AIextra.c AIextra.h RuleSet.h MoveList.h Move.h board.h
	$(CC) $(LFLAGS) AIextra.c -o AIextra.o -g

BoardList.o: BoardList.c BoardList.h board.h
	$(CC) $(LFLAGS) BoardList.c -o BoardList.o -g

test.o: test.h test.c RuleSet.h RuleSet.c Move.h Move.c MoveList.h MoveList.c board.h board.c log.h log.c ChessUI.c ChessUI.h
	$(CC) $(LFLAGS) test.c -o test.o -g
	


clean:
	rm -f *.o 
	rm -f Chess
# EOF
