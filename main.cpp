//P Hanbury and J Kang
//Algorithms
//Project5a

#include <iostream>
#include <fstream>
#include "maze.h"
#include "graph.h"

int main()
{
   try
   {
      ifstream fin;
	  ofstream fout;

      // Read the maze from the file.
      string fileName = "maze1.txt";
      
      fin.open(fileName.c_str());
	  fout.open("graph.txt");
      if (!fin)
      {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g;
      m.mapMazeToGraph(g);

      fout << g << endl;
   }
}
