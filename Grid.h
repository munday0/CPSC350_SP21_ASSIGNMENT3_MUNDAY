/*
Stephanie Munday and Cecilia Marie Abrahamsson
2343625 and 2347542
smunday@chapman.edu and abrahamsson@chapman.edu
CPSC-350-08
Assignment 3
*/

//Header file for Grid

#ifndef GRID_H
#define GRID_H

#include <string>
#include <iostream>
using namespace std;

class Grid{
private:
  int m_row;
  int m_column;
  char m_char;
  int m_totalRows;
  string m_mode;
public:
  int rows = 0;
  int cols = 0;

  Grid();
  Grid(int row, int column, char currChar, string mode, int totalRows);
  ~Grid();
  char** grid1;
  char** grid2;
  char** grid3;

  char** generations[3] = {nullptr}; 

  //GETTERS
  int getRow();
  int getColumn();
  char getChar();
  int getTotalRows();
  string getMode();

  //SETTERS
  void setRow(int row);
  void setColumn(int column);
  void setChar(char currChar);
  void setTotalRows(int totalRows);
  void setMode(string mode);

  //finds the neighbors for a position in the grid for 3 modes
  int findNeighbors(char** grid, string mode, int row, int column, int numRows, int numColumns);

  //finds the average neighbors for a position in the grid over the number of available generations up to 3
  double findAvgNeighbors(int currentGen, int totalRows, int totalCols);

  //determines the next generation by calling findAvgNeighbors() and making comparisons
  char findBirthDeath(int currentGen, int totalRows, int totalCols);

  //generates grids 2 and 3
  void generateArray(int totalRows, int totalCols);

  //generates grid 1
  void generateArray1(int totalRows, int totalCols);

  //checks if grid is empty - all '-'
  bool empty(char** grid,int totalRows, int totalCols);

  //checks if grid is oscillating - grid0 = grid2 || grid1 == grid0 || grid2 == grid1
  bool oscillating(char*** generations,int totalRows, int totalCols, int currentGen);

  //checks if 3 most recent grids are stable - the same
  bool stable(char*** generations,int totalRows, int totalCols);

};

#endif
