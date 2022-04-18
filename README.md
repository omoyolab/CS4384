# CS4384
CS 4384 - AUTOMATA THEORY

Attached are the files DFA_2.hpp, DFA_2.cpp, DFA_test_file_2.cpp, and YOURNAME_2.cpp.

DFA_2.hpp and DFA_2.cpp define a simple data structure to represent a deterministic finite automaton;
but the implementation of some of functions is missing.

Note there are implementations of the union, intersection, difference, and complement constructions included.

YOURNAME_2.cpp contains wrong implementations of six functions; your task is to implement them.

DFA_test_file_2.cpp has a main function which tests the functions.

You can compile this as-is on the CS linux machines with:
g++ --std=c++11 DFA_2.cpp DFA_test_file_2.cpp and YOURNAME_2.cpp
The Boost C++ libraries are already available on the CS linux machines.
Running the resulting program will of course declare the test a failure.
There are other compiler flags beyond --std=c++11 that you may wish to use, but they aren't strictly needed.

Revise YOURNAME_2.cpp to correctly implement these six functions, rename it to your name, and submit that file.
Don't change either of DFA_2.hpp or DFA_2.cpp.
Feel free to revise DFA_test_file_2.cpp or write your own.
Just because all test cases pass does not mean your solution is correct.

You may discuss the assignment with each other, but do not copy.

(You may notice that this uses the boost matrix library instead of the boost multidimentional array library;
The syntax to access a stored value is a little different.)

The functions to be implemented:
dfa_is_accepted: Given a DFA and a string, does the DFA accept the string? (This is the same function from Coding 1.)
dfa_is_empty: Given a DFA, is its language the empty set?
dfa_is_all: Given a DFA, is its language the set of all bit strings?
dfa_is_infinite: Given a DFA, is its language infinite?
dfa_is_equal: Given two DFAs, are their languages the same?
dfa_is_subset: Given two DFAs, is the first's language a subset of the second's?
