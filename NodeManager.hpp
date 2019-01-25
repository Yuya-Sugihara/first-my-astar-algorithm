#ifndef NODEMANAGERCLASS
#define NODEMANAGERCLASS

#include "Node.hpp"
#include <vector>

static const int width=10;
static const int height=10;

class NodeManager
{
public:
    static NodeManager* getInstance();
    Node* getNodeByPoint(Point searchingPoint);
    Node* getNodeByMark(std::string searchingMark);
    void showMap();
    void showMapWithDetail();
    void showPath();
    
    Point getStartPoint() { return startPoint; };
    void setStartPoint(Point point) { startPoint=point; };
    Point getGoalPoint() { return goalPoint; };
    void setGoalPoint(Point point) { goalPoint=point; };
private:
    NodeManager();
    ~NodeManager();
    NodeManager(const NodeManager& obj);
    NodeManager& operator=(const NodeManager& obj);

    static NodeManager* instance;
    std::vector<Node*> map;
    std::list<Point> pathList;
    Point startPoint;
    Point goalPoint;
   

};

#endif //NODEMANAGERCLASS
