
#include <stdio.h>

#include "Node.hpp"

void Node::getPath(list<Point>& pathList)
{
    pathList.push_back(Point(point.x,point.y));
    if(parent)
    {
        parent->getPath(pathList);
    }
}
