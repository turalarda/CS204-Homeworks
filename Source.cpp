#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Stack.h"

//#include <thread>         // std::this_thread::sleep_for
//#include <chrono> 
//#include <iomanip>
//#include <windows.h>


using namespace std;

struct MazePart
{
	Point p;
	int w;
	char visited;
	bool branch;
	MazePart()
	{	
		branch=0;
		visited=0;
	}

};


int row,col;
MazePart** Maze;
pair<int,int> start;



void print_table(Stack & st,int num_rows, int num_cols)
{ 
	
	int i, j; 


	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < row; i++) 
	{ 
		for (j= 0 ; j< col ; j++) {
			/*if(Maze[i][j].w==0)
				cout << setw(1)<<char(248) <<" "; 
			if(Maze[i][j].w==1)
				cout << setw(1)<< char(178) <<" "; 
			if(Maze[i][j].w==99){
				SetConsoleTextAttribute(hConsole, 12);
				cout << setw(1)<<char(254) <<" "; 
				SetConsoleTextAttribute(hConsole, 15);
			}*/

			/*cout<<Maze[i][j].branch<<" ";*/
		}
		cout << endl; 
	} 
}

int findWay(int x,int y)
{
	if(x==1 && y== 0)
		cout<<"";
	//  00 bottom 
	//	01 left 
	//	10 right 
	//	11 up

	if (x==0 && y==0)	//top left
	{
		if(Maze[x+1][y].w==0)
			return 0;
		if(Maze[x][y+1].w==0)
			return 2;

	}

	if (x==row-1 && y==0)	// top right
	{
		if(Maze[x+1][y].w==0)
			return 0;
		if ((Maze[x][y-1].w) == 0)
			return 1;
	}	
	if (x==col-1 && y==0)	// bottom left
	{
		if(Maze[x-1][y].w==0)
			return 3;
		if ((Maze[x][y-1].w) == 0)
			return 1;

	}
	if (x==row-1 && y==col-1)	// bottom right
	{
		if(Maze[x-1][y].w==0)
			return 3;
		if(Maze[x][y+1].w==0)
			return 2;
	}
	if (x==0 && y!=0 && y!=col-1)	//up
	{
		if ((Maze[x][y-1].w) == 0)
			return 1;
		if(Maze[x][y+1].w==0)
			return 2;
		if(Maze[x+1][y].w==0)
			return 0;
	}
	if (x==row-1 && y!=0 && y!=col-1)	//bottom
	{
		if ((Maze[x][y-1].w) == 0)
			return 1;
		if(Maze[x][y+1].w==0)
			return 2;
		if(Maze[x-1][y].w==0)
			return 3;
	}
	if (y==col-1 && x!=row-1 && x!=0)	//right
	{
		if (Maze[x-1][y].w==0)
			return 3;
		if(Maze[x+1][y].w==0)
			return 0;
		if ((Maze[x][y-1].w) == 0)
			return 1;
	}
	if (y==0)	//left
	{
		if (Maze[x-1][y].w==0)
			return 3;
		if(Maze[x+1][y].w==0)
			return 0;
		if(Maze[x][y+1].w==0)
			return 2;
	}

	if ( y!=col-1 && y!=0 && x!=row-1 && x!=0)
	{

	
	if ((Maze[x][y-1].w) == 0)
		return 1;
	else if(Maze[x][y+1].w==0)
		return 2;
	else if(Maze[x-1][y].w==0)
		return 3;
	else if(Maze[x+1][y].w==0)
		return 0;
	}
	return 4;	//stuck..
}

bool isBranch(int x,int y)
{
	unsigned char branch=0;	//0000

	/*if(x==1 && y==5)
		cout<<"";*/


	if(Maze[x][y].w==1)
		return false;

	if (x==0 && y==0)	//top left
	{
		if (Maze[x][y+1].w==0)
			branch|=4;
		else
			branch|=1;

	}

	if (x==col-1 && y==0)	// top right
	{
		if (Maze[x][y+1].w==0)
			branch|=2;
		else
			branch|=1;
	}	
	if (x==0 && y==row-1)	// bottom left
	{
		if (Maze[x][y-1].w==0)
			branch|=2;
		else
			branch|=8;

	}
	if (x==col-1 && y==row-1)	// bottom right
	{
		if (Maze[x][y-1].w==0)
			branch|=4;
		else
			branch|=8;
	}
	if (x==0 && y!=0)	//up
	{
		if (Maze[x][y-1].w==0)
			branch|=2;
		else if(Maze[x][y+1].w==0)
			branch|=4;
		else if(Maze[x+1][y].w==0)
			branch|=1;
	}
	if (x==col-1 && y!=0 && y!=row-1)	//bottom
	{
		if (Maze[x][y-1].w==0)
			branch|=2;
		else if(Maze[x][y+1].w==0)
			branch|=4;
		else
			branch|=8;
	}
	if (y==row-1 && x!=0)	//right
	{
		if (Maze[x-1][y].w==0)
			branch|=8;
		else if(Maze[x+1][y].w==0)
			branch|=1;
		else
			branch|=2;
	}
	if (y==0 && x!=0 && x!=row-1)	//left
	{
		if (Maze[x-1][y].w==0)
			branch|=8;
		else if(Maze[x+1][y].w==0)
			branch|=1;
		else
			branch|=4;
	}

	if (x>0 && x < row-1 && y > 0 && y < col-1)
	{


		if ((Maze[x][y-1].w) == 0)
			branch|=2;
		if(Maze[x][y+1].w==0)
			branch|=4;
		if(Maze[x-1][y].w==0)
			branch|=8;
		if(Maze[x+1][y].w==0)
			branch|=1;
	}

	int counter=0;
	for (int i = 0; i < 4; i++)
	{
		if(branch&1)
			counter++;
		branch=branch>>1;
	}

	return counter>2;
}
bool goBack(Stack& st,int & e1,int & e2)
{
	MazePart m;
	Point p;
	m.branch=0;
	while(true)
	{
		//std::this_thread::sleep_for (std::chrono::milliseconds(50));
		if (start.first==e1 && start.second==e2)
		{
			return 1;	//finish
		}

		if (m.branch!=1){
			Maze[p.x][p.y].w=1;
			st>>p;
			e1=p.x;
			e2=p.y;
		}
		else
			return 0;	//do not finish


		m.branch=Maze[p.x][p.y].branch;
		//print_table(st,row,col);
	}
	
}
void branches()
{
	for (int a = 0; a < row; a++)
	{
		for (int j= 0 ; j< col; j++)
		{
			Maze[a][j].branch=isBranch(a,j);
		}
	}
}
void go(Stack & st ,int & e1,int & e2)
{
	int direction=findWay(e1,e2);
	Maze[e1][e2].w=99;
	Maze[e1][e2].visited=true;
	Point p;
	p.x=e1;
	p.y=e2;
	st<<p;

	if(direction==0)
		e1++;
	else if (direction==1)
		e2--;
	else if (direction==2)
		e2++;
	else if (direction==3)
		e1--;
	else{
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		cout<<"Stuck.."<<endl;
		system("pause");
	}
	Maze[e1][e2].w=99;
	Maze[e1][e2].visited=true;
};
int main()
{
	string str="";
	ifstream fin;
	cout<<"Welcome to the homework \"A Great Day for Freedom\".\nPlease enter a file name for the maze: ";

	cin>>str;
	fin.open(str.c_str());
	if (fin.is_open())
	{

	



	int e1=0,e2=0;
	fin>>col>>row>>e2>>e1;
	start.first=e1;
	start.second=e2;
	MazePart m;
	int i=0,j=0;
	char c;

	Stack st;
	Stack* possibilites = new Stack[100];

	Maze=new MazePart* [row];
	for (int i = 0; i<row; i++)
	{
		Maze[i] = new MazePart [col];
	}
	for (int a = 0; a < row; a++)
	{
		for (int j= 0 ; j< col; j++)
		{

			fin >> m.w;
			/*	static int id=1;
			if (m.w==1)
			{
			m.w=id;
			id++;
			}*/
			m.p.x=a;
			m.p.y=j;
			Maze[a][j]=m;

		}
	}

	branches();
	//print_table(st,row,col);
	bool status;
	int w=0;	//ways-w
	do
	{
		while (findWay(e1,e2)!=4)
		{
			
			go(st,e1,e2);
			//print_table(st,row,col);
			
			//std::this_thread::sleep_for (std::chrono::milliseconds(50));
		}
	
		if (e1==0 || e1==row-1 || e2==0 || e2==col-1)
		{
			Point p;
			p.x=e1;
			p.y=e2;
			st<<p;
			possibilites[w]=st;
			w++;
		}
			
		
		goBack(st,e1,e2);
		
		

		
	}while(!st.isEmpty());
	
	int min=100000;
	int index=0;
	for (int i = 0; i < w; i++)
	{
		
		int cand=possibilites[i].getcap();
		if (cand<min)
		{
			index=i;
			min=cand;
		}
	}

	
	cout<<possibilites[index];


	}
	else
	{
		cout<<"File name is incorrect. Program exiting..."<<endl;
	}


	return 0;
}