# Name
EXEC = TIMING_ATTACK.bin

# Archive
ZIP = zip
TAR = tar.gz
ARCHIVE = Timing_Attack_On_Smart_Cards

# Directories
SRCDIR = Attack
OBJDIR = obj
BINDIR = bin

# Compiler
CC = g++ 

# Flags
FLAGS = -c -std=c++17 -g -L -Wall
GMPFLAG = -lgmp
THREADFLAG = -lpthread

# Files
DEPS = $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/*/*.h)
SRC = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Link files to get the program
all: config compil
	@ echo "Compilation done..."

compil: $(OBJ)
	@ $(CC) -o $(BINDIR)/$(EXEC) $(OBJ) $(GMPFLAG) $(THREADFLAG)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@ $(CC) -c -o $@ $< $(GMPFLAG) $(THREADFLAG) $(FLAGS)
	@ echo "Compilation : "$@" succes"

# Run program
run:
	@ ./$(BINDIR)/$(EXEC)
	
# Clean the whole programm
clean:
	@ if [ $(ARCHIVE).$(TAR) ]; then rm -f $(ARCHIVE).$(ZIP); fi
	@ rm -rf $(OBJDIR)
	@ rm -rf $(BINDIR)
	@ echo "Program cleaned up..."
	
# Make a zip archive
zip: clean
	@ zip -r $(ARCHIVE).$(ZIP) *
	@ echo "Find your zip in your directory..."

# Make a tar archive
tar: clean
	@ tar -czvf $(ARCHIVE).$(TAR) *
	@ echo "Find your tar in your directory..."

# Script
config:
	@ $(shell ./linker.sh) 
	
