#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

  ifstream puzzleFile;
  puzzleFile.open("puzzle.txt"); // Change the location of the puzzle from here
  ifstream wordsFile;
  wordsFile.open("words.txt");
  unordered_set<string> wordSet;
  vector<string> dictionary;
  string newWord;
  string tempChar;
  int width;
  std::cout << "Enter the length/width of the puzzle" << '\n';
  std::cin >> width;
  int diagNum = width * 2;
  char charArr[width][width];
  char bDiagonal[width][width];
  string horizontalForward[width];
  string horizontalBackward[width];
  string verticalForward[width];
  string verticalBackward[width];
  string diagonalForward[diagNum];
  string diagonalBackward[diagNum];
  string reverseDiagonalForward[diagNum];
  string reverseDiagonalBackward[diagNum];

  for (int i = 0; i < width; i++)
  { // read in puzzle from file
    for (int j = 0; j < width; j++)
    {
      puzzleFile >> charArr[j][i];
    }
  }

  for (int i = 0; i < width; i++)
  { // horizontal forwards
    for (int j = 0; j < width; j++)
    {
      tempChar = charArr[j][i];
      horizontalForward[i] += tempChar;
    }
  }

  for (int i = 0; i < width; i++)
  { // horizontal backwards
    for (int j = width - 1; j >= 0; j--)
    {
      tempChar = charArr[j][i];
      horizontalBackward[i] += tempChar;
    }
  }

  for (int i = 0; i < width; i++)
  { // vertical forwards
    for (int j = 0; j < width; j++)
    {
      tempChar = charArr[i][j];
      verticalForward[i] += tempChar;
    }
  }

  for (int i = 0; i < width; i++)
  { // vertical backwards
    for (int j = width - 1; j >= 0; j--)
    {
      tempChar = charArr[i][j];
      verticalBackward[i] += tempChar;
    }
  }

  for (int i = 1; i < width; i++)
  { // get diagonal top left to bottom right
    for (int j = 0; j + i < width; j++)
    {
      tempChar = charArr[j + i][j];
      diagonalForward[i + width] += tempChar;
    }
  }
  for (int i = 0; i < width; i++)
  { // get diagonal top left to bottom right
    for (int j = 0; j + i < width; j++)
    {
      tempChar = charArr[j][j + i];
      diagonalForward[i] += tempChar;
    }
  }

  for (int i = 0; i < diagNum; i++)
  { // get diagonal bottom right to top left
    tempChar = diagonalForward[i];
    reverse(tempChar.begin(), tempChar.end());
    diagonalBackward[i] = tempChar;
  }

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < width; j++)
    {
      tempChar = horizontalBackward[i];
      bDiagonal[i][j] = tempChar[j];
    }
  }

  for (int i = 1; i < width; i++)
  { // get diagonal top right to bottom left
    for (int j = 0; j + i < width; j++)
    {
      tempChar = bDiagonal[j + i][j];
      reverseDiagonalForward[i + width] += tempChar;
    }
  }
  for (int i = 0; i < width; i++)
  { // get diagonal top right to bottom left
    for (int j = 0; j + i < width; j++)
    {
      tempChar = bDiagonal[j][j + i];
      reverseDiagonalForward[i] += tempChar;
    }
  }

  for (int i = 0; i < diagNum; i++)
  { // get diagonal bottom left to top right
    tempChar = reverseDiagonalForward[i];
    reverse(tempChar.begin(), tempChar.end());
    reverseDiagonalBackward[i] = tempChar;
  }

  while (wordsFile >> newWord)
  { // read in dictionary
    if (newWord.length() > 5)
      dictionary.push_back(newWord);
  }

  for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
  { // checking/printing
    for (int j = 0; j < width; j++)
    { // find horiz/vertical matches
      if (horizontalForward[j].find(*it) != string::npos)
      { // print any horizontal forward matches
        tempChar = *it;
        std::cout << *it << " from (" << horizontalForward[j].find(*it) << "," << j << ") to (" << horizontalForward[j].find(*it) + tempChar.length() << "," << j << ")" << '\n';
      }
      if (horizontalBackward[j].find(*it) != string::npos)
      { // print any horizontal backward matches
        tempChar = *it;
        std::cout << *it << " from (" << width - horizontalBackward[j].find(*it) << "," << j << ") to (" << width - horizontalBackward[j].find(*it) - tempChar.length() << "," << j << ")" << '\n';
      }
      if (verticalForward[j].find(*it) != string::npos)
      { // print any vertical forward matches
        tempChar = *it;
        std::cout << *it << " from (" << j << "," << verticalForward[j].find(*it) << ") to (" << j << "," << verticalForward[j].find(*it) + tempChar.length() << ")" << '\n';
      }
      if (verticalBackward[j].find(*it) != string::npos)
      { // print any vertical backward matches
        tempChar = *it;
        std::cout << *it << " from (" << j << "," << width - verticalBackward[j].find(*it) << ") to (" << j << "," << width - verticalBackward[j].find(*it) - tempChar.length() << ")" << '\n';
      }
    }

    for (int j = 0; j < diagNum; j++)
    { // find diagonal matches
      if (diagonalForward[j].find(*it) != string::npos)
      { // print any diagonal forward matches
        tempChar = *it;
        std::cout << "diag 1" << '\n';
        std::cout << *it << " from (" << j << "," << diagonalForward[j].find(*it) << ") to (" << j + tempChar.length() << "," << diagonalForward[j].find(*it) + tempChar.length() << ")" << '\n';
      }
      if (diagonalBackward[j].find(*it) != string::npos)
      { // print any diagonal backward matches
        tempChar = *it;
        std::cout << "diag 2" << '\n';
        std::cout << *it << " from (" << diagNum - diagonalBackward[j].find(*it) - width - 1 << "," << j - tempChar.length() - 2 << ") to (" << diagNum - diagonalBackward[j].find(*it) - tempChar.length() - width << "," << j - 2 << ")" << '\n';
      }
      if (reverseDiagonalForward[j].find(*it) != string::npos)
      { // print any reverse diagonal forward matches
        tempChar = *it;
        std::cout << "diag 3" << '\n';
        std::cout << *it << " from (" << j << "," << reverseDiagonalForward[j].find(*it) << ") to (" << j + tempChar.length() << "," << reverseDiagonalForward[j].find(*it) + tempChar.length() << ")" << '\n';
      }
      if (reverseDiagonalBackward[j].find(*it) != string::npos)
      { // print any reverse diagonal backward matches
        tempChar = *it;
        std::cout << "diag 4" << '\n';
        std::cout << *it << " from (" << diagNum - reverseDiagonalBackward[j].find(*it) - width - 1 << "," << j - tempChar.length() - 2 << ") to (" << diagNum - reverseDiagonalBackward[j].find(*it) - tempChar.length() - width << "," << j - 2 << ")" << '\n';
      }
    }
  }
  return 0;
}
