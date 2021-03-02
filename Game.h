/*
Stephanie Munday and Cecilia Marie Abrahamsson
2343625 and 2347542
smunday@chapman.edu and abrahamsson@chapman.edu
CPSC-350-08
Assignment 3
*/

//Header file for Game

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include "Grid.h"
using namespace std;

class Game{
private:
  int m_totalRows;
  int m_totalCols;
public:
  Game();
  ~Game();
  int getTotalRows();
  int getTotalCols();
  void setTotalRows(int totalRows);
  void setTotalCols(int totalCols);
  int rows = 0;
  int cols = 0;
  int currentGen = 0;

  //starts the game logic
  void startGame();
  
  //takes in the dimensions and the population density (between 0 and 1) to run the game with a random grid configuration
  char** randRun(int rows, int cols, double density);

  //takes in the name of the map file containing dimensions and placements of - and X to run the game with the inputted grid configuration
  char** fileRun(string fileName);
};

#endif
