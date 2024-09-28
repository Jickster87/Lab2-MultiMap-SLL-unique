#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    head = nullptr;
    totalElems = 0;
}


void MultiMap::add(TKey c, TValue v) {
    Node * nomad = head;
    //if key already exists, push value
    while (nomad != nullptr) {
        if (nomad->key == c) {
            nomad->values.push_back(v);
            totalElems++;
            return;
        }
        nomad = nomad->next;
    }
    //key doesnt exist
    std::vector<TValue> vals = {v}; // Create a vector containing only value v
    Node * newNode = new Node(c, vals); // Pass the key and the vector to the const
    newNode->next = head;
    head = newNode;
    totalElems++;
}


bool MultiMap::remove(TKey c, TValue v) {
    if (head == nullptr) {
        return false;
    }
    Node * nomad = head;
    Node * prev = nullptr;
    while (nomad != nullptr) {
        if (nomad->key == c) {
            //GPT
            for (size_t i = 0; i < nomad->values.size(); i++) {
                if (nomad->values[i] == v) {
                    // Value found, remove it
                    nomad->values.erase(nomad->values.begin() + i);

                    // If vector is empty, remove the entire node
                    if (nomad->values.empty()) {
                        if (prev == nullptr) { // If it's the head node
                            head = nomad->next;
                        } else {
                            prev->next = nomad->next;
                        }
                        delete nomad;
                    }
                    totalElems--;
                    return true;
                }
            }
            //end GPT
        }
        prev = nomad;
        nomad = nomad->next;
    }
	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
    Node * nomad = head;
    while (nomad != nullptr) {
        if (nomad->key == c) {
            return nomad->values;
        }
        nomad = nomad->next;
    }
	return vector<TValue>();
}


int MultiMap::size() const {
    return totalElems;
}


bool MultiMap::isEmpty() const {
    return totalElems == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}

