vector: src/vector.cpp
	g++ -std=c++17 -o $@ $<

seq-id: src/sequence-ids.cpp
	g++ -std=c++17 -o $@ $<

if: src/if.cpp
	g++ -std=c++17 -o $@ $<

init: src/init.cpp
	g++ -std=c++17 -o $@ $<

lambda: src/lambda.cpp
	g++ -std=c++17 -o $@ $<

optional: src/optional.cpp
	g++ -std=c++17 -o $@ $<
