#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include "graph.h"

using namespace std;

void buildGraph(graph &g, const string &dictionaryFile);
bool isDoublet(const string &word1, const string &word2);
vector<string> solveDoublets(graph &g, const string &startWord, const string &endWord);
size_t getIndex(const graph &g, const string &word);
string getWord(const graph &g, size_t index);

vector<string> knuthWords; // Static vector to store the words

void buildGraph(graph &g, const string &dictionaryFile)
{
  ifstream file(dictionaryFile);
  string word;
  while (file >> word)
  {
    knuthWords.push_back(word); // Store the words
    g.add_vertex();
  }

  for (size_t i = 0; i < knuthWords.size(); ++i)
  {
    for (size_t j = i + 1; j < knuthWords.size(); ++j)
    {
      if (isDoublet(knuthWords[i], knuthWords[j]))
      {
        g.add_edge(i, j);
      }
    }
  }
}

bool isDoublet(const string &word1, const string &word2)
{
  int diffCount = 0;
  for (size_t i = 0; i < word1.length(); ++i)
  {
    if (word1[i] != word2[i])
    {
      if (++diffCount > 1)
        return false;
    }
  }
  return diffCount == 1;
}

vector<string> solveDoublets(graph &g, const string &startWord, const string &endWord)
{
  size_t start = getIndex(g, startWord);
  size_t end = getIndex(g, endWord);

  vector<int> parent(g.n(), -1);
  queue<size_t> q;
  q.push(start);
  parent[start] = start;

  while (!q.empty())
  {
    size_t current = q.front();
    q.pop();

    if (current == end)
      break;

    for (auto neighbor : g.neighbors(current))
    {
      if (parent[neighbor] == -1)
      {
        parent[neighbor] = current;
        q.push(neighbor);
      }
    }
  }

  vector<string> path;
  if (parent[end] != -1)
  { // Check if a path was found
    for (size_t v = end; v != start; v = parent[v])
    {
      path.push_back(getWord(g, v));
    }
    path.push_back(startWord);

    reverse(path.begin(), path.end());
  }
  return path;
}

size_t getIndex(const graph &g, const string &word)
{
  auto it = find(knuthWords.begin(), knuthWords.end(), word);
  if (it != knuthWords.end())
  {
    return distance(knuthWords.begin(), it);
  }
  return g.n(); // Return an invalid index if word is not found
}

string getWord(const graph &g, size_t index)
{
  if (index < g.n())
  {
    return knuthWords[index];
  }
  return ""; // Return an empty string for invalid index
}

int main()
{
  const vector<string> puzzles = {
      "black white",
      "tears smile",
      "small giant",
      "stone money",
      "angel devil",
      "amino right",
      "amigo signs"};

  graph g;
  buildGraph(g, "knuth.txt");

  for (const auto &puzzle : puzzles)
  {
    istringstream iss(puzzle);
    string startWord, endWord;
    iss >> startWord >> endWord;

    cout << "Puzzle: " << startWord << " -> " << endWord << endl;

    vector<string> path = solveDoublets(g, startWord, endWord);

    if (!path.empty())
    {
      cout << "Solution: ";
      for (const auto &word : path)
      {
        cout << word << " ";
      }
      cout << endl;
    }
    else
    {
      cout << "No solution found." << endl;
    }
    cout << endl;
  }

  return 0;
}
