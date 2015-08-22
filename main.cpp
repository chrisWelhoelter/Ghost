//
//  main.cpp
//  Ghost
//
//  Created by Chris Welhoelter on 8/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "trie.h"


int main(int argc, const char * argv[]) {
    
    std::string fileName = "words.txt";
    
    std::fstream fsIn;
    fsIn.open(fileName);
    if (!fsIn.is_open()){
        std::cout << "could not open " << fileName  << std::endl;
        exit(EXIT_FAILURE);
    }
    
    Trie dictionary;
    
    std::string curWord;
    size_t testCount = 0;
    while (!fsIn.eof()){
        fsIn >> curWord;
        dictionary.addEntry(curWord);
        testCount ++;
    }
    
    bool gameOver = false;
    std::string workingWord;
    std::string playerMove;
    char compMove;
    
    std::cout << "let's play ghost. you go first..." << std:: endl;
    
    std::cin >> playerMove;
    
    if (playerMove.length() != 1){
        std::cout << "please enter just one character" << std::endl;
    }
    
    if (playerMove[0] < 'A' || playerMove[0] > 'z'){
        std::cout << "make sure you choose a letter from a to z" << std:: endl;
    }
    
    dictionary.buildMoveMap(playerMove[0]);
    
    workingWord += playerMove;
    
    while (!gameOver){
        
        if (!dictionary.getNode(workingWord).moves.winningMovesWithDepth.empty()){
            size_t randomWinningIndex = rand() % dictionary.getNode(workingWord).moves.winningMovesWithDepth.size();
            compMove = dictionary.getNode(workingWord).moves.winningMovesWithDepth[randomWinningIndex].first + 'a';
            workingWord += compMove;
        }
        
        else if (!dictionary.getNode(workingWord).moves.otherMoves.empty()){
            size_t randomOtherIndex = rand() % dictionary.getNode(workingWord).moves.otherMoves.size();
            compMove = dictionary.getNode(workingWord).moves.otherMoves[randomOtherIndex] + 'a'; // this could be chosen relative to win/lose ratio
            workingWord += compMove;
        }
        
        else {
            size_t maxDepth = 0;
            for (size_t i = 0; i < dictionary.getNode(workingWord).moves.losingMovesWithDepth.size(); i++){
                if (dictionary.getNode(workingWord).moves.losingMovesWithDepth[i].second >= maxDepth){
                    compMove = dictionary.getNode(workingWord).moves.losingMovesWithDepth[i].first + 'a';
                }
            }
            workingWord += compMove;
            if (dictionary.isEntry(workingWord)){
                std::cout << "dang! you win!" << std::endl;
                std::cout << "i have to spell " << workingWord << std::endl;
                gameOver = true;
                break;
            }
        }
        
        std::cout << "i choose '" << compMove << "'" << std::endl;
        std::cout << "we have: " << workingWord << std::endl;
        std::cout << "your turn..." << std::endl;
        
        std::cin >> playerMove;
        
        if (playerMove.length() != 1){
            std::cout << "please enter just one character" << std::endl;
            continue;
        }
        
        if (playerMove[0] < 'A' || playerMove[0] > 'z'){
            std::cout << "make sure you choose a letter from a to z" << std:: endl;
            continue;
        }
        
        if (!dictionary.getNode(workingWord).isPrefix(playerMove)){
            std::cout << "there are no words that start with " << workingWord << playerMove << std::endl;
            std::cout << "i win! better luck next time." << std::endl;
            gameOver = true;
            break;
        }
        
        workingWord += playerMove;
        
        if (dictionary.isEntry(workingWord)){
            std::cout << "you spelled " << workingWord << std::endl;
            std::cout << "i win! better luck next time." << std::endl;
            gameOver = true;
        }

    }
    
    return 0;
}
