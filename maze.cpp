#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "maze.h"

using namespace std;

maze::maze(int Ccount, int Rcount, string mazeid)
{
	RowNum = Rcount;
	ColNum = Ccount;
	Cell temp(0, 0);
	this->matrix = vector<vector<Cell>>(RowNum, vector<Cell>(ColNum, temp));
	for (int i = 0; i < RowNum; i++)
	{
		for (int j = 0; j < ColNum; j++)
		{
			this->matrix[i][j] = Cell(j, i);
		}
	}
	ID = mazeid;
}

maze::~maze()
{
	this->matrix.clear();
}

int maze::Random()
{
	int toBeReturned = (rand()) % 4;
	return toBeReturned;
}

vector<int> maze::RandomGenerator()
{
	vector<int> vec;
	vec.push_back(0 + rand() % RowNum);    //y coordinate
	vec.push_back(0 + rand() % ColNum); //x coordinate
	return vec;
}

void maze::MazeGenerator()
{
	Stack<Cell*> Mystack = Stack<Cell*>();
	Mystack.push(&this->matrix[0][0]);
	this->matrix[0][0].isVisited = true;
	int CountofCells = (RowNum * ColNum) - 1;
	while (CountofCells != 0)
	{
		Cell* head = Mystack.top();
		int x = head->x;
		int y = head->y;
		int rand = this->Random();
		int Count = 3;
		while (Count != -1)
		{
			if (rand == 0 && y > 0)
			{
				if (matrix[y - 1][x].isVisited)
				{
					Count--;
					rand = (rand + 1) % 4;
				}
				else
				{
					y--;
					Mystack.push(&matrix[y][x]);    //If not already isVisited, push it to the stack.
					matrix[y][x].isVisited = true; //Mark it as isVisited.
					CountofCells--;
					matrix[y][x].u = false;     //Break the upper wall of our current cell
					matrix[y + 1][x].d = false; //Break the lower wall of our previous cell.
					break;
				}
			}
			else if (rand == 1 && x > 0)
			{
				if (matrix[y][x - 1].isVisited)
				{
					Count--;
					rand = (rand + 1) % 4;
				}
				else
				{
					x--;
					Mystack.push(&matrix[y][x]);
					matrix[y][x].isVisited = true;
					CountofCells--;
					matrix[y][x].r = false;
					matrix[y][x + 1].l = false;
					break;
				}
			}
			else if (rand == 2 && y < RowNum - 1)
			{
				if (matrix[y + 1][x].isVisited)
				{
					Count--;
					rand = (rand + 1) % 4;
				}
				else
				{
					y++;
					Mystack.push(&matrix[y][x]);
					matrix[y][x].isVisited = true;
					CountofCells--;
					matrix[y][x].d = false;
					matrix[y - 1][x].u = false;
					break;
				}
			}
			else if (rand == 3 && x < ColNum - 1)
			{
				if (matrix[y][x + 1].isVisited)
				{
					Count--;
					rand = (rand + 1) % 4;
				}
				else
				{
					x++;
					Mystack.push(&matrix[y][x]);
					matrix[y][x].isVisited = true;
					CountofCells--;
					matrix[y][x].l = false;
					matrix[y][x - 1].r = false;
					break;
				}
			}
			else
			{
				rand = (rand + 1) % 4;
				Count--;
			}
		}
		if (Count == -1)
		{
			Mystack.pop();
		}
	}
	ofstream print("maze" + ID + ".txt");
	string final = to_string(RowNum) + " " + to_string(ColNum) + "\n";

	final += "\n";
	print << final;
	print.close();
}

void maze::PathFinder(int Xa, int Ya, int Xb, int Yb)
{
	ofstream print("maze_" + this->ID + "_path_" + to_string(Xa) + "_" + to_string(Ya) + "_" + to_string(Xb) + "_" + to_string(Yb) + ".txt");
	Stack<Cell*> My2Stack = Stack<Cell*>();
	My2Stack.push(&matrix[Ya][Xa]);
	int x = My2Stack.top()->x, y = My2Stack.top()->y;
	My2Stack.top()->checkPath = true;
	while (x != Xb || y != Yb)
	{
		Cell* cell = My2Stack.top();
		x = cell->x;
		y = cell->y;
		int Next = this->Random();
		int Counter = 3;
		while (Counter != -1)
		{
			if (Next == 0 && !this->matrix[y][x].d)
			{
				y -= 1;
				if (matrix[y][x].checkPath)
				{
					y += 1;
					Counter--;
					Next = (Next + 1) % 4;
				}
				else
				{
					My2Stack.push(&matrix[y][x]);
					matrix[y][x].checkPath = true;
					break;
				}
			}
			else if (Next == 1 && !this->matrix[y][x].l)
			{
				x -= 1;
				if (matrix[y][x].checkPath)
				{
					x += 1;
					Counter--;
					Next = (Next + 1) % 4;
				}
				else
				{
					My2Stack.push(&matrix[y][x]);
					matrix[y][x].checkPath = true;
					break;
				}
			}
			else if (Next == 2 && !this->matrix[y][x].u)
			{
				y += 1;
				if (matrix[y][x].checkPath)
				{
					y -= 1;
					Counter--;
					Next = (Next + 1) % 4;
				}
				else
				{
					My2Stack.push(&matrix[y][x]);
					matrix[y][x].checkPath = true;
					break;
				}
			}
			else if (Next == 3 && !this->matrix[y][x].r)
			{
				x += 1;
				if (matrix[y][x].checkPath)
				{
					x -= 1;
					Counter--;
					Next = (Next + 1) % 4;
				}
				else
				{
					My2Stack.push(&matrix[y][x]);
					matrix[y][x].checkPath = true;
					break;
				}
			}
			else
			{
				Next = (Next + 1) % 4;
				Counter--;
			}
		}
		if (Counter == -1)
		{
			My2Stack.pop();
		}
	}
	string WriteFile = "";
	while (!My2Stack.isEmpty())
	{
		Cell* cell = My2Stack.top();
		WriteFile = (to_string(cell->x) + " " + to_string(cell->y) + '\n' + WriteFile);
		My2Stack.pop();
	}
	print << WriteFile;
}
