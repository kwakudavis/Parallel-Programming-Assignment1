//============================================================================
// Name        : dama0001-Assignment1.cpp
// Author      : Davis Poku Amankwa
// Version     :
// Copyright   : Your copyright notice
// Description : Serial Implementation of Zhang Suen Thinning Algorithm in C++, Ansi-style
//============================================================================




#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include "jbutil.h"


using namespace std;








//check if one of a pixel's north neighbors is white
bool isNorthWhite(vector<vector<int> > &array, int i, int j){


   // If Pixel is on the north edge, return false

   if(  (i-1)<0 ){
     return false;
   }else{

    //check if the north pixel is White
    if( array[i-1][j] ==0){

              return true;
      }

    //Don't update vector if condition does not Apply

    return false;

   }

}


//check if one of a pixel's south neighbors is white
bool isSouthWhite(vector<vector<int> > &array, int i, int j, int rows){

    //check if we are not on the last row

    if( (i+1)>=rows ){

       return false;
    }else{

      if(array[i+1][j] == 0){
        return true;
      }{
      return false;
    }

    }

}


bool isEastWhite(vector<vector<int> > &array, int i, int j, int columns){


    //check if the pixel is not on the right edge
    if((j+1)>=columns){

      return false;

    }else{
       if (array[i][j+1]==0){

        return true;
      }
      return false;
    }



}


bool isWestWhite(vector<vector<int> > &array, int i, int j,int columns){


   //check if pixel is not on the left knowledge
   if((j-1)<0){
     return false;
   }else{

       if(array[i][j-1]==0){

         return true;
       }

       return false;
   }




}





//Returns the number of black neighbors
int countBlackneighborsHelper(vector<vector<int> > &array, int i, int j,int rows,int columns){


    //Black pixel counter
    int blackPixCounter=0;

    //If north is not white, then its black, increase black neighbor pixel counter
    if(!isNorthWhite(array,i,j)){
      blackPixCounter++;
    }

    //If south is black,increase pixel neighbor counter
    if(!isSouthWhite(array,i,j,rows)){
      blackPixCounter++;
    }


    //If east is black,increase pixel neighbor counter
    if(!isEastWhite(array,i,j,columns)){
      blackPixCounter++;
    }


    //If west is black,increase pixel neighbor counter
    if(!isWestWhite(array,i,j,columns)){
      blackPixCounter++;
    }


    return blackPixCounter;

}



//Checks if at least one of the North, East, or South neighbors is white
 bool atLeastOneOfNorthEastSouthIsWhiteHelper(vector<vector<int> > &array, int i,int j,int rows, int columns){

    return isNorthWhite(array,i,j)  || isSouthWhite(array,i,j,rows)  || isEastWhite(array,i,j,columns);
 }



 //Checks if at least one of the  East, South,West neighbors is white
bool atLeastOneOfEastSouthWestIsWhiteHelper(vector<vector<int> > &array, int i,int j,int rows, int columns){

    return isWestWhite(array,i,j,columns) || isSouthWhite(array,i,j,rows)  || isEastWhite(array,i,j,columns);
 }



 //Checks if at least one of the  North, East,West neighbors is white
 bool atLeastOneOfNorthEastWestIsWhiteHelper(vector<vector<int> > &array, int i,int j, int columns){


    return isNorthWhite(array,i,j) || isWestWhite(array,i,j,columns) || isEastWhite(array,i,j,columns);
 }



 //Checks if at least one of the  North, South,West neighbors is white
bool atLeastOneOfNorthSouthWestIsWhiteHelper(vector<vector<int> > &array, int i,int j, int rows, int columns){


    return isNorthWhite(array,i,j) || isWestWhite(array,i,j,columns) || isSouthWhite(array,i,j,rows);
}







//check if the minimum transisition across neighbhors is one

bool minimumTransitionOfOne(vector<vector<int> > &array, int i, int j,int rows,int columns){

    //Pixel and north neighbor aren't both white or black
    if( (array[i][j] == 1 &&  (isNorthWhite(array,i,j)))  ||  (array[i][j] == 0 &&  (isNorthWhite(array,i,j))) ){
        return false;
    }


    //Pixel and south neighbor aren't both white or black

  if( (array[i][j] == 1 &&  (isSouthWhite(array,i,j,rows)))  ||  (array[i][j] == 0 &&  (isSouthWhite(array,i,j,rows))) ){
      return false;
  }



    //Pixel and east neighbor aren't both white or black


  if( (array[i][j] == 1 &&  (isEastWhite(array,i,j,columns)))  ||  (array[i][j] == 0 &&  (isEastWhite(array,i,j,columns))) ){
      return false;
  }




    //Pixel and West neighbor aren't both white or black


    if( (array[i][j] == 1 &&  (isWestWhite(array,i,j,columns)))  ||  (array[i][j] == 0 &&  (isWestWhite(array,i,j,columns))) ){
        return false;
    }



    return true;
}

















//Executes Zhang Suen Thinning Algorithm on each pixel
int ZhangSuenThinningAlgorithm( vector<vector<int> > &array, int rows, int columns){

    cout <<" The Output is "<<endl;
    bool state = true;
    while(state){

     for (int i = 0; i < rows; i++){
                for (int j  = 0; j < columns; j++)  {



                 //Iteration 1, to check if pixel matches condition to be thinned

                 //If the pixel is black    and        if the number of black neighbors is between 2 and 6 given that it has eight neighbors                                                                    and     if the pixel is black    and     if at least one of the north,east and south neighbors is white         and     if at east one of the east, south and west neighbors is white
                 if ( (array[i][j] == 1 )    &&  (2<= countBlackneighborsHelper(array, i,j,rows, columns) && countBlackneighborsHelper(array, i,j,rows,columns)<=6 )         &&        (array[i][j] == 1)       &&            (atLeastOneOfNorthEastSouthIsWhiteHelper(array, i,j,rows,columns))           &&                (atLeastOneOfEastSouthWestIsWhiteHelper(array, i,j, rows,columns)) && minimumTransitionOfOne(array, i,j, rows,columns) ){
                    array[i][j] = 0;
                     state =true;

                 }



                }

        }



          //Iteration 2, to check if pixel matches condition to be thinned


               for (int i = 0; i < rows; i++){
                          for (int j  = 0; j < columns; j++)  {


                            //If the pixel is black      and        if the number of black neighbors is between 2 and 6  if the number of black neighbors is between 2 and 6 given that it has eight neighbors                                                    and      if the pixel is black         and         if at least one of the north,east and south neighbors is white       and           if at east one of the east, south and west neighbors is white and a minimum transition of 1
                           if(  (array[i][j] == 1 )           &&               (2<= countBlackneighborsHelper(array, i,j,rows, columns) && countBlackneighborsHelper(array, i,j,rows,columns)<=6 )         &&              (array[i][j] == 1)     &&                    (atLeastOneOfNorthEastWestIsWhiteHelper(array, i,j,columns))       &&                   (atLeastOneOfNorthSouthWestIsWhiteHelper(array, i,j, rows,columns)) && minimumTransitionOfOne(array, i,j, rows,columns)      )    {
                             array[i][j] = 0;
                             state = true;

                           }
                             state = false;



                            }

                        }

}


    return 0;

}



int printRestults(vector<vector<int> > &array, int rows, int columns,string filename){


       ofstream myfile;
       myfile.open (filename+"Results");




       //Displaying pixel values
        for (int i = 0; i < rows; i++){
                for (int j  = 0; j < columns; j++)  {
                   cout<< array[i][j]<<" ";
                   myfile<< array[i][j]<<" ";
                }
                cout <<endl;
                myfile << endl;

        }

        myfile.close();
        return 0;
}


bool isZeroOrOne(string word){
    if( ! (word.compare("0") || word.compare("1"))){
        return false;
    }

    return true;
}



bool isDigit(const string s){
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);

}




//Main Program
int main(int argc, char *argv[]){


        //Request file name to be passed
        if(argc < 2){
            cout << "Enter a filename and reload" <<endl;
            return 0;
        }


        //Read filename
        string Filename = argv[1];

        //Create a file read stream
        ifstream File (Filename);




        //Return error message if file could not be opened

        if(!File.is_open()){
            cout<<"File not found"<<endl;
            return 0;
        }


        //Read first line, which should contain number of rows and columns.
        string Line;
        getline (File,Line);


        //Read first string in line
        istringstream iss(Line);


        //Get number of rows
        string word;
        iss >> word;

        //Initialization of row and column variables
        size_t rows = 0;
        size_t columns = 0;


        //check validity of word
        if(!isDigit(word)){
            cout << "Row value is not a number"<<endl;
            return 0;
        }
        rows = stoi(word);



        //Get number of columns
        iss >> word;
        if(!isDigit(word)){
            cout << "Column value is not a number"<<endl;
            return 0;
        }
        columns = stoi(word);

      //  cout<<"number of columns:";
    //    cout<<columns<<endl;

    //    cout<<"number of Rows:";
    //    cout<<rows<<endl;

        //Initialization of vector of vectors to hold pixel values
        vector <vector <int> > arr(rows, vector<int>(columns));

        //Get remaining lines

        int rowCounter = 0;
        int columnCounter = 0;

        //while there are still more lines to read get words
        while(File.eof() != true){
            getline(File,Line);
            istringstream iss(Line);

                while(iss >> word){




                    //Return error message if a non digit is read

                  //  cout<<word;

                    if(!isZeroOrOne(word)){
                        cout<<"Invalid number detected in input"<<endl;
                        return 0;
                    }

                    //Convert to string and store value
                    arr[rowCounter][columnCounter] = stoi(word);
                    columnCounter++;


                  }

            //       cout<<"columnCounter:"<<endl;
              //     cout<<columnCounter<<endl;

            //       cout<<"Moving to next Row"<<endl;
                    //Raise error if number of columns read does not match column number input
                    if(columnCounter != columns){
                        cout << " Column value does not match number of columns read"<<endl;
                       return 0;
                    }

                    //Reset Column counter
                    columnCounter = 0;


                    rowCounter++;


      }

           //Raise error if number of rows read does not match column number input
        if(rowCounter != rows ){
                cout << "Row value do noes not match number of rows read" <<endl;
                return 0;
        }







//Start Timer

double time = jbutil::gettime();
        //Applying thinning algorithm on each pixel value
       ZhangSuenThinningAlgorithm(arr, rows, columns);


//Stop timer

time = jbutil::gettime() - time;
       //Display results and store in file
       printRestults(arr,rows, columns,Filename);

       cout<<"Time taken is:"<<time<<"s"<<endl;





       return 1;

}
