###############################################################################
# Makefile for boom-attacks
###########################
# Makes baremetal executables to run on BOOM
###############################################################################

# Folders
SRC  := src
INC  := include
OBJ  := obj
BIN  := bin
DUMP := dump
DEP  := dep

# Commands and flags
CC       := /home/admin1/ZZworkspace/git/chipyard/.conda-env/riscv-tools/bin/riscv64-unknown-elf-gcc
OBJDUMP  := /home/admin1/ZZworkspace/git/chipyard/.conda-env/riscv-tools/bin/riscv64-unknown-elf-objdump -S
CFLAGS    = -I$(INC) -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable
DEPFLAGS  = -MT $@ -MMD -MP -MF $(DEP)/$*.d

# Programs to compile
PROGRAMS = spectre-v1
BINS     = $(addprefix $(BIN)/,$(addsuffix .riscv,$(PROGRAMS)))
DUMPS    = $(addprefix $(DUMP)/,$(addsuffix .dump,$(PROGRAMS)))


all: $(BINS) $(DUMPS)

dumps: $(DUMPS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@mkdir -p $(DEP)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Build executable
$(BIN)/%.riscv: $(OBJ)/%.o  
	@mkdir -p $(BIN)
	$(CC) $< -o $@

# Build dump
$(DUMP)/%.dump: $(BIN)/%.riscv
	@mkdir -p $(DUMP)
	$(OBJDUMP) -D $< > $@

# Keep the temporary .o files
.PRECIOUS: $(OBJ)/%.o

# Remove all generated files
clean:
	rm -rf $(BIN) $(OBJ) $(DUMP) $(DEP)
.PHONY: all clean
# Include dependencies
-include $(addprefix $(DEP)/,$(addsuffix .d,$(PROGRAMS)))
