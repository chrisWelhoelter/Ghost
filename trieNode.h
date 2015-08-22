//
//  trieNode.h
//  Ghost
//
//  Created by Chris Welhoelter on 8/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#ifndef __Ghost__trieNode__
#define __Ghost__trieNode__

#include <stdio.h>
#include <vector>
#include <utility> //for pair
#include <string>

struct MoveMap{
    std::vector<std::pair<size_t, size_t>> winningMovesWithDepth;
    std::vector<std::pair<size_t, size_t>> losingMovesWithDepth;
    std::vector<size_t> otherMoves;
};

class TrieNode{
public:
    bool isEndOfWord;
    std::vector<TrieNode*> nextLetters;
    MoveMap moves;
    
    TrieNode();
    void addEntry(std::string entry);
    bool isPrefix(std::string entry);
    bool isEntry(std::string entry);
    void buildMoveMap();
};

#endif /* defined(__Ghost__trieNode__) */
