CC = g++
SRCDIR = src
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TARGETS := $(patsubst $(SRCDIR)/%.cpp, %, $(SOURCES))

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): % : $(SRCDIR)/%.cpp | bindir
	$(CC) -std=c++11 -o ${BINDIR}/$@ $<

#noexcept: src/noexcept.cpp | bindir
#	$(CC) -std=c++11 -Wall -Wextra -Wpedantic -Wnoexcept -fexceptions -Wnoexcept-type -o ${BINDIR}/noexcept $<

bindir: bin

bin: 
	@mkdir -p $(BINDIR)

clean:
	${RM} -rf $(BINDIR)

