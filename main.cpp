#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <list>

#include "Node.hpp"
#include "NodeManager.hpp"

using namespace std;



float getDistance(Point p1,Point p2)
{
    int dx=abs(p1.x-p2.x);
    int dy=abs(p1.y-p2.y);
    
    return sqrt(dx*dx+dy*dy);
}

int getCost(Point p1,Point p2)
{
    int dx=abs(p1.x-p2.x);
    int dy=abs(p1.y-p2.y);
    
    return max(dx,dy);
}

Node* selectLeastCostNode(list<Node*> openedList)
{
    Node* selectedNode=nullptr;
    int minScore=1000;
    
    list<Node*>::iterator it;
    for(it=openedList.begin();it!=openedList.end();it++)
    {
        if(minScore >= (*it)->score)
        {
            minScore=(*it)->score;
            selectedNode=(*it);
        }
    }
    cout <<"selected Node is: ";
    selectedNode->showDetail();
    return selectedNode;
}

void eraseTheNode(list<Node*>& openedList,Node* erasingNode)
{
    list<Node*>::iterator it;
    for(it=openedList.begin();it!=openedList.end();it++)
    {
        if(erasingNode == (*it) )
        {
            it=openedList.erase(it);
            continue;
        }
    }
}

void setAndCalculateScore(list<Node*>& addingNodeList,Node* openNode)
{
    NodeManager* nodeManager=NodeManager::getInstance();
    const Point startPoint=nodeManager->getStartPoint();
    const Point goalPoint=nodeManager->getGoalPoint();
    
    Point upPoint(openNode->point.x,openNode->point.y-1);
    upPoint.showPoint();
    Point downPoint(openNode->point.x,openNode->point.y+1);
    downPoint.showPoint();
    Point leftPoint(openNode->point.x-1,openNode->point.y);
    leftPoint.showPoint();
    Point rightPoint(openNode->point.x+1,openNode->point.y);
    rightPoint.showPoint();
    Point rightUpPoint(openNode->point.x+1,openNode->point.y-1);
    rightUpPoint.showPoint();
    Point rightDownPoint(openNode->point.x+1,openNode->point.y+1);
    rightDownPoint.showPoint();
    Point leftDownPoint(openNode->point.x-1,openNode->point.y+1);
    leftDownPoint.showPoint();
    Point leftUpPoint(openNode->point.x-1,openNode->point.y-1);
    leftUpPoint.showPoint();
    
    if(upPoint.y>=0 && nodeManager->getNodeByPoint(upPoint)->state == None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(upPoint));
    if(downPoint.y<height && nodeManager->getNodeByPoint(downPoint)->state == None)    addingNodeList.push_back(nodeManager->getNodeByPoint(downPoint));
    if(leftPoint.x>=0 && nodeManager->getNodeByPoint(leftPoint)->state==None)    addingNodeList.push_back(nodeManager->getNodeByPoint(leftPoint));
    if(rightPoint.x<width && nodeManager->getNodeByPoint(rightPoint)->state == None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(rightPoint));
    
    if(rightUpPoint.y>=0 && rightUpPoint.x<width &&
       nodeManager->getNodeByPoint(rightUpPoint)->state == None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(rightUpPoint));
    if(rightDownPoint.y<height && rightDownPoint.x<width &&
       nodeManager->getNodeByPoint(rightDownPoint)->state == None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(rightDownPoint));
    if(leftDownPoint.x>=0 && leftDownPoint.y<height &&
       nodeManager->getNodeByPoint(leftDownPoint)->state==None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(leftDownPoint));
    if(leftUpPoint.x>=0 && leftUpPoint.y>=0 &&
       nodeManager->getNodeByPoint(leftUpPoint)->state == None)
        addingNodeList.push_back(nodeManager->getNodeByPoint(leftUpPoint));
    
    list<Node*>::iterator it;
    cout <<"adding Node is:" <<endl;
    for(it=addingNodeList.begin();it!=addingNodeList.end();it++)
    {
        (*it)->cost=getCost((*it)->point,startPoint);
        (*it)->hCost=getDistance((*it)->point,goalPoint);
        (*it)->setScore();
        (*it)->parent=openNode;
        (*it)->state=Open;
        (*it)->mark="O";
        (*it)->showDetail();
    }
    
}



void astar()
{
    NodeManager* nodeManager=NodeManager::getInstance();
    list<Node*> openedNodeList;
    
    Node* firstNode= nodeManager->getNodeByPoint(nodeManager->getStartPoint());
    openedNodeList.push_back(firstNode);
    firstNode->state=Open;
    firstNode->mark="O";
    //cout << openedNodeList.size() <<endl;
    
    //スコアの一番低いノードをopenedNodeListから取得
    //もしそのノードがゴールノードなら探索終了
    //選択されたノードの隣にあるノードを全て（stateがNone）openedNodeListに追加する
    //追加時に選択されたノードをparentに代入する
    //スコアの計算、stateをopenにする
    //最初に選択されたノードを削除する
    while( openedNodeList.size() != 0)
    {
        Node* openNode=selectLeastCostNode(openedNodeList);
        if( openNode->point == nodeManager->getGoalPoint())
        {
            cout <<"探索を完了しました"<<endl;
            nodeManager->showPath();
            return ;
        }
        list<Node*> addingNodeList;
        
        setAndCalculateScore(addingNodeList,openNode);
        cout <<addingNodeList.size() <<endl;
        openedNodeList.merge(addingNodeList);
        openNode->state=Close;
        openNode->mark="C";
        eraseTheNode(openedNodeList,openNode);
        
        nodeManager->showMap();
    }
    
    cout <<" 探索に失敗しました。" <<endl;
  
}



int main()
{
    NodeManager* nodeManager=NodeManager::getInstance();
    nodeManager->showMap();
    //nodeManager->showMapWithDetail();
    
    astar();
    //nodeManager->showMapWithDetail();
    return 0;
}
