#include <iostream>
#include <string>

using namespace std;

class linearProbing
{
private:
    class bins
    {
    public:
        string s;
        int val;
        bins()
        {
            s="NULL";
            val=0;
        }
        bins(const string& s,int val):s(s),val(val){}
    };
    bins* table;
    int size;
    int used;
    int hash(const string& s)
    {
        int sum=0;
        for(int i=0;i<s.length();i++)
            sum+=(int)(s[i]-'a');
        return sum;
    }
    void grow()
    {
        if(used*2>=size)
            size*=2;
        bins* temp=table;
        table=new bins [size];
        for(int i=0;i<size/2;i++)
            table[i]=temp[i];
    }
public:
    linearProbing(int size):size(size)
    {
        table=new bins [size];
        used=0;
    }
    ~linearProbing()
    {
        delete [] table;
    }
    void add(const string& s,int val)
    {
        grow();
        int pos=hash(s);
        while(table[pos].s!="NULL")
        {
            if(table[pos].s==s)
                table[pos].val=val;
            pos++;
            if(pos==size)
                pos=0;
        }
        used++;
        table[pos]=bins(s,val);
    }
    int getValue(const string& s)
    {
        int pos=hash(s);
        while(table[pos].s!="NULL")
        {
            if(table[pos].s==s)
                return table[pos].val;
            pos++;
            if(pos==size)
                pos=0;
        }
        return 0;
    }
};

int main()
{
    linearProbing lp(400);
    lp.add("apple",100);
    lp.add("apple",150);
    lp.add("elppa",50);
    cout<<lp.getValue("apple")<<endl;
    cout<<lp.getValue("aplpe")<<endl;
    cout<<lp.getValue("elppa")<<endl;
}
