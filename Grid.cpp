/*
Stephanie Munday and Cecilia Marie Abrahamsson
2343625 and 2347542
smunday@chapman.edu and abrahamsson@chapman.edu
CPSC-350-08
Assignment 3
*/

//Cpp file for Grid

#include "Grid.h"

Grid::Grid(){
  m_row = 0;
  m_column = 0;
  m_char = '-';
  m_totalRows = 0;
  m_mode = "Classic";
}

Grid::Grid(int row, int column, char currChar, string mode, int totalRows){
  m_row = row;
  m_column = column;
  m_char = currChar;
  m_totalRows = totalRows;
  m_mode = mode;
  grid1 = new char*[totalRows];
}

Grid::~Grid(){
  for(int i = 0; i < getTotalRows(); ++i){
    delete[] grid1[i];
    delete[] grid2[i];
    delete[] grid3[i];
  }
  for(int i = 0; i < 3; ++i){
    delete[] generations[i];
  }
}

//GETTERS
int Grid::getRow(){
  return m_row;
}
int Grid::getColumn(){
  return m_column;
}
char Grid::getChar(){
  return m_char;
}
int Grid::getTotalRows(){
  return m_totalRows;
}
string Grid::getMode(){
  return m_mode;
}

//SETTERS
void Grid::setRow(int row){
  m_row = row;
}
void Grid::setColumn(int column){
  m_column = column;
}
void Grid::setChar(char currChar){
  m_char = currChar;
}
void Grid::setTotalRows(int totalRows){
  m_totalRows = totalRows;
}
void Grid::setMode(string mode){
  m_mode = mode;
}

//finds the neighbors for a position in the grid for 3 modes
int Grid::findNeighbors(char** grid, string mode, int row, int column, int numRows, int numColumns){
  int numNeighbors = 0;

  //looking up if else statment
  if(row-1 >= 0){ //looking up if not out of bounds
    if(grid[row-1][column] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(grid[numRows-1][column] == 'X'){ //looking at last row but same column
      ++numNeighbors;
    }
  }
  else if(mode == "mirror"){
    if(grid[row][column] == 'X'){ //looking at it self
      ++numNeighbors;
    }
  }

  //looking down if else statment
  if(row+1 < numRows){ //looking down if not out of bounds
    if(grid[row+1][column] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(grid[0][column] == 'X'){ //looking at first row but same column
      ++numNeighbors;
    }
  }
  else if(mode == "mirror"){
    if(grid[row][column] == 'X'){ //looking at it self
      ++numNeighbors;
    }
  }

  //looking to the left if else statment
  if(column-1 >= 0){// looking left if not out of bounds
    if(grid[row][column-1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(grid[row][numColumns-1] == 'X'){ //looking at same row but last column
      ++numNeighbors;
    }
  }
  else if(mode == "mirror"){
    if(grid[row][column] == 'X'){ //looking at it self
      ++numNeighbors;
    }
  }

  //looking to the right if else statment
  if(column+1 < numColumns){ //looking right if not out of bounds
    if(grid[row][column+1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(grid[row][0] == 'X'){ //looking at same row but first column
      ++numNeighbors;
    }
  }
  else if(mode == "mirror"){
    if(grid[row][column] == 'X'){ //looking at it self
      ++numNeighbors;
    }
  }

  //looking left up if else statment
  if((row-1 >= 0) && (column-1 >= 0)){//looking left up if not out of bounds
    if(grid[row-1][column-1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(row-1 >= 0){ //if row is in bounds but columns is not
      if(grid[row-1][numColumns-1] == 'X'){//look up one row and end of columns
        ++numNeighbors;
      }
    }
    else if(column-1 >= 0){ //if column is not in bounds but row is
      if(grid[numRows-1][column-1] == 'X'){ //look at bottom of rows and left one column
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[numRows-1][numColumns-1] == 'X'){ //look at diagonal
        ++numNeighbors;
      }
    }
  }
  else if(mode == "mirror"){
    if(column-1 >= 0){ //if cloumn is in bounds but row is not
      if(grid[row][numColumns-1] == 'X'){ //look at neighbor to the left
        ++numNeighbors;
      }
    }
    else if(row-1 >= 0){ //if row is in bounds but column is not
      if(grid[row-1][column] == 'X'){ //look at neighbor that is above
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[row][column] == 'X'){ //look at it self
        ++numNeighbors;
      }
    }
  }

  // looking right up if else statment
  if((row-1 >= 0) && (column+1 < numColumns)){ //looking right up if in bounds
    if(grid[row-1][column+1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(row-1 >= 0){ // if row is in bounds but column is not
      if(grid[row-1][0] == 'X'){//look at row above and first column
        ++numNeighbors;
      }
    }
    else if(column+1 < numColumns){ //if row is not in bounds but column is
      if(grid[numRows-1][column+1] == 'X'){ //look at last row and next column
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[numRows-1][0] == 'X'){ //look at diagonal
        ++numNeighbors;
      }
    }
  }
  else if(mode == "mirror"){
    if(column+1 < numColumns){ //if columns is in bounds but rows is not
      if(grid[row][numColumns+1] == 'X'){ //look to right column
        ++numNeighbors;
      }
    }
    else if(row-1 >= 0){ //if column is not in bounds but rows is
      if(grid[numRows-1][column] == 'X'){ //look up one row
        ++numNeighbors;
      }
    }
    else{ //if its a column
      if(grid[row][column] == 'X'){ //look at it self
        ++numNeighbors;
      }
    }
  }

  //looking right down if else statment
  if((row+1 < numRows) && (column+1 < numColumns)){ //looking right down if in bounds
    if(grid[row+1][column+1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(row+1 < numRows){ //if rows is in bounds but cloumn is not
      if(grid[row+1][0] == 'X'){ //look down one row and at first column
        ++numNeighbors;
      }
    }
    else if(column+1 < numColumns){ //if row is not in bounds but column is
      if(grid[0][column+1] == 'X'){ //look at first row and left one column
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[0][0] == 'X'){ //look at diagonal
        ++numNeighbors;
      }
    }
  }
  else if(mode == "mirror"){
    if(column+1 < numColumns){ //if row is not in bounds but column is
      if(grid[row][column+1] == 'X'){ //look one column to the right
        ++numNeighbors;
      }
    }
    else if(row+1 < numRows){ //if rows is in bounds but column is not
      if(grid[row+1][column] == 'X'){ //look one row down
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[row][column] == 'X'){ //look at it self
        ++numNeighbors;
      }
    }
  }

  //looking left down if else statment
  if((row+1 < numRows) && (column-1 >= 0)){ //looking left down if in bounds
    if(grid[row+1][column-1] == 'X'){
      ++numNeighbors;
    }
  }
  else if(mode == "doughnut"){
    if(row+1 < numRows){ //if rows is in bounds but column is not
      if(grid[row+1][numColumns-1] == 'X'){ //look one row up and last column
        ++numNeighbors;
      }
    }
    else if(column+1 < numColumns){ //if rows is not in bounds but column is
      if(grid[0][column-1] == 'X'){ //look at first row and one column to the left
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[0][numColumns-1] == 'X'){ //look at diagonal
        ++numNeighbors;
      }
    }
  }
  else if(mode == "mirror"){
    if(column-1 >= 0){ //if rows is not in bounds but column is
      if(grid[row][column-1] == 'X'){ //look one column to the left
        ++numNeighbors;
      }
    }
    else if(row+1 < numRows){ //if row is in bounds but cloumn is not
      if(grid[row+1][column] == 'X'){ //look one row down
        ++numNeighbors;
      }
    }
    else{ //if its a corner
      if(grid[row][column] == 'X'){ //look at it self
        ++numNeighbors;
      }
    }
  }

  // initialize int to count neighbors
  // account for classic, donut, and mirror modes
  return numNeighbors;
}

//finds the average neighbors for a position in the grid over the number of available generations up to 3
double Grid::findAvgNeighbors(int currentGen, int totalRows, int totalCols){
  int totalNumNeighbors = 0;
  double avgNeighbors = 0.0;
  for (int f = 0; f < 3; ++f) { //for each grid in generations
    if (generations[f] != nullptr) {  //checks to see if the grid exists
      //if exists, finds neightbors for each cell in grid
      totalNumNeighbors += findNeighbors(generations[f], getMode(), getRow(), getColumn(), totalRows, totalCols);
    }
  }
  if(currentGen == 0){ //if we are on the first gen divide by 1
    avgNeighbors = (double)totalNumNeighbors / 1.0;
  }
  else if(currentGen == 1){ //if we are on the second gen divide by 2
    avgNeighbors = (double)totalNumNeighbors / 2.0;
  }
  else{ // gen 3 and up we divide by 3
    avgNeighbors = (double)totalNumNeighbors / 3.0;
  }
  return avgNeighbors; // return avg
}

//generates grid 1
void Grid::generateArray1(int totalRows, int totalCols){
  //creates the first array of generations
  grid1 = new char*[totalRows];

  for(int i = 0; i < totalRows; ++i){
    grid1[i] = new char[totalCols];
  }
}

//generates grids 2 and 3
void Grid::generateArray(int totalRows, int totalCols){
  //generates the second and third array of generations
  grid2 = new char*[totalRows];

  for(int i = 0; i < totalRows; ++i){
    grid2[i] = new char[totalCols];
  }

  grid3 = new char*[totalRows];

  for(int i = 0; i < totalRows; ++i){
    grid3[i] = new char[totalCols];
  }
//fills the array with - bc they are empty
  for(int i = 0; i < totalRows; ++i){
    for(int j = 0; j < totalCols; ++j){
      grid2[i][j] = '-';
      grid3[i][j] = '-';
    }
  }
}

//determines the next generation by calling findAvgNeighbors() and making comparisons
char Grid::findBirthDeath(int currentGen, int totalRows, int totalCols){
  double avgNeighbors = findAvgNeighbors(currentGen, totalRows, totalCols);

  if(avgNeighbors <= 1.50){ // if avgNeighbors < 1.5 --> -
    return '-';
  }
  else if(avgNeighbors <= 2.50){ // else if avgNeighbors <= 2.5 --> stays same
    return getChar(); //returns the same char
  }
  else if(avgNeighbors <= 3.50){ // else if avgNeighbors <= 3.5 --> X
    return 'X';
  }
  else{ // if avgNeighbors > 3.5 --> -
    return '-';
  }
}

//checks if grid is empty - all '-'
bool Grid::empty(char** grid, int totalRows, int totalCols){
  //checks every index for an X
  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalCols; ++j) {
      if (grid[i][j] == 'X') { //if X found its not empty
        return false;
      }
    }
  }
  //if no X is found its empty
  return true;
}

//checks if grid is oscillating - grid0 = grid2 || grid1 == grid0 || grid2 == grid1
bool Grid::oscillating(char*** generations, int totalRows, int totalCols, int currentGen){
  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalCols; ++j) {
      if(generations[2] == nullptr){ //if generation 3 doesn't exist it can't oscillate
        return false;
      }
      if(generations[2] != nullptr){ //checking to make sure generation 3 exists
        if ((currentGen%3) == 0) { //checking most current generation
          if (generations[0][i][j] != generations[2][i][j]) { //check if gen 0 and gen 2 are different
            return false; //if differs, doesn't oscillate
          }
        }
        if ((currentGen%3) == 1) { //checking most current generation
          if (generations[1][i][j] != generations[0][i][j]) { //check if gen 1 and gen 0 are different
            return false; //if differs, doesn't oscillate
          }
        }
        if ((currentGen%3) == 2) { //checking most current generation
          if (generations[2][i][j] != generations[1][i][j]) { //check if gen 2 and gen 1 are different
            return false; //if differs, doesn't oscillate
          }
        }
      }
    }
  }
  return true;
}

//checks if 3 most recent grids are stable - the same
bool Grid::stable(char*** generations, int totalRows, int totalCols){
  int counter = 1;
  for(int m = 0; m < 3; ++m){
    for (int i = 0; i < totalRows; ++i) {
      for (int j = 0; j < totalCols; ++j) {
        if (generations[m] != nullptr) { //check to make sure generation exists
          if(generations[m][i][j] != generations[counter][i][j]){ //if grids are different
            ++counter;
            return false; // not stable
          }
        }
      }
    }
  }
  return true;
}
