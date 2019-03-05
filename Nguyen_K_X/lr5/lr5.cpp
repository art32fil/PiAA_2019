// lr5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <deque>
class Word {
public:
	int wordId;
	std::string word;
	Word(int wordId, std::string word) :wordId(wordId), word(word) {};
};
class State {
public:
	int state_id;
	State *parent;
	std::map<char, State*> nextStates;
	std::vector<Word*> output;
	State *failState;
	State(int state_id, State* parent = nullptr) :state_id(state_id), parent(parent) {}
	bool hasNext(char key) {
		return nextStates.find(key) != nextStates.end();
	}
	State* getNext(char key) {
		if (hasNext(key)) {
			return nextStates.find(key)->second;
		}
		else return failState;
	}
	State* addNext(int stateId, char key) {
		State *next = new State(stateId, this);
		nextStates[key] = next;
		return next;
	}

};

class SearchResult {
public:
	int pos;
	Word *word;
	SearchResult(int pos, Word *word) :pos(pos), word(word) {}
};
void addWord(Word *word, State *root, int& lastState, std::map<int, State*>& states) {
	State *current = root;
	for (int i = 0; i < word->word.length(); i++) {
		if (current->hasNext(word->word.at(i))) {
			current = current->getNext(word->word.at(i));
		}
		else {
			lastState++;
			current = current->addNext(lastState, word->word.at(i));
			states[current->state_id] = current;
		}
	}
	current->output.push_back(word);
}
void printTree(State* root, int level = 0) {
	for (int i = 0; i < level; i++) std::cout << "\t";
	std::cout << "State: " << root->state_id<<std::endl;
	if (root->failState != nullptr)
	{
		for (int i = 0; i < level; i++) std::cout << "\t";
		std::cout << "Fail state: " << root->failState->state_id << std::endl;
	}
	if (!root->output.empty()) {
		for (int i = 0; i < level; i++) std::cout << "\t";
		std::cout << "Output:  ";
		for (Word *w : root->output) {
			std::cout << w->word <<"  ";
		}
		std::cout << std::endl;
	}
	for (std::map<char, State*>::iterator it = root->nextStates.begin(); it != root->nextStates.end(); it++)
	{
		for (int i = 0; i < level; i++) std::cout << "\t";
		std::cout << root->state_id << "  =" << it->first << "=>  " << it->second->state_id << '\n';

		printTree(it->second, level + 1);
	}


}
State* constructGoto(std::vector<Word*> dictionary, std::map<int, State*>& states, int& lastState) {
	State* root = new State(0);
	states[0] = root;
	for (Word *word : dictionary) {
		addWord(word, root, lastState, states);
	}
	return root;
}
void constructFailFunction(State *root, std::map<int, State*>& states) {

	std::deque<State*> queue;
	int * ff = new int[states.size()];
	ff[0] = 0;
	root->failState = root;
	for (auto it = root->nextStates.begin(); it != root->nextStates.end(); it++) {
		queue.push_back(it->second);
		ff[it->second->state_id] = 0;
		it->second->failState = root;
	}

	while (!queue.empty()) {
		State *cur = queue.front();
		queue.pop_front();
		for (auto it = cur->nextStates.begin(); it != cur->nextStates.end(); it++) {
			queue.push_back(it->second);
			State* state = states[ff[cur->state_id]];
			while (!state->hasNext(it->first)) {
				if (state == states[ff[state->state_id]]) break;
				state = states[ff[state->state_id]];
			}
			if (state->hasNext(it->first)) {
				//using temporary fail function array 
				ff[it->second->state_id] = state->nextStates[it->first]->state_id;


				//itergrating fail function in state object
				it->second->failState = state->nextStates[it->first];
				for (Word *merge_output : it->second->failState->output) {
					it->second->output.push_back(merge_output);
				}
				
			}
			else {
				it->second->failState = state;
				ff[it->second->state_id] = state->state_id;
			}
		}
	}

	delete ff;
}

bool compareResult(SearchResult *a, SearchResult *b) {
	if (a->pos == b->pos) return a->word->wordId < b->word->wordId;
	else
	return a->pos < b->pos;
}
void AhoCorasick(State *root, std::string text) {
	std::vector<SearchResult*> results;
	State* current = root;
	for (int i = 0; i < text.length(); i++) {
		char c = text.at(i);
		while (current!=root&&!current->hasNext(c)) current = current->failState;
		current = current->getNext(c);
		//std::cout << text.at(i)<< "   go to: " << current->state_id << std::endl;
		if (!current->output.empty()) {
			for (Word *word : current->output) {
				SearchResult *r = new SearchResult(i - word->word.length()+2, word);
				results.push_back(r);
			}
			
		}
	}

	std::sort(results.begin(), results.end(), compareResult);
	for (SearchResult *r : results) {
		std::cout << r->pos << " " << r->word->wordId << std::endl;
	}
}
int main()
{
	std::vector<Word*> dictionary;
	std::map<int, State*> states;
	int totalStates = 0;
	std::string text;

	int dictionaryLength;
	std::cin >> text;
	std::cin >> dictionaryLength;
	for (int i = 0; i < dictionaryLength; i++) {
		std::string word;
		std::cin >> word;
		dictionary.push_back(new Word(i + 1, word));
	}
	

	State* root = constructGoto(dictionary, states, totalStates);
	constructFailFunction(root, states);

	//printTree(root);

	AhoCorasick(root, text);
	getchar();
	getchar();
	getchar();
	return 0;
}

