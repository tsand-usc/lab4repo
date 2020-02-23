#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class matrix{
   
    public:
      matrix(int);
      int value[20][10];
      int linear_search(int *); 
      void sort_row(int); 
      int binary_search(int, int *);
      void print_row(int); 
      
};

matrix::matrix(int filler){ 
   
   // uses the same file reading code I wrote for the last lab
   int i = 0; 
   int bin; 
   std::string line;  // space to take in one line
   std::ifstream input("input.txt"); // input file
 
   while(getline(input, line)){ // runs through all lines
     //std::cout << line << std::endl;
     std::stringstream digits(line); // makes an input from the string
     for(int j = 0; j < 10; j++){ // runs through all the values
        digits >> value[i][j]; // puts the values in a place
        //std::cout << obj.value[i][j] << std::endl; 
     }
     i++;  // moves forward one set 
   }
    
   input.close();  // close the file
}

int matrix::linear_search(int *loops){ // adjust for this application
   
  for(int i = 1; i < 20; i++){                                      
     for(int j = 0; j < 10; j++){          //run through each element of the other set
        (*loops)++;
        if(value[0][0] == value[i][j]){  //check the value with the rest of the given set  
            return i; // if the value appears return true
        }
     }
  }
  return (-1); // if the value does no appear again, give return false
  
}


//==================BUBBLE SORT=========================
void matrix::sort_row(int row){ 

   bool swapped = false; 
   bool exit = false;
   int temp;  
   
   while(!exit){ // keep going til they are all ordered
      
      for(int i = 0; i < 9; i++){ // iterate through each value 
         if(value[row][i] > value[row][i+1]){ // if a value at a later location is smaller than an earlier one, swap them
            temp = value[row][i+1];
            value[row][i+1] = value[row][i];
            value[row][i] = temp; 
            swapped = true;  // mark that something was swapped
         }
         if((i == 8) && (swapped == false)){ // if it reaches the end and nothing was swapped it is over
            exit = true; 
         }else if((i == 8) && (swapped == true)){ // if something was swapped, reset flag and repeat
            swapped = false; 
         }
      }
   }
}

//=====================Binary Search========================

int matrix::binary_search(int row, int *loops){ // look over this 
   
  int top =  9; 
  int bottom = 0; 
  bool exit = false; 
  int searchLoc = (top - bottom)/2; 
  int goal = value[0][0];
  
  while(!exit){
     (*loops)++; 
     if(value[row][searchLoc] < goal){ // if the value is less than the search value
         
         bottom = searchLoc + 1; // adjust the bottom to just greater than the previous search location
          
         searchLoc = (top + bottom)/2; // new location is the average of the top and bottom
     
     }else if(value[row][searchLoc] > goal){ // if you are greater than the value
         
         top = searchLoc - 1; // make the top of the new array one less than the current location
         
         searchLoc = (top + bottom)/2; // reset the search location
     
     }else if(value[row][searchLoc] == goal){ // if the value is equal, return its location
         exit = true; 
         return searchLoc; 
     }
  }
}

//===================================================

void print(matrix obj, int row, int bloops, int lloops, int index){ 
    
   std::ofstream output ("output.txt"); // opens output file
   
   output << lloops << std::endl; // linear search loops
   for(int i = 0; i < 9; i++){ // the row
      
       output << obj.value[row][i] << ",";
   }
   output << obj.value[row][9] << std::endl; // last row element
   output << index << std::endl; // the index
   output << bloops << std::endl; // the number of binary search loops
   
     
   output.close();  // close the file
   
}


using namespace std; 

int main(){

  int searchrow; 
  int index; 
  int lsearchLoops = 0; 
  int bsearchLoops = 0; 
      
  matrix test(0); // creates array
    
  searchrow = test.linear_search(&lsearchLoops); // linear search, return the row
  
  test.sort_row(searchrow); // sort that row
  
  index = test.binary_search(searchrow, &bsearchLoops); // binary search that row, return that index
  
  print(test, searchrow, bsearchLoops, lsearchLoops, index); // print all this info
   
  return 0; 
}
