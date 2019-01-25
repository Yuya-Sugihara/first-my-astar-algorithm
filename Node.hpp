#ifndef ASTARNODECLASS
#define ASTARNODECLASS

#include <string>
#include <iostream>
#include <list>
using namespace std;
enum State
{
    None,
    Open,
    Close,
    Wall
};

struct Point
{
    int x;
    int y;

    Point (int tx,int ty):
    x(tx),
    y(ty)
    {}

    void showPoint()
    {
        cout << " ( " << x << " , " << y << " ) " <<endl;
        
    }
    bool operator==(const Point& rhs) const
    {
        return (this->x==rhs.x && this->y==rhs.y);
    }
};

class Node
{
public:
    std::string mark;
    Point point;
    State state;
    int cost;
    float hCost;
    float score;
    Node* parent;

        
    Node():
    point (Point(0,0))
    {}
    
    Node(std::string tMark,Point tPoint,int tCost=0,float tHCost=0):
    mark(tMark),
    point (tPoint),
    state(None),
    cost(tCost),
    hCost(tHCost),
    score(tCost+tHCost),
    parent(nullptr)
    {}
    
    void setMark(std::string s)
    {
        mark=s;
    }
    void setScore()
    {
        score=cost+hCost;
    }

    void showDetail()
    {
        printf("point (%d,%d), cost %d, hCost %.1f, score %.1f \n"
                ,point.x,point.y,cost,hCost,score);
    }
    
    void getPath(list<Point>& pathList);
        
};

#endif //ASTARNODECLASS
