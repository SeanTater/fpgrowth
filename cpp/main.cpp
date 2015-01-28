/*
 * main.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: sean
 */

#include "btree/btree_map.h"
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

template <class T>
class FPNode {
private:
    T item;
    int support;
    std::vector<FPNode> children;

public:
    FPNode(T item) {
        this->item = item;
        support = 1;
    }

    void insert(std::deque<T>& itemset) {
    	/**
    	 * Note on semantics
    	 * If you increment here, then each node will contain the sum of the
    	 * supports of its children plus itself.
    	 * If you instead increment in the base case, each node will contain
    	 * only the count of itemsets where it is the _last entry_!
    	 */
    	//support++;

    	if (itemset.empty()) {
    		// Base case
        	support++;
    	} else {
        	T next_item = itemset.front();
        	itemset.pop_front();

			for (FPNode& n : children) {
				if (n.item == item) {
					item.insert(itemset);
					return;
				}
			}
			// No items matched.
			children.emplace_back(item);
			children.
    	}
    }
};

/**
 * Higher order function running a function on every line in a stream.
 */
void eachLineOf(istream &input, std::function<void(std::string&)> f) {
	// For line in file
	for (std::string line; input >> line; input.good()) {

		f(line);
	}
}

/**
 * Higher order function running a function on every word in a stream.
 */
void eachWordOf(string& line, std::function<void(std::string&)> f) {
	// For item in line.split()
	std::istringstream line_get(line);
	for (std::string item; line_get >> item; line_get.good()) {
		f(line);
	}
}



/**
 * Find the frequent itemsets using the FP-growth algorithm
 *
 * The input file is named input_sets (not stdin because we need multiple runs)
 * It should be formatted with strings separated by spaces (no escapes),
 *   with one itemset per line
 * It will output counts (the first column) and itemsets, one per line.
 */
int main() {
    puts("Example");
    std::fstream example("example_input");

    btree::btree_map<string, int> hist;
    eachLineOf(cin, [&](string& line){
    	eachWordOf(line, [&](string& word) {
        	hist[word]++;
    	});
    });



    for (auto x = hist.begin(); x != hist.end(); ++x) {
    	std::cout << x->first << " -> " << x->second << endl;
    }



}




