//
//  trie.cpp
//  Ghost
//
//  Created by Chris Welhoelter on 8/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#include "trie.h"

void Trie::addEntry(std::string entry){
    root.addEntry(entry);
}

bool Trie::isEntry(std::string entry){
    return root.isEntry(entry);
}

void Trie::buildMoveMap(char c){
    root.nextLetters[c - 'a']->buildMoveMap();
}

TrieNode Trie::getNode(std::string str){
    TrieNode ret = root;
    while (str != ""){
        ret = *ret.nextLetters[str[0] - 'a'];
        str = str.substr(1, -1);
    }
    return ret;
}