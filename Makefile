#-------------------------------------------------------------------------------
# Environment
#-------------------------------------------------------------------------------

CC = gcc
CC_STD = -std=iso9899:1999
CC_WARN = -Wpedantic -Wall -Wextra
CC_OPTM = -O2
CC_FLAGS =
CPP_INC =
LD_INC =
LD_LIBS = -lm

#-------------------------------------------------------------------------------
# Directories
#-------------------------------------------------------------------------------

BASEDIR = .
BASEDIR_MAIN = $(BASEDIR)

SRCDIR_MAIN = $(BASEDIR_MAIN)
OBJDIR_MAIN = $(BASEDIR_MAIN)/build
DISTDIR_MAIN = $(BASEDIR_MAIN)/bin

#-------------------------------------------------------------------------------
# Name of targets
#-------------------------------------------------------------------------------

G1_01_491_345 = gal1_01_491_345
G2_02_491_345 = gal2_02_491_345
G2_03_491_345 = gal2_03_491_345
G2_04_491_345 = gal2_04_491_345
G1_01_491_360 = gal1_01_491_360
G2_02_491_360 = gal2_02_491_360
G2_03_491_360 = gal2_03_491_360
G2_04_491_360 = gal2_04_491_360
H1 = heu1
H2 = heu2
H3 = heu3

#-------------------------------------------------------------------------------
# Default target(s)
#-------------------------------------------------------------------------------

default: all

all: $(G1_01_491_345) $(G2_02_491_345) $(G2_03_491_345) $(G2_04_491_345) \
     $(G1_01_491_360) $(G2_02_491_360) $(G2_03_491_360) $(G2_04_491_360) \
     $(H1) $(H2) $(H3)

#-------------------------------------------------------------------------------
# Dependencies and objects
#-------------------------------------------------------------------------------

FQLA_DEP =
FQLA_OBJ = \
	$(OBJDIR_MAIN)/fqla/fqla.o

GALLAGER_DEP = \
	$(SRCDIR_MAIN)/decoder/gallager_thr.h
GALLAGER_OBJ = \
	$(FQLA_OBJ) \
	$(OBJDIR_MAIN)/decoder/fqla_util.o
G1_01_491_345_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g1_01_491_345.o \
	$(OBJDIR_MAIN)/gallager.o
G2_02_491_345_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_02_491_345.o \
	$(OBJDIR_MAIN)/gallager.o
G2_03_491_345_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_03_491_345.o \
	$(OBJDIR_MAIN)/gallager.o
G2_04_491_345_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_04_491_345.o \
	$(OBJDIR_MAIN)/gallager.o
G1_01_491_360_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g1_01_491_360.o \
	$(OBJDIR_MAIN)/gallager.o
G2_02_491_360_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_02_491_360.o \
	$(OBJDIR_MAIN)/gallager.o
G2_03_491_360_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_03_491_360.o \
	$(OBJDIR_MAIN)/gallager.o
G2_04_491_360_OBJ = \
	$(GALLAGER_OBJ) \
	$(OBJDIR_MAIN)/decoder/gallager_core_g2_04_491_360.o \
	$(OBJDIR_MAIN)/gallager.o

HEURISTIC_DEP =
HEURISTIC_OBJ = \
	$(FQLA_OBJ) \
	$(OBJDIR_MAIN)/decoder/fqla_util.o
H1_OBJ = \
	$(HEURISTIC_OBJ) \
	$(OBJDIR_MAIN)/decoder/heuristic_core_h1.o \
	$(OBJDIR_MAIN)/heuristic_h1.o
H2_OBJ = \
	$(HEURISTIC_OBJ) \
	$(OBJDIR_MAIN)/decoder/heuristic_core_h2.o \
	$(OBJDIR_MAIN)/heuristic_h2.o
H3_OBJ = \
	$(HEURISTIC_OBJ) \
	$(OBJDIR_MAIN)/decoder/heuristic_core_h3.o \
	$(OBJDIR_MAIN)/heuristic_h3.o

#-------------------------------------------------------------------------------
# Targets
#-------------------------------------------------------------------------------

$(OBJDIR_MAIN)/decoder/gallager_core_%.o: $(GALLAGER_DEP)

$(OBJDIR_MAIN)/decoder/gallager_core_g1_01_491_345.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG1_01_491_345 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_02_491_345.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_02_491_345 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_03_491_345.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_03_491_345 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_04_491_345.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_04_491_345 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g1_01_491_360.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG1_01_491_360 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_02_491_360.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_02_491_360 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_03_491_360.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_03_491_360 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/gallager_core_g2_04_491_360.o: $(SRCDIR_MAIN)/decoder/gallager_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DG2_04_491_360 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/heuristic_core_%.o: $(HEURISTIC_DEP)

$(OBJDIR_MAIN)/decoder/heuristic_core_h1.o: $(SRCDIR_MAIN)/decoder/heuristic_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H1 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/heuristic_core_h2.o: $(SRCDIR_MAIN)/decoder/heuristic_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H2 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/heuristic_core_h3.o: $(SRCDIR_MAIN)/decoder/heuristic_core.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H3 -c -o $@ $<

$(OBJDIR_MAIN)/decoder/%.o: $(SRCDIR_MAIN)/decoder/%.c
	mkdir -p $(OBJDIR_MAIN)/decoder
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -c -o $@ $<

$(OBJDIR_MAIN)/fqla/fqla.o: $(FQLA_DEP)

$(OBJDIR_MAIN)/fqla/%.o: $(SRCDIR_MAIN)/fqla/%.c
	mkdir -p $(OBJDIR_MAIN)/fqla
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -c -o $@ $<

$(OBJDIR_MAIN)/heuristic_h1.o: $(SRCDIR_MAIN)/heuristic.c
	mkdir -p $(OBJDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H1 -c -o $@ $<

$(OBJDIR_MAIN)/heuristic_h2.o: $(SRCDIR_MAIN)/heuristic.c
	mkdir -p $(OBJDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H2 -c -o $@ $<

$(OBJDIR_MAIN)/heuristic_h3.o: $(SRCDIR_MAIN)/heuristic.c
	mkdir -p $(OBJDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -DHEURISTIC_H3 -c -o $@ $<

$(OBJDIR_MAIN)/%.o: $(SRCDIR_MAIN)/%.c
	mkdir -p $(OBJDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) -c -o $@ $<

$(G1_01_491_345): $(G1_01_491_345_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_02_491_345): $(G2_02_491_345_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_03_491_345): $(G2_03_491_345_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_04_491_345): $(G2_04_491_345_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G1_01_491_360): $(G1_01_491_360_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_02_491_360): $(G2_02_491_360_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_03_491_360): $(G2_03_491_360_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(G2_04_491_360): $(G2_04_491_360_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(H1): $(H1_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(H2): $(H2_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

$(H3): $(H3_OBJ)
	mkdir -p $(DISTDIR_MAIN)
	$(CC) $(CC_STD) $(CC_WARN) $(CC_OPTM) $(CC_FLAGS) $(CPP_INC) $(LD_INC) $(LD_LIBS) -o $(DISTDIR_MAIN)/$@ $^

#-------------------------------------------------------------------------------
# Clean
#-------------------------------------------------------------------------------

clean:
	rm -rf $(OBJDIR_MAIN)

clean-all:
	rm -rf $(OBJDIR_MAIN) $(DISTDIR_MAIN)
