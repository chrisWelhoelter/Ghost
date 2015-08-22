//
//  trieNode.cpp
//  Ghost
//
//  Created by Chris Welhoelter on 8/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#include "trieNode.h"

TrieNode::TrieNode(){
    isEndOfWord = false;
    nextLetters = std::vector<TrieNode*>(26, nullptr);
}

void TrieNode::addEntry(std::string entry){
    if (entry.length() == 0){
        isEndOfWord = true;
        return;
    }
    else if (nextLetters[entry[0] - 'a'] == nullptr){
        nextLetters[entry[0] - 'a'] = new TrieNode;
        nextLetters[entry[0] - 'a']->addEntry(entry.substr(1, -1));
    }
    else {
        nextLetters[entry[0] - 'a']->addEntry(entry.substr(1, -1));
    }
}

bool TrieNode::isPrefix(std::string entry){
    if (nextLetters[entry[0] - 'a'] != nullptr){
        return true;
    }
    else {
        return false;
    }
}

bool TrieNode::isEntry(std::string entry){
    if (entry.length() == 0 && isEndOfWord == true){
        return true;
    }
    else if (entry.length() != 0 && isPrefix(entry)){
        return nextLetters[entry[0] - 'a']->isEntry(entry.substr(1, -1));
    }
    else {
        return false;
    }
}

void TrieNode::buildMoveMap(){
        
    for (size_t i = 0; i < 26; i++){
        if (nextLetters[i] != nullptr){
            if (nextLetters[i]->isEndOfWord == true){
                moves.losingMovesWithDepth.push_back(std::make_pair(i, 0));
                return;
            }
            
            nextLetters[i]->buildMoveMap();
            
            if (!nextLetters[i]->moves.losingMovesWithDepth.empty()
                && nextLetters[i]->moves.winningMovesWithDepth.empty())
            {
                size_t minDepth = -1; // max size_t
                for (size_t j = 0; j < nextLetters[i]->moves.losingMovesWithDepth.size(); j++){
                    if (nextLetters[i]->moves.losingMovesWithDepth[j].second < minDepth){
                        minDepth = nextLetters[i]->moves.losingMovesWithDepth[j].second;
                    }
                }
                moves.winningMovesWithDepth.push_back(std::make_pair(i, minDepth + 1));
            }
            else {
                size_t minDepth = -1; // max size_t
                for (size_t j = 0; j < nextLetters[i]->moves.winningMovesWithDepth.size(); j++){
                    if (nextLetters[i]->moves.winningMovesWithDepth[j].second < minDepth){
                        minDepth = nextLetters[i]->moves.winningMovesWithDepth[j].second;
                    }
                }
                moves.losingMovesWithDepth.push_back(std::make_pair(i, minDepth + 1));
            }
        }
    }
}






