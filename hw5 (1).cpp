#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Laser{
    bool on;
    char direction;
    int x_coord;
    int y_coord;
};

void inputFile(ifstream &file){
  string filename;
  cout << "Enter the file name: ";
  cin >> filename;

  file.open(filename);
}

void turnRight(Laser &l1){
  if(l1.direction == 'E')
    l1.direction = 'S';
  else if(l1.direction == 'S')
    l1.direction = 'W';
  else if(l1.direction == 'W')
    l1.direction = 'N';
  else if(l1.direction == 'N')
    l1.direction = 'E';
}

void turnLeft(Laser &l1){
  if(l1.direction == 'E')
    l1.direction = 'N';
  else if(l1.direction == 'N')
    l1.direction = 'W';
  else if(l1.direction == 'W')
    l1.direction = 'S';
  else if(l1.direction == 'S')
    l1.direction = 'E';
}

void expandGrid(const Laser &l1, vector<vector<char>> &grid){
  if(l1.y_coord >= grid.size()){
    grid.resize(l1.y_coord + 1, vector<char>(grid[0].size(), ' '));
  }
  if(l1.x_coord >= grid[0].size()){
    for(int i = 0; i < grid.size(); i++)
      grid[i].resize(l1.x_coord + 1, ' ');
  }
  
}

void printGrid(vector<vector<char>> &grid){ 
  // prints array
  for(int i = 0; i < grid.size(); i++){
      for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] != '*')
              grid[i][j] = ' ';
        
            cout << grid[i][j];
          }
    cout << endl;
  }
}




int main()
{  
  ifstream file;
  string filename;
  vector<vector<char>> grid(1, vector<char> (1));
  string command;
  int move;

  //fills array with empty spaces
  //for(int i = 0; i < grid.size(); i++){
      //for(int j = 0; j < grid[i].size(); j++){
        //    grid[i][j] = ' ';
          //}
  //}

  inputFile(file);

  if(!file.is_open()){
    cout << "Error, cannot open file.";
    return 1;
  }

  //define laser properties
  Laser l1;
  l1.on = false;
  l1.direction = 'E';
  l1.x_coord = 0;
  l1.y_coord = 0;

  //parses input file
  if(!file.fail()){
    while(getline(file, command)){
      if(command == "" || command[0] == 'I' || command[0] == 'O' || command[0] == 'R' || command[0] == 'L'){
      if(command == ""){}
      
      else if(command[0] == 'I'){
        l1.on = true;
        grid[l1.y_coord][l1.x_coord] = '*';
        //cout << "on"<<endl;
      }
      else if(command[0] == 'O'){
        l1.on = false;
        //cout << "off" << endl;
      }

      else if(command[0] == 'R'){
        //cout << l1.direction << " turns right to ";
        turnRight(l1);
        //cout << l1.direction << endl;
      }
      else if(command[0] == 'L'){
        //cout << l1.direction << " turns left to ";
        turnLeft(l1);
        //cout << l1.direction << endl;
      } 
      }

      //moves laser and prints cuts
      else if(command[0] == 'A'){
        move = stoi(command.substr(2, command.length()-1));
        if(l1.on){
          for(int i = 0; i < move; i++){
            if(l1.direction == 'E'){
              l1.x_coord++;
              expandGrid(l1, grid);
              grid[l1.y_coord][l1.x_coord] = '*';
            }
            else if(l1.direction == 'W'){
              l1.x_coord--;
              expandGrid(l1, grid);
              grid[l1.y_coord][l1.x_coord] = '*';
            }
            else if(l1.direction == 'N'){
              l1.y_coord--;
              expandGrid(l1, grid);
              grid[l1.y_coord][l1.x_coord] = '*';
            }
            else if(l1.direction == 'S'){
              l1.y_coord++;
              expandGrid(l1, grid);
              grid[l1.y_coord][l1.x_coord] = '*';
            }
          }
          
        }
        else{ //moves laser without cutting
          for(int i = 0; i < move; i++){
            if(l1.direction == 'E'){
              l1.x_coord++;
              expandGrid(l1, grid);
            }
            else if(l1.direction == 'W'){
              l1.x_coord--;
              expandGrid(l1, grid);
            }
            else if(l1.direction == 'N'){
              l1.y_coord--;
              expandGrid(l1, grid);
            }
            else if(l1.direction == 'S'){
              l1.y_coord++;
              expandGrid(l1, grid);
            }
          }
          
        }
        
      }
      
      else{
        cout << "Encountered an Invalid command. Terminating." << endl;
        return 1;
          }
    }
    
  }
  
  printGrid(grid);
   
  file.close();
  
  return 0;
}
