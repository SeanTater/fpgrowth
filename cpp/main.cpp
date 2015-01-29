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
class FPTree {
private:
    T item;
    int support;
    vector<FPTree> children;

    /**
     * Insert into a subtree. Doesn't sort the itemset.
     * But it does modify the input parameter.
     */
    void insert_(deque<T>& itemset) {
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

			for (FPTree& t : children) {
				if (t.item == item) {
					t.insert_(itemset);
					return;
				}
			}
			// No items matched.
			children.emplace_back(item);
			children.back().insert_(itemset);
		}
    }

    /**
     * Query the subtree, modifying the itemset in the process
     */
    int query_(deque<T>& itemset) {
    	if (itemset.empty()) {
    		return support;
    	} else {
			T next_item = itemset.front();
			itemset.pop_front();

    		for (FPTree t : children) {
    			if (t.item == item) {
    				return t.query_(itemset);
    			}
    		}
    	}
    	// This is impossible but it keeps gcc quiet.
    	return -1;
    }

    string show(function<string(T)> show_item) {
    	string x = "(" + show_item(item);
    	for (FPTree t : children) {
    		x.append(t.show(show_item));
    	}
    	x.append(")");
    	return x;
    }

public:
    FPTree(T item) {
        this->item = item;
        support = 1;
    }

    /**
     * Copy the original itemset, but don't in the recursion
     */
    void insert(deque<T> itemset) {
    	sort(itemset.begin(), itemset.end());
    	insert_(itemset);
    }

    /**
     * Copy the query itemset, but don't when recursing
     */
    int query(deque<T> itemset) {
    	sort(itemset.begin(), itemset.end());
    	return query_(itemset);
    }
};

/**
 * Higher order function running a function on every line in a stream.
 */
void eachLineOf(istream &input, function<void(string&)> f) {
	// For line in file
	for (std::string line; input >> line; input.good()) {

		f(line);
	}
}

/**
 * Higher order function running a function on every word in a stream.
 */
void eachWordOf(string& line, function<void(string&)> f) {
	// For item in line.split()
	istringstream line_get(line);
	for (string item; line_get >> item; line_get.good()) {
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
    fstream example("example_input");

    /*btree::btree_map<string, int> hist;
    eachLineOf(example, [&](string& line){
    	eachWordOf(line, [&](string& word) {
        	hist[word]++;
    	});
    });*/

    /*for (auto x = hist.begin(); x != hist.end(); ++x) {
    	std::cout << x->first << " -> " << x->second << endl;
    }*/

    FPTree<string> root("");
    eachLineOf(cin, [&](string& line){
    	deque<string> itemset;
    	eachWordOf(line, [&](string& word){
    		itemset.push_back(word);
    	});

    	root.insert(itemset);
    });
    deque<string> query_set {"ogreism","Ramesses","squinac","respectably", "scenic"};
    cout << query_set.front();
    cout << root.query(query_set) << endl;

    cout << root.show([&](string& t){return t});
}




