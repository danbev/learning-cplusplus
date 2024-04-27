a.so: b.so a.cpp
	g++ -shared -fPIC -o lib$@ a.cpp -L. -lb

b.so: b.cpp
	g++ -shared -fPIC -o lib$@ $<

a_test: a.so b.so
	g++ -o a_test a_test.cpp \
	    -Igoogletest/googletest/include \
	    liba.so \
	    -Lgoogletest/build/lib \
	    -lgtest -pthread

install_gtest:
	git clone --depth=1 -b main https://github.com/google/googletest.git
	mkdir googletest/build && googletest/build
	cmake .. & make

.PHONY: clean
clean:
	${RM} a.so b.so a_test
