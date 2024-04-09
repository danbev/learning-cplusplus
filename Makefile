CC = g++
SRCDIR = src
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TARGETS := $(patsubst $(SRCDIR)/%.cpp, %, $(SOURCES))

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): % : $(SRCDIR)/%.cpp | bindir
	$(CC) -o ${BINDIR}/$@ $<

bindir: bin

bin: 
	@mkdir -p $(BINDIR)

clean:
	${RM} -rf $(BINDIR)

