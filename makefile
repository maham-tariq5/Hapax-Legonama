## define the two executables we want to build
HEXE = hapax
WEXE = printwords

## define the set of object files we need to build each executable
HOBJS		= hapax_main.o LLNode.o word_extractor.o word_tally.o
WOBJS		= words_main.o word_extractor.o


##
## TARGETS: below here we describe the target dependencies and rules
##

## top level target -- build all the dependent executables
all : $(HEXE) $(WEXE)

## targets for each executable, based on the object files indicated
$(HEXE) : $(HOBJS)
	$(CC) $(CFLAGS) -o $(HEXE) $(HOBJS)

$(WEXE): $(WOBJS)
	$(CC) $(CFLAGS) -o $(WEXE) $(WOBJS)

## convenience target to remove the results of a build
clean :
	- rm -f $(HOBJS) $(HEXE)
	- rm -f $(WOBJS) $(WEXE)

