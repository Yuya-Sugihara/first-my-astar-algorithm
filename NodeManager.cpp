#include "NodeManager.hpp"

#include <iostream>

NodeManager* NodeManager::instance=nullptr;

NodeManager* NodeManager::getInstance()
{
    if(!instance) instance=new NodeManager();
    return instance;
}

Node* NodeManager::getNodeByPoint(Point searchingPoint)
{
    std::vector<Node*>::iterator it;
    for(it=map.begin();it!=map.end();it++)
    {
        if( (*it)->point == searchingPoint)
            return (*it);
    }

    std::cout << "getNodeByPointメソッド内でノードが見つかりませんでした" <<std::endl;
    return nullptr;
}

Node* NodeManager::getNodeByMark(std::string searchingMark)
{
    std::vector<Node*>::iterator it;
    for(it=map.begin();it!=map.end();it++)
    {
        if( (*it)->mark == searchingMark)
            return (*it);
    }

    std::cout << "getNodeByMarkメソッド内でノードが見つかりませんでした" <<std::endl;
    return nullptr;
}

void NodeManager::showMap()
{
    for(int i=0 ;i<map.size();i++)
    {
        if(i%width ==0) std::cout <<std::endl;
        //std::cout << map[i]->mark << "(" <<map[i]->point.x << map[i]->point.y << ")";
        std::cout << map[i]->mark << " ";
    }
    
    std::cout <<std::endl;
}

void NodeManager::showMapWithDetail()
{
    for(int i=0 ;i<map.size();i++)
    {
        if(i%width ==0) std::cout <<std::endl;
        //std::cout << map[i]->mark << "(" <<map[i]->point.x << map[i]->point.y << ")";
        printf("(%d,%.1f,%.1f) ",map[i]->cost,map[i]->hCost,map[i]->score);
    }
    
    std::cout <<std::endl;
}

void NodeManager::showPath()
{
    getNodeByPoint(goalPoint) ->getPath(pathList);
    cout << pathList.size()<<endl;
    pathList.reverse();
    
    std::list<Point>::iterator it;
    for(it=pathList.begin();it!=pathList.end();it++)
    {
        cout << "( "<< (*it).x << " , "<<(*it).y <<" ) ";
    }
    cout <<endl;
}

NodeManager::NodeManager():
startPoint(1,3),
goalPoint(7,9)
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==startPoint.y && j==startPoint.x)
            {
                Node* node=new Node("S",startPoint);
                map.push_back(node);
                continue;
            }
            else if(i==goalPoint.y && j==goalPoint.x)
            {
                Node* node=new Node("G",goalPoint);
                map.push_back(node);
                continue;
            }
            
            /*
            else if( (i==4 && j <= 4) || (i==2 && j>=2) )
            {
                Node* node=new Node("W",Point(j,i));
                node->state=Wall;
                map.push_back(node);
                continue;
            }
             */
            
            Node* node=new Node("@",Point(j,i),0,0);
            map.push_back(node);
            
        }
    }
    
    showMap();
}
   
NodeManager::~NodeManager()
{
    map.clear();
}
    
