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

void matrix::print_row(int row){
   
   for(int i = 0; i < 10; i++){
       std::cout << " " << value[row][i];
   }
      std::cout << std::endl;   
}

matrix::matrix(int filler){ //why is this input necessary?
  
   int i = 0; 
   int bin; 
   std::string line;  // space to take in one line
   std::ifstream input("input2.txt"); // input file
 
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
  
   /*
   for(int i = 0; i < 20; i++){
      for(int j = 0; j < 10; j++){
         value[i][j] = filler; 
      }
   }
   */
   
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
// identical read function from my Lab3 code since the input file has the same structure
/*
void read(matrix obj){

   int i = 0; 
   int bin; 
   std::string line;  // space to take in one line
   std::ifstream input("input.txt"); // input file
    
   while(getline(input, line)){ // runs through all lines
     std::cout << line << std::endl;
     std::stringstream digits(line); // makes an input from the string
     for(int j = 0; j < 10; j++){ // runs through all the values
        digits >> obj.value[i][j]; // puts the values in a place
        std::cout << obj.value[i][j] << std::endl; 
     }
     i++;  // moves forward one set 
   }
    
   input.close();  // close the file

}
*/


void print(matrix obj, int row, int bloops, int lloops, int index){ // this needs to be modified for the correct output
    
   std::ofstream output ("output.txt"); // opens output file
   
   output << "Linear Search took " << lloops << " loops" << std::endl; 
   for(int i = 0; i < 10; i++){
       output << obj.value[row][i] << " ";
   }
   output << std::endl;
   output << "Index: " << index << std::endl;
   output << "Binary Search took " << bloops << " loops" << std::endl;
   
     
   output.close();  // close the file
   
}


using namespace std; 

int main(){

  int searchrow; 
  int index; 
  int lsearchLoops = 0; 
  int bsearchLoops = 0; 
      
  matrix test(0);
    
  searchrow = test.linear_search(&lsearchLoops); 
  
  test.sort_row(searchrow); 
  
  index = test.binary_search(searchrow, &bsearchLoops);
  
  print(test, searchrow, bsearchLoops, lsearchLoops, index); 
   
  return 0; 
}
