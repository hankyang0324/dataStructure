#include <iostream>
#include <list>
#include <cmath>

using namespace std;
#define rows 10
#define cols 10

class Astar
{
private:
    class Point
    {
    public:
        int x,y;
        int G,H,F;
        Point* parent;
        Point(int x=0,int y=0,int G=0,int H=0,int F=0,Point* parent=nullptr):x(x),y(y),G(G),H(H),F(F),parent(parent){}
        void calF()
        {
            F=G+H;
        }
    };
    Point *startPoint,*endPoint;
    list<Point*> Path;
    list<Point*> openList;
    list<Point*> closeList;
    int spot[rows][cols]={
        {0,0,0,0,0,1,0,0,0,0},
        {1,1,1,1,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1},
        {0,0,0,0,1,1,0,0,0,0},
        {1,1,1,0,0,1,1,1,1,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,1,1,1},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,0,0,0}
    };
public:
    Astar(int xStart,int yStart,int xEnd,int yEnd)
    {
        startPoint=new Point(xStart,yStart,0,0,0,nullptr);
        endPoint=new Point(xEnd,yEnd,0,0,0,nullptr);
    }
    ~Astar()
    {
        while(!openList.empty())
        {
            Point* temp=openList.front();
            openList.pop_front();
            delete temp;
        }
        while(!closeList.empty())
        {
            Point* temp=closeList.front();
            closeList.pop_front();
            delete temp;
        }
    }
    Point* SetcloseList()
    {
        Point* leastF=openList.front();
        int F=leastF->F;
        for(list<Point*>::iterator it=openList.begin();it!=openList.end();++it)
        {
            if((*it)->F<F)
            {
                F=(*it)->F;
                leastF=*it;
            }
        }
        closeList.push_front(leastF);
        return leastF;
    }
    Point* SetopenList(Point* currentPoint)
    {
        openList.remove(currentPoint);
        int dx[8]={0,1,1,1,0,-1,-1,-1};
        int dy[8]={-1,-1,0,1,1,1,0,-1};
        int x,y;
        int dG=0;
        bool inCloseList=false;
        for(int k=0;k<8;k++)
        {
            if(k%2==0)
                dG=10;
            else
                dG=14;
            x=currentPoint->x+dx[k];
            y=currentPoint->y+dy[k];
            if(x==endPoint->x&&y==endPoint->y)
            {
                endPoint->parent=currentPoint;
                openList.push_front(endPoint);//方便析构时delete
                return endPoint;
            }
            if(0<=x&&x<rows&&0<=y&&y<rows&&spot[y][x]==0)
            {
                for(list<Point*>::iterator it=closeList.begin();it!=closeList.end();++it)
                {
                    if(x==(*it)->x&&y==(*it)->y)
                    {
                        inCloseList=true;
                        break;
                    }
                }
                if(inCloseList)
                {
                    inCloseList=false;
                    continue;
                }
                for(list<Point*>::iterator it=openList.begin();it!=openList.end();++it)
                {
                    if(x==(*it)->x&&y==(*it)->y)
                    {
                        if ((*it)->G>currentPoint->G+dG)
                        {
                            (*it)->G=currentPoint->G+dG;
                            (*it)->calF();
                            (*it)->parent=currentPoint;
                        }
                        break;
                    }
                }
                int G=currentPoint->G+dG;
                int H=abs(x-endPoint->x)+abs(y-endPoint->y);// Manhattan M
                int F=G+H;
//                Point newPoint(x,y,G,H,F,currentPoint);
//                openList.push_front(&newPoint);
//                不能这样，每次新建的newPoint可能使用同样的地址，会覆盖openList中的其余指针指向的Point的值，然后调用list.remove()时会被全部删除。
//                一定用new开辟新的地址，析构时一并delete。
                Point* newPoint=new Point(x,y,G,H,F,currentPoint);
                openList.push_front(newPoint);
            }
        }
        return nullptr;
    }
    bool findPath()
    {
        openList.push_front(startPoint);
        while(!openList.empty())
        {
            Point* p=SetcloseList();
            Point* p2=SetopenList(p);
            if(p2==endPoint)
                return true;
        }
        return false;
    }
    void getPath()
    {
        Point* p=endPoint;
        if(findPath()==true)
        {
            while(p!=nullptr)
            {
                Path.push_front(p);
                p=p->parent;
            }
        }
        for(list<Point*>::iterator it=Path.begin();it!=Path.end();++it)
            spot[(*it)->y][(*it)->x]=7;
    }
    friend ostream& operator<<(ostream& cout,Astar& a)
    {
        if(a.Path.empty())
            cout<<"No Path"<<endl;
        else
        {
            for(list<Point*>::iterator it=a.Path.begin();it!=a.Path.end();++it)
                cout<<"("<<(*it)->x<<","<<(*it)->y<<") ";
            cout<<endl;
            for(int y=0;y<rows;y++)
            {
                for(int x=0;x<cols;x++)
                    cout<<a.spot[y][x]<<" ";
                cout<<endl;
            }
        }
        return cout;
    }
};

int main()
{
    Astar a(0,0,rows-1,cols-1);
    a.getPath();
    cout<<a;
}
