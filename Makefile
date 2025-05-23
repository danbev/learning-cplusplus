CC = g++
SRCDIR = src
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TARGETS := $(patsubst $(SRCDIR)/%.cpp, %, $(SOURCES))

CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wnoexcept -fexceptions -Wnoexcept-type
#CXXFLAGS += -I./external/cpp-httplib -DCPPHTTPLIB_OPENSSL_SUPPORT
CXXFLAGS += -I./external/cpp-httplib
#LDFLAGS = -lssl -lcrypto

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): % : $(SRCDIR)/%.cpp | bindir
	$(CC) $(CXXFLAGS) -g -o ${BINDIR}/$@ $< $(LDFLAGS)

#noexcept: src/noexcept.cpp | bindir
#	$(CC) $(CXXFLAGS) $(LDFLAGS) -o ${BINDIR}/noexcept $< 

bindir: bin

bin: 
	@mkdir -p $(BINDIR)

update-submodule:
	git submodule update --init --recursive

clean:
	${RM} -rf $(BINDIR)

curl-http-server:
	curl http://localhost:8080/something

vision-main: src/vision.cpp
	$(CC) -Isrc -std=c++11 -Wall -Wextra -Wpedantic -g -o bin/vision-main src/vision.cpp src/vision-main.c
