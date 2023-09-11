.DEFAULT: all

TARGETS=puzzle

BINDIR?=bin
BUILDDIR?=build

.PHONY: all
all: $(BUILDDIR) $(BINDIR) $(addprefix $(BINDIR)/, $(TARGETS))

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	rm -rf $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

DBG_OPT?=-gdwarf-2 -O2 # symbols and optimization

CC=gcc

CFLAGS+=-std=gnu99
#CXXFLAGS+=-Werror
CFLAGS+=-Wall

SRC=
SRC+=core_split_screen.c

INC=

SRC_OBJ=$(subst .c,.o,$(SRC))
OBJS=$(SRC_OBJ)

$(BINDIR)/puzzle: $(addprefix $(BUILDDIR)/, $(OBJS))
	$(CC) $(CFLAGS) $(DBG_OPT) $^ -o $@ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o:%.c
	$(CC) $(CFLAGS) $(DBG_OPT) $(DEPFLAGS) $(INC) -c $< -o $@

$(SRC): Makefile
	touch $@

-include $(subst .o,.d,$(shell ls $(BUILDDIR)/*.o))
