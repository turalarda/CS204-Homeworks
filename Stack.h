#include <sstream>
#include <iostream>

using namespace std;

struct Point
{
	Point()
	{
		x=0;
		y=0;
	};
	Point(int x,int y):x(x),y(y)
	{

	}

	Point(const Point & a):x(a.x),y(a.y)
	{

	}

	int x,y;

	void print()
	{
		cout<<x<<"-"<<y<<endl;
	}

	const Point& operator=(const Point & c)
	{
		x=c.x;
		y=c.y;
		return *this;
	}

};

struct StackNode
{
	Point coor;
	StackNode *next;
};

class Stack
{
private:
	
	void pop(int &,int &);
	void push(int,int);
	int cap;
public:
	StackNode *top;
	Stack(void);
	~Stack()
	{
		StackNode* ptr=top;
		
		StackNode* toDelete;
		while (ptr!=NULL)
		{
			toDelete=ptr;
			ptr=ptr->next;
			delete toDelete;
		}
	
	}
	const Stack& operator<<(Point&);
	const Stack& operator>>(Point&);

	bool isEmpty(void) const;

	Stack(Stack & copy)
	{
		cap=copy.getcap();
		Stack temp;
		top=NULL;
		while (!copy.isEmpty())
		{
			Point p;
			copy.pop(p.x,p.y);
			temp.push(p.x,p.y);
		}

		

		while (!temp.isEmpty())
		{
			Point p;
			temp.pop(p.x,p.y);
			copy.push(p.x,p.y);

			StackNode *newNode;
			// Allocate a new node & store Num
			newNode = new StackNode;
			newNode->coor.x = p.x;
			newNode->coor.y = p.y;

			// If there are no nodes in the list
			// make newNode the first node
			if (isEmpty()){
				top = newNode;
				newNode->next = NULL;
			}
			else{	// Otherwise, insert NewNode before top
				newNode->next = top;
				top = newNode;
			}
		}
	}

	const Stack& operator=(Stack & copy)
	{
		Stack temp;
		cap=copy.getcap();
		while (!copy.isEmpty())
		{
			Point p;
			copy.pop(p.x,p.y);
			temp.push(p.x,p.y);
		}

		temp.reverse();

		while (!temp.isEmpty())
		{
			Point p;
			temp.pop(p.x,p.y);
			copy.push(p.x,p.y);

			StackNode *newNode;
			cap++;
			// Allocate a new node & store Num
			newNode = new StackNode;
			newNode->coor.x = p.x;
			newNode->coor.y = p.y;

			// If there are no nodes in the list
			// make newNode the first node
			if (isEmpty()){
				top = newNode;
				newNode->next = NULL;
			}
			else{	// Otherwise, insert NewNode before top
				newNode->next = top;
				top = newNode;
			}
		}
		return *this;
	}
	int getcap()
	{
		return cap;
	}
	void reverse()
	{

		Stack temp;
		while (!isEmpty())
		{
			Point p;
			pop(p.x,p.y);
			temp.push(p.x,p.y);
		}
		while (!temp.isEmpty())
		{
			Point p;
			temp.pop(p.x,p.y);
			push(p.x,p.y);
		}
	};
	friend void recursive(ostringstream& oss,StackNode* n)
	{
		if(!n)
			return;

		recursive(oss,n->next);
		oss<<n->coor.x<<","<<n->coor.y<<endl;
	}
	friend ostream& operator<<(ostream& os,Stack & a)
	{

		ostringstream oss;
		int l=a.getcap();
		oss<<"Printing the shortest exit path, with the length of "<<l/2<<"\n";

		recursive(oss,a.top);


		os<<oss.str();
		return os;
	}
};
