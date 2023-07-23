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

CC=g++-10

CXXFLAGS+=-std=c++20
CXXFLAGS+=-Werror
CXXFLAGS+=-Wall

SRC=
SRC+=main.cpp

SRC_OBJ=$(subst .cpp,.o,$(SRC))
OBJS=$(SRC_OBJ)

$(BINDIR)/puzzle: $(addprefix $(BUILDDIR)/, $(OBJS))
	$(CC) $(CXXFLAGS) $(DBG_OPT) $^ -o $@

DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o:%.cpp
	$(CC) $(CXXFLAGS) $(DBG_OPT) $(DEPFLAGS) -c $< -o $@

$(SRC): Makefile
	touch $@

-include $(subst .o,.d,$(shell ls $(BUILDDIR)/*.o))
