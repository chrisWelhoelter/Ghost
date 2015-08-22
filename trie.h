//
//  trie.h
//  Ghost
//
//  Created by Chris Welhoelter on 8/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#ifndef __Ghost__trie__
#define __Ghost__trie__

#include <stdio.h>
#include <vector>
#include <string>
#include "trieNode.h"

class Trie{
private:
    TrieNode root;
public:
    void addEntry(std::string entry);
    bool isPrefix(std::string entry);
    bool isEntry(std::string entry);
    void buildMoveMap(char c);
    TrieNode getNode(std::string str);
};

#endif /* defined(__Ghost__trie__) */
