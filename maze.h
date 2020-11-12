#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include "stack.cpp"


using namespace std;
struct Cell
{
public:
    Cell(int Xcoor, int Ycoor, bool up = true, bool down = true, bool left = true, bool right = true, bool isVisited = false)
    {
        this->u = up;
        this->d = down;
        this->l = left;
        this->r = right;
        this->isVisited = isVisited;
        this->x = Xcoor;
        this->y = Ycoor;
        this->checkPath = false;
        this->next = nullptr;
    }
    bool u, d, l, r, isVisited, checkPath;
    int x, y;
    Cell *next;
};
class maze
{
private:
    int RowNum, ColNum;
    string ID;
    vector<vector<Cell>> matrix;
    int Random();
    vector<int> RandomGenerator();
public:
    void MazeGenerator();
    void PathFinder(int Xa, int Ya, int Xb, int Yb);
    maze(int RowNum, int ColNum, string ID);
    ~maze();
};
#endif
