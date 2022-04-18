#include <iostream>
#include <vector>
#include <list>
#include "DFA_2.hpp"

// Does m accept string w?
bool dfa_is_accepted(const DFA &m, const std::string &w) {
	int currentState = m.initialState;
	for (int i = 0; i < w.length(); i++) {
		//cout << w[i];
		int character = w[i] - 48; //get alphabet 0 or 1
		int nextState = m.transFunc(character, currentState);     //go to next state by looking up in transFucn
		if (nextState == -1) { //-1 indicates a dead end which means you cant move from that state to any other.
			break;
		}
		currentState = nextState;           //update current state
	}

	return m.finalStates[currentState];      //check if final state is true in finalStates or not


}

// Does m accept any strings? That is, is L(m) the empty set?
void FinalCheck(const DFA&m,int c, vector<bool> visit,bool &final) {
	if (m.finalStates[c]) {
		final = true;
		return;
	}
	else if (visit[c]) {
		return;
	}

	visit[c] = true;
	FinalCheck(m, m.transFunc(1,c), visit, final);
	FinalCheck(m, m.transFunc(0,c), visit, final);


}

bool dfa_is_empty(const DFA&m) {
	bool final = false;
	vector<bool> visit;
	for (int i = 0; i < m.numStates; i++) {
		visit.push_back(false);
	}
	int currentState = m.initialState;
	FinalCheck(m,currentState,visit,final);
	if (final) {
		return false;
	}
	return true;

}

// Does m accept every string? That is, is L(m) the set of all strings?
bool mustBeFinal(const DFA &m, vector<bool> visit, int input) {
	bool cycle = false;
	int currentState = m.initialState;
	while (!cycle) {
		if (visit[currentState]) {
			cycle = true;
		}
		else if (!m.finalStates[currentState]) {
			cycle = false;
			break;
		}
		else if (currentState == -1) {
			cycle = true;
		}
		visit[currentState] = true;
		currentState = m.transFunc(input,currentState);

	}
	return cycle;
}

bool dfa_is_all(const DFA &m) {
	vector<bool> visit;
	for (int i = 0; i < m.numStates; i++) {
		visit.push_back(false);
	}
	int currentState = m.initialState;
	if (mustBeFinal(m, visit, 1)) {
		return true;
	}
	else if (mustBeFinal(m, visit, 0)) {
		return true;
	}
	return false;
	


}


// Is L(m) infinite?
enum state { UNVISITED, SEEN, VISITED };
void cycle_help(vector<int> &path, vector<state> &status, vector<int> &p, vector<int> &cycle, int u, bool &check, list<int> *vertice)  {
	status[u] = SEEN;
	cycle.push_back(u);

	for (int v : vertice[u]) {
		if (status[v] == UNVISITED) {
			p[v] = u;
			cycle_help(path, status, p, cycle, v, check,vertice);
		}
		else if ((status[v] == SEEN) && !check) {

			vector<int>::iterator ptr = cycle.begin();
			while (*ptr != v) ptr++;

			for (ptr; ptr < cycle.end(); ptr++) {
				path.push_back(*ptr);
			}

			check = true;
		}
	}
	status[u] = VISITED;
}

bool cycle(vector<int> &path, int num_vertices, list<int> *vertice)  {

	vector<state> status(num_vertices);
	vector<int> p(num_vertices);
	vector<int> cycle;
	bool check = false;

	for (int i : status) {
		status[i] = UNVISITED;
		p[i] = -1;
	}

	for (int u = 0; u < num_vertices; ++u) {
		if (status[u] == UNVISITED) {
			cycle_help(path, status, p, cycle, u, check,vertice);
		}
	}

	return check;
}


bool dfa_is_infinite(const DFA &m) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < m.numStates; j++) {
			cout << m.transFunc(i,j) << " ";
		}
		cout << endl;
	}
	int num_vertices = m.numStates;
	list<int> *vertice = new list<int>[num_vertices];

	for (int i = 0; i < m.numStates; i++) {
		vertice[i].push_back(m.transFunc(0,i));
		vertice[i].push_back(m.transFunc(1,i));
	}
	vector<int> path;
	bool c = cycle(path, m.numStates,vertice);

	if (c) {
		for (int i = 0; i < path.size(); i++) {
			if (m.finalStates[path[i]]) {
				return true;
			}
		}
	}
	if (!dfa_is_empty(m)) {
		for (int i = 0; i < m.numStates; i++) {
			if (m.finalStates[i]) {
				if (m.transFunc(0,i) == i || m.transFunc(1,i) == i) {
					return true;
				}
			}
		}
	}
	return false;


	
}


// Is L(m1) equal to L(m2)?
bool checkCombination(const DFA &m1, const DFA &m2, int state1, int state2, int input) {
	int s1 = m1.transFunc(input,state1);
	int s2 = m2.transFunc(input,state2);
	if (m1.finalStates[s1] && m2.finalStates[s2]) {
		return true;
	}
	if (!m1.finalStates[s1] && !m2.finalStates[s2]) {
		return true;
	}
	return false;

}
bool search(vector<int> s, int k,int k1) {
	for (int i = 0; i < s.size(); i=i+2) {
		if (s[i] == k && s[i+1]==k1) {
			return true;
		}
	}
	return false;
}

bool dfa_is_equal(const DFA &m1, const DFA &m2) {
	bool ret = true;
	bool brk = false;
	vector<int> sum;
	int current = m1.initialState;
	int current2 = m2.initialState;
	int current3 = m1.initialState;
	int current4 = m2.initialState;
	sum.push_back(current);
	sum.push_back(current2);

	while (true) {
		brk = false;
		int s1 =0, s2 = 0, s3 = 0, s4 = 0;
		if (checkCombination(m1, m2, current, current2, 0)) {
			s1 = m1.transFunc(0,current);
			s2 = m2.transFunc(0,current2);
		}
		else {
			ret = false;
			break;
		}
		if (checkCombination(m1, m2, current3, current4, 1)) {
			s3 = m1.transFunc(1,current);
			s4 = m2.transFunc(1,current2);
		}
		else {
			ret = false;
			break;
		}

		if (!search(sum,s1,s2)) {
			sum.push_back(s1);
			sum.push_back(s2);
			current = s1;
			current2 = s2;
			brk = true;
		}
		if(!search(sum,s3,s4)){
			sum.push_back(s3);
			sum.push_back(s4);
			current3 = s3;
			current4 = s4;
			brk = true;
		}
		if (!brk) {
			break;
		}

	}
	return ret;


}




// Is L(m1) a subset of L(m2)?
DFA dfa_complement (const DFA &m)
{
	DFA m2 = m;
	for (auto it = m2.finalStates.begin (); it != m2.finalStates.end (); ++it)
		*it = !*it;
	return m2;
}

DFA dfa_crossproduct_helper (const DFA &m1, const DFA &m2)
{
	DFA m3;
	m3.numStates = m1.numStates * m2.numStates;
	m3.transFunc.resize (2, m3.numStates);
	m3.initialState = m1.initialState + m1.numStates * m2.initialState;
	for (int i = 0; i < m1.numStates; ++i)
		for (int j = 0; j < m2.numStates; ++j)
			for (int x : {0, 1})
				m3.transFunc (x, i + m1.numStates * j) = m1.transFunc (x, i) + m1.numStates * m2.transFunc (x, j);
	m3.finalStates.resize (m3.numStates);
	return m3;
}

DFA dfa_union (const DFA &m1, const DFA &m2)
{
	DFA m3 = dfa_crossproduct_helper (m1, m2);
	for (int i = 0; i < m1.numStates; ++i)
		for (int j = 0; j < m2.numStates; ++j)
			m3.finalStates [i + m1.numStates * j] = m1.finalStates [i] || m2.finalStates [j];
	return m3;
}

DFA dfa_intersection (const DFA &m1, const DFA &m2)
{
	DFA m3 = dfa_crossproduct_helper (m1, m2);
	for (int i = 0; i < m1.numStates; ++i)
		for (int j = 0; j < m2.numStates; ++j)
			m3.finalStates [i + m1.numStates * j] = m1.finalStates [i] && m2.finalStates [j];
	return m3;
}

bool dfa_is_subset(const DFA &m1, const DFA &m2){
	DFA newdfa =  dfa_intersection(m1, dfa_complement(m2));  //if its equal to m1, m1 is subset of m2
	if (dfa_is_empty(newdfa)) {
		return true;
	}
	return false;

}


