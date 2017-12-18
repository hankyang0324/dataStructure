#include <iostream>
#include <list>
#include <queue>

using namespace std;

class edgeList
{
private:
    class edge
    {
    public:
        int to;
        double w;
        edge(int to,double w):to(to),w(w){}
    };
    int V;
    list<edge>* edges;
public:
    edgeList(int v):V(v),edges(new list<edge>[V]){}
    ~edgeList()
    {
        delete [] edges;
    }
    void add(int from,int to,double w)
    {
        for(list<edge>::iterator i=edges[from].begin();i!=edges[from].end();++i)
        {
            if(i->to==to)
            {
                i->w=w;
                return;
            }
        }
        edges[from].push_back(edge(to,w));
        edges[to].push_back(edge(from,w));//I think it would be better to add this line.
    }
    bool isAdjacent(int from,int to)
    {
        for(list<edge>::iterator i=edges[from].begin();i!=edges[from].end();++i)
            if(i->to==to)
                return true;
        return false;
    }
    double getDistance(int from,int to)
    {
        for(list<edge>::iterator i=edges[from].begin();i!=edges[from].end();++i)
            if(i->to==to)
                return i->w;
        return 0;//should be INFINITY;
    }
    void DFS(int v)
    {
        bool visited[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        visited[v]=true;
        list<int> todo;
        todo.push_back(v);
        while(!todo.empty())
        {
            v=todo.back();
            cout<<v<<" ";
            todo.pop_back();
            for(int i=0;i<V;i++)
            {
                if(isAdjacent(v,i)&&visited[i]==false)
                {
                    visited[i]=true;
                    todo.push_back(i);
                }
            }
        }
    }
    void DFSR(int v)
    {
        bool visited[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        DFSR2(v,visited);
    }
    void DFSR2(int v,bool* visited)
    {
        visited[v]=true;
        cout<<v<<" ";
        for(int i=0;i<V;i++)
            if(isAdjacent(v,i)&&visited[i]==false)
                DFSR2(i,visited);
    }
    void BFS(int v)
    {
        bool visited[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        visited[v]=true;
        queue<int> todo;
        todo.push(v);
        while(!todo.empty())
        {
            v=todo.front();//NOT todo.back()!
            cout<<v<<" ";
            todo.pop();
            for(int i=0;i<V;i++)
            {
                if(isAdjacent(v,i)&&visited[i]==false)
                {
                    visited[i]=true;
                    todo.push(i);
                }
            }
        }
    }
};

int main()
{
    edgeList el(6);
    el.add(0,1,0.5);
    el.add(1,2,1.5);
    el.add(2,3,2.5);
    el.add(3,4,3.5);
    el.add(4,0,2);
    el.add(1,5,3);
    el.add(2,5,3.5);
    el.DFS(5);//this would be wrong without added line
    cout<<endl;
    el.DFSR(5);//this would be wrong without added line
    cout<<endl;
    el.BFS(5);//this would be wrong without added line
    cout<<endl;
}
