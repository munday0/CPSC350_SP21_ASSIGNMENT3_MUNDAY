/*
Stephanie Munday and Cecilia Marie Abrahamsson
2343625 and 2347542
smunday@chapman.edu and abrahamsson@chapman.edu
CPSC-350-08
Assignment 3
*/

//Cpp file for Game

#include "Game.h"
#include "Grid.h"
#include <ctime>
#include <cstdlib>
#include <unistd.h>

Game::Game(){
}

Game::~Game(){
}
int Game::getTotalRows(){
  return m_totalRows;
}
int Game::getTotalCols(){
  return m_totalCols;
}
void Game::setTotalRows(int totalRows){
  m_totalRows = totalRows;
}
void Game::setTotalCols(int totalCols){
  m_totalCols = totalCols;
}
//Methods
//starts the game logic
void Game::startGame(){
  Grid grid;
  string gridType;
  string runMode;
  string endingType;
  string fileName;
  int rows;
  int cols;
  int count = 0;
  double density;
  string outfile;
  bool checkEmpty = false;
  bool checkStable = false;
  bool checkOscillating = false;
  ofstream writeFile;

  //begin prompting user
  cout << "Do you want to generate a random grid (r) or do you want to provide a grid (p)? " << endl;
  cin >> gridType;

  //account for invalid input
  if(gridType != "r" && gridType != "p"){
    cout << "Invalid grid type please try again" << endl;
    string testGrid;
    cin >> testGrid;
    while(testGrid != "p" && testGrid != "r"){
      cout << "Invalid grid type please try again" << endl;
      cin >> testGrid;
    }
    gridType = testGrid;
  }
  //if choose random grid configuration
  if(gridType == "r"){
    cout << "Amount of rows: " << endl;
    cin >> rows;
    setTotalRows(rows); //set rows
    cout << "Amount of columns: " << endl;
    cin >> cols;
    setTotalCols(cols); //set cols
    cout << "Population density: " << endl;
    cin >> density;

    grid.generateArray(getTotalRows(), getTotalCols()); //generate array of given dimensions
    grid.grid1 = randRun(rows, cols, density); //populates array with given density
    grid.generations[0] = grid.grid1; //stores grid in generation[0]

  }
  //if choose to enter a file
  else if(gridType == "p"){
    grid.generateArray(getTotalRows(), getTotalCols()); //generate array of given dimensions
    grid.grid1 = fileRun(fileName);
    cout << getTotalCols() << endl;
    for(int i = 0; i < getTotalRows(); ++i){
       for(int k = 0; k < getTotalCols(); ++k){
         cout << grid.grid1[i][k];
       }
       cout << "" << endl;
     }
     cout << "" << endl;
    grid.generations[0] = grid.grid1;
  }

  //asks the user which mode they would like to run in
  cout << "Would you like to run in classic, doughnut, or mirror mode" << endl;
  cin >> runMode;
  //accouts for invalid input
  if(runMode != "classic" && runMode != "doughnut" && runMode != "mirror"){
    cout << "Invalid mode type please try again (classic, doughnut, or mirror)" << endl;
    cin >> runMode;
    while(runMode != "classic" && runMode != "doughnut" && runMode != "mirror"){
      cout << "Invalid mode type please try again (classic, doughnut, or mirror)" << endl;
      cin >> runMode;
    }
  }
  //sets the mode of the grid
  grid.setMode(runMode);
  //asks the user if they want to print to the console, pause/hit enter between rounds
  cout << "Do you want the game printed in console (print), paused between rounds (pause), or press enter between rounds (enter)" << endl;
  cin >> endingType;

  //accounts for invalid input
  if(endingType != "print" && endingType != "enter" && endingType != "pause"){
    cout << "Invalid grid type please try again" << endl;
    string testType;
    cin >> testType;
    while(testType != "enter" && testType != "pause" && testType != "print"){
      cout << "Invalid grid type please try again" << endl;
      cin >> testType;
    }
    endingType = testType;
  }

  //for printing to file
  if(endingType == "print"){
    cout << "please enter the file you would like to print to: " << endl;
    cin >> outfile;
    writeFile.open(outfile);
    while(!writeFile.is_open()){
      cout << "please enter the file you would like to print to: " << endl;
      cin >> outfile;
      writeFile.open(outfile);
    }

  }

  //while not empty, stable, or oscillating
  while(!checkEmpty && !checkStable && !checkOscillating){
    if(endingType == "print"){
      writeFile << currentGen << endl;//print to file
    }
    else{
      cout << currentGen << endl;
    }

    for (int i = 0; i < getTotalRows(); ++i) {
      for (int j = 0; j < getTotalCols(); ++j) {
        grid.setRow(i);
        grid.setColumn(j);

        if ((currentGen%3) == 0) { //first gen +3
          grid.setChar(grid.generations[0][i][j]);
          grid.grid2[i][j] = grid.findBirthDeath(currentGen, getTotalRows(), getTotalCols());
        }
        else if ((currentGen%3) == 1) { //second gen +3
          grid.setChar(grid.generations[1][i][j]);
          grid.grid3[i][j] = grid.findBirthDeath(currentGen, getTotalRows(), getTotalCols());
        }
        else if ((currentGen%3) == 2) { //third gen +3
          grid.setChar(grid.generations[2][i][j]);
          grid.grid1[i][j] = grid.findBirthDeath(currentGen, getTotalRows(), getTotalCols());

        }
        else {

        }
      }
    }

    if ((currentGen%3) == 0) { //first gen +3
      grid.generations[1] = grid.grid2;
      count = 1;
      //printing out loops
      for(int i = 0; i < getTotalRows(); ++i){
        for(int k = 0; k < getTotalCols(); ++k){
          if(endingType == "print"){
            writeFile << grid.grid1[i][k];
          }
          else{
            cout << grid.grid1[i][k];
          }
        }
        if(endingType == "print"){
          writeFile << "" << endl;;
        }
        else{
          cout << "" << endl;
        }
      }
      if(endingType == "print"){
        writeFile << "" << endl;
      }
      else{
        cout << "" << endl;
      }
    }
    else if ((currentGen%3) == 1) { //second gen +3
      grid.generations[2] = grid.grid3;
      count = 2;
      //printing out loops
      for(int i = 0; i < getTotalRows(); ++i){
        for(int k = 0; k < getTotalCols(); ++k){
          if(endingType == "print"){
            writeFile << grid.grid2[i][k];
          }
          else{
            cout << grid.grid2[i][k];
          }
        }
        if(endingType == "print"){
          writeFile << "" << endl;;
        }
        else{
          cout << "" << endl;
        }
      }
      if(endingType == "print"){
        writeFile << "" << endl;
      }
      else{
        cout << "" << endl;
      }
    }
    else if ((currentGen%3) == 2) { //third gen +3
      grid.generations[0] = grid.grid1;
      count = 0;
      //printing out loops
      for(int i = 0; i < getTotalRows(); ++i){
        for(int k = 0; k < getTotalCols(); ++k){
          if(endingType == "print"){
            writeFile << grid.grid3[i][k];
          }
          else{
            cout << grid.grid3[i][k];
          }
        }
        if(endingType == "print"){
          writeFile << "" << endl;;
        }
        else{
          cout << "" << endl;
        }
      }
      if(endingType == "print"){
        writeFile << "" << endl;
      }
      else{
        cout << "" << endl;
      }
    }

    //checking run condtitions
    checkEmpty = grid.empty(grid.generations[count], getTotalRows(), getTotalCols());
    checkStable = grid.stable(grid.generations, getTotalRows(), getTotalCols());
    checkOscillating = grid.oscillating(grid.generations, getTotalRows(), getTotalCols(), currentGen);

    if(endingType == "print"){}
    else if(endingType == "pause"){
      sleep(3); //mac OS equivalent of system pause
    }
    else if(endingType == "enter"){
      if (currentGen == 0) {
        cin.ignore();
      }
      if(!checkEmpty && !checkStable && !checkOscillating){
        cout << "Please press enter to continue" << endl;
        while(cin.get() != '\n'){//check while the user has not pressed enter
          cout << "Please press enter to continue" << endl;
        }
      }
      else{
        cout << "Please press enter to exit" << endl;
        while(cin.get() != '\n'){//check while the user has not pressed enter
          cout << "Please press enter to exit" << endl;
        }
      }
    }
    else{
      cout << "Invalid finishing type" << endl;
    }
    ++currentGen; //updating currentGen
  }//end of while

  if(endingType == "print"){
    writeFile.close();
    //write current generation to file w/o overwriteing it
  }
  grid.setTotalRows(getTotalRows());
}

//takes in the dimensions and the population density (between 0 and 1) to run the game with a random grid configuration
char** Game::randRun(int rows, int cols, double density){
  Grid grid;

  setTotalCols(cols);//setting the total number of columns
  setTotalRows(rows); //setting the total number of rows

  grid.generateArray1(getTotalRows(), getTotalCols()); //creating the 2D array

  srand(static_cast<unsigned int>(clock()));

  //looping through the 2D array
  for(int i = 0; i < rows; ++i){
    for(int k = 0; k < cols; ++k){
      if( rand() / (double(RAND_MAX) + 1.0) <= density){ //if the random number is less then the users density put a X
        grid.grid1[i][k] = 'X';
      }
      else{ //if random number is higher then the users density put a -
        grid.grid1[i][k] = '-';
      }
    }
  }
   return grid.grid1; //returns random grid
}

//takes in the name of the map file containing dimensions and placements of - and X to run the game with the inputted grid configuration
char** Game::fileRun(string fileName){
  Grid grid;
  cout << "Enter text file: " << endl; //prompting user for filename
  cin >> fileName; //storing filename
  ifstream readFile;
  string numRows;
  string numCols;
  int rows;
  int cols;

  readFile.open(fileName);
  if (readFile.is_open()) {
    readFile >> numRows; //takes first line of file as numRows
    rows = stoi(numRows); //converts to int
    setTotalRows(rows); //seting the total number of rows

    readFile >> numCols; //takes second line of file as numCols
    cols = stoi(numCols); //converts to int
    setTotalCols(cols); //setting the total number of columns

    grid.generateArray1(getTotalRows(), getTotalCols()); //generates the first array

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        readFile >> grid.grid1[i][j];
      }
    }
    readFile.close(); //closing file
    return grid.grid1; //returning the file grid
  }
  else { //if file could not be opened it tells the user
    cout << "File not open" << endl;
  }
}
