CC = g++
BISON = bison
FLEX = flex

TARGET = translater
YY = yy
BISON_SOURCE = $(YY)/parser.y
FLEX_SOUCRCE = $(YY)/scanner.l
YY_SRC = $(YY)/src
BISON_OUTPUT = $(YY_SRC)/parser.cc
FLEX_OUTPUT = $(YY_SRC)/scanner.cc
SOURCES = src/*.cpp $(YY_SRC)/*.cc
INCLUDE = include
BIN = bin

OPTIMIZE = -O3

all : 
	@mkdir -p $(YY_SRC) $(BIN)
	@$(BISON) -ra -o $(BISON_OUTPUT) $(BISON_SOURCE)
	@$(FLEX) -o $(FLEX_OUTPUT) $(FLEX_SOUCRCE)
	@$(CC) -DNDEBUG $(OPTIMIZE) -I$(INCLUDE) -I$(YY_SRC) -o $(BIN)/$(TARGET) $(SOURCES) 

clean :
	@rm -r $(YY_SRC) $(BIN)