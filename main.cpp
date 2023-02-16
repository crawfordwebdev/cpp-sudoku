/***********************************************************************
* Program:
*    Project Sudoku Game
* Author:
*    Michael Crawford
* Summary: 
*    This is a simple Sudoku game program. It will read a given sudoku board file,
*    show options the user has, display the board and then allow the user
*    to select from the options. The choices are to display the instructions
*    again, display the board, edit one square, show the possible values for
*    a square and to save and quit.
*
************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#define FILELENGTH 256
using namespace std;

void promptFileName(char fileName[FILELENGTH]);
void readFile(char fileName[FILELENGTH], int board[9][9]);
void displayInstructions();
void displayBoard(int board[9][9]);
void interact(int board[9][9]);
void computeValues(int board[9][9]);
bool checkValue(int board[9][9], int square[2], int userValue);
void editSquare(int board[9][9]);
void getSquare(int board[9][9], int square[2], char inputSquare[3],
               bool &validSquare);
void saveAndQuit(int board[9][9]);

/**********************************************************************
* Main will call the other functions necessary to work the program.
***********************************************************************/
int main()
{
   char fileName[FILELENGTH];
   int board[9][9];

   promptFileName(fileName);
   readFile(fileName, board);
   displayInstructions();
   displayBoard(board);

   interact(board);
   
   return 0;
}

/**********************************************************************
 * This function will prompt the user for the board filename.
 ***********************************************************************/
void promptFileName(char fileName[FILELENGTH])
{
   cout << "Where is your board located? ";
   cin.getline(fileName, 256);
}

/**********************************************************************
 * This function will read the board and write it into an array.
 ***********************************************************************/
void readFile(char fileName[FILELENGTH], int board[9][9])
{
   ifstream fin(fileName);
   if (fin.fail()) // In case there is a fail.
   {
      cout << "Failed to read filename: "
           << fileName
           << endl;
      return;
   }

   for (int iboardRow = 0; iboardRow < 9; iboardRow++)
   {
      for (int iboardCol = 0; iboardCol < 9; iboardCol++)
      {
         fin >> board[iboardRow][iboardCol];

         if (fin.fail()) // In case there is a fail.
         {
            cout << "Failed to read filename: "
                 << fileName
                 << endl;
            return;
         }
      }
   }
   fin.close();
}

/**********************************************************************
 * This function will display the user's options.
 ***********************************************************************/
void displayInstructions()
{
   cout << "Options:\n"
        << "   " << "?" << "  " "Show these instructions\n"
        << "   " << "D" << "  " "Display the board\n"
        << "   " << "E" << "  " "Edit one square\n"
        << "   " << "S" << "  " "Show the possible values for a square\n"
        << "   " << "Q" << "  " "Save and Quit\n"
        << endl;
}

/**********************************************************************
 * This function will display the board.
 ***********************************************************************/
void displayBoard(int board[9][9])
{

   cout << "   " << "A B C D E F G H I\n";

   for (int iboardRow = 0; iboardRow < 9; iboardRow++)
   {
      cout << (iboardRow + 1) << "  ";
            
      for (int iboardCol = 0; iboardCol < 9; iboardCol++)
      {
         if (board[iboardRow][iboardCol] == 0)
         {
            cout << " ";
         }
         else
         {
            cout << board[iboardRow][iboardCol];
         }

         if ( (iboardCol + 1) % 3 == 0 && (iboardCol + 1) != 9)
         {
            cout << "|";
         }
         else
         {
            if ( (iboardCol + 1) != 9)
               cout << " ";
         }
      }

      if ( (iboardRow + 1) % 3 == 0 && (iboardRow + 1) != 9 )
      {
         cout << endl
              << "   "
              << "-----+-----+-----";
      }
      cout << endl;
   }
}

/**********************************************************************
 * This function will take the user's input and then call the appropriate
 * function.
 ***********************************************************************/
void interact(int board[9][9])
{
   char userInput;
   bool quit = false;
   
   do      
   {
      char userInput;
      cout << "\n> ";
      cin >> userInput;
      cin.ignore();
      
      switch (userInput)
      {
         case '?':
            displayInstructions();
            break;
         case 'D':
         case 'd':
            displayBoard(board);
            break;
         case 'E':
         case 'e':
            editSquare(board);
            break;
         case 'S':
         case 's':
            computeValues(board);
            break;
         case 'Q':
         case 'q':
            saveAndQuit(board);
            quit = true;
            break;
         default:
            cout << "ERROR: Invalid command\n";
            break;
      }
   }

   while (quit != true);

}

/**********************************************************************
 * This function will compute the possible values of a given valid
 * position on the board.
 ***********************************************************************/
void computeValues(int board[9][9])
{
   int square[2];
   char inputSquare[2];
   int oneToNine[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   bool validSquare;

   getSquare(board, square, inputSquare, validSquare);
        
   if (validSquare == true)
   {
      assert(validSquare == true);

      cout << "The possible values for '" << inputSquare << "' are: ";

      // Logic to figure out possible values
      for (int i = 0; i < 9; i++)
      {         
         if ( board[square[0]][i] != 0)
         {
            oneToNine[board[square[0]][i]] = 0;
         }
         if (board[i][square[1]] != 0)
         {
            oneToNine[board[i][square[1]]] = 0;
         }
         else
         {
            for (int j = (square[0] / 3) * 3;
                 j < (square[0] / 3 ) * 3 + 3; j++)
            {
               for (int k = (square[1] / 3) * 3;
                    k < (square[1] / 3 ) * 3 + 3; k++)
               {
                  if (board[j][k] != 0)
                  {
                     oneToNine[board[j][k]] = 0;
                  }
               }
            }
         }         
      }

      bool start = true;
      for (int i = 0; i <= 9; i++)
      {
         if (oneToNine[i] != 0 )
         {
            if (start != true)
            {
               cout << ", ";                
               cout << oneToNine[i];
            }

            else
            {
               cout << oneToNine[i];
               start = false;
            }
         }
      }
      cout << endl;
   }      
}

/**********************************************************************
 * This function will modify a given value on the board if it doesn't
 * already contain a value.
 ***********************************************************************/
void editSquare(int board[9][9])
{
   int square[2];
   char inputSquare[2];
   int userValue = 0;
   bool validSquare;
   bool validValue;

   getSquare(board, square, inputSquare, validSquare);

   if (validSquare == true)
   {
      assert(validSquare == true);
      
      cout << "What is the value at '" << inputSquare << "': ";
      cin >> userValue;
      cin.ignore();

      if ( userValue < 0 || userValue > 9 )
      {
         cout << "ERROR: Value '" << userValue << "' in square '"
              << inputSquare << "' is invalid"
              << endl;
      }
      else
      {
         validValue = checkValue(board, square, userValue);
          
          
         if (validValue == true)          
            board[square[0]][square[1]] = userValue;

         else
         {
            cout << "ERROR: Value '" << userValue << "' in square '"
                 << inputSquare << "' is invalid"
                 << endl;
         }
      }
   }

}

/**********************************************************************
 * This function will check the value to see if it's a valid one to use.
 ***********************************************************************/
bool checkValue(int board[9][9], int square[2], int userValue)
{
   if (userValue <= 9 && userValue > 0)
   {
      for (int i = 0; i < 9; i++)
      {
         // Checking Rows and Columns
         if ( board[square[0]][i] == userValue ||
              ( board[i][square[1]] == userValue ) )
         {
            return false;
         }
      }      
      // Checking Squares Rows
      for (int j = (square[0] / 3) * 3;
           j < (square[0] / 3 ) * 3 + 3; j++)
      {
            
         // Checking Squares Columns
         for (int k = (square[1] / 3) * 3;
              k < (square[1] / 3 ) * 3 + 3; k++)
         {
            if (board[j][k] == userValue)
            {
               return false;
            }
         }
      }
   
   
      return true;
   }   
}

/**********************************************************************
 * This function will convert the user's input into a valid array
 * format. It will also check to see if the user's input is a valid
 * square to modify.
 ***********************************************************************/
void getSquare(int board[9][9], int square[2], char inputSquare[2],
               bool &validSquare)
{
   cout << "What are the coordinates of the square: ";
   cin >> inputSquare;
   
   if ( isalpha(inputSquare[0]) && isdigit(inputSquare[1]) )
   {
      square[1] = (int)toupper(inputSquare[0]) - 65;
      square[0] = atoi(&inputSquare[1]) - 1;
   }

   else if ( isalpha(inputSquare[1]) && isdigit(inputSquare[0]))
   {
      square[1] = (int)toupper(inputSquare[1]) - 65;
      square[0] = atoi(&inputSquare[0]) - 1;
   }

   if ( (isalpha(inputSquare[0]) && isalpha(inputSquare[1]) ) ||
        isdigit(inputSquare[0]) && isdigit(inputSquare[1]) )
   {
      cout << "ERROR: Square '" << inputSquare[0]
           << inputSquare[1] << "' is invalid"
           << endl;
      validSquare = false;
   }

   else if ( board[square[0]][square[1]] != 0)
   {
      cout << "ERROR: Square '" << inputSquare[0]
           << inputSquare[1] << "' is filled"
           << endl;
      validSquare = false;
   }

   else if ( square[0] > 9 || square[1] > 9
             || square[0] < 0 || square[1] < 0)
   {
      cout << "ERROR: Square '" << inputSquare[0]
           << inputSquare[1] << "' is invalid"
           << endl;
      validSquare = false;
   }

   else if ( square[0] < 9 && square[1] < 9
             && square[0] >= 0 && square[1] >= 0)
   {
      validSquare = true;
   }
   else
      validSquare = true;
    
}

/**********************************************************************
 * This function will save the board to specified file.
 ***********************************************************************/
void saveAndQuit(int board[9][9])
{
   char newFileName[FILELENGTH];
   
   cout << "What file would you like to write your board to: ";
   cin.getline(newFileName, 256);

   ofstream fout;
   fout.open(newFileName);

   if (fout.fail())
   {
      cout << "Failed to read filename: "
           << newFileName
           << endl;
      return;
   }


   for (int iboardRow = 0; iboardRow < 9; iboardRow++)
   {
      for (int iboardCol = 0; iboardCol < 9; iboardCol++)
      {
         fout << board[iboardRow][iboardCol] << " ";
      }
      fout << endl;
   }
   fout.close();
   cout << "Board written successfully"
        << endl;
}
