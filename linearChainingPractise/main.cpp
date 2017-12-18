#include <iostream>
#include <string>
#include <list>

using namespace std;

class linearChaining
{
private:
    class bins
    {
    public:
        string s;
        int val;
        bins(string s,int val):s(s),val(val){}
    };
    list<bins>* chains;
    int hash(const string& s)
    {
        int sum=0;
        for(int i=0;i<s.length();i++)
            sum+=(int)(s[i]-'a');
        return sum;
    }
public:
    linearChaining(int size)
    {
        chains=new list<bins> [size];
    }
    ~linearChaining()
    {
        delete [] chains;
    }
    void add(const string& s,int val)
    {
        int pos=hash(s);
        for(list<bins>::iterator i=chains[pos].begin();i!=chains[pos].end();++i)
        {
            if(s==i->s)
            {
                i->val=val;
                return;
            }
        }
        chains[pos].push_front(bins(s,val));
    }
    int getValue(const string& s)
    {
        int pos=hash(s);
        for(list<bins>::iterator i=chains[pos].begin();i!=chains[pos].end();++i)
        {
            if(s==i->s)
                return i->val;
        }
        return 0;
    }
};

int main()
{
    linearChaining lc(400);
    lc.add("apple",100);
    lc.add("apple",150);
    lc.add("elppa",50);
    cout<<lc.getValue("apple")<<endl;
    cout<<lc.getValue("aplpe")<<endl;
    cout<<lc.getValue("elppa")<<endl;
}
