#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Trie
{
private:
    class Node
    {
    public:
        Node* next[26];
        bool isWord;
        Node()
        {
            for(int i=0;i<26;i++)
                next[i]=nullptr;
            isWord=false;
        }
        ~Node()
        {
            for(int i=0;i<26;i++)
                delete next[i];
        }
    };
    Node* root;
public:
    Trie()
    {
        root=new Node();
    }
    void add(const string& word)
    {
        Node* p=root;
        for(int i=0;i<word.length();i++)
        {
            if(p->next[(int)(word[i]-'a')]==nullptr)
                p->next[(int)(word[i]-'a')]=new Node();
            p=p->next[(int)(word[i]-'a')];
        }
        p->isWord=true;
    }
    bool contains(const string& word)
    {
        Node* p=root;
        for(int i=0;i<word.length();i++)
        {
            if(p->next[(int)(word[i]-'a')]==nullptr)
                return false;
            p=p->next[(int)(word[i]-'a')];
        }
        return p->isWord;
    }
    bool containsPrefix(const string& word)
    {
        Node* p=root;
        for(int i=0;i<word.length();i++)
        {
            if(p->next[(int)(word[i]-'a')]==nullptr)
                return false;
            p=p->next[(int)(word[i]-'a')];
        }
        return true;
    }
    void load(const string& filename)
    {
        ifstream fin(filename);
        string word;
        while(!fin.eof())
        {
            fin>>word;
            add(word);
        }
    }
};

int main()
{
    Trie tr;
    tr.load("dict.txt");
    cout<<tr.contains("aaa")<<endl;
    cout<<tr.containsPrefix("bird")<<endl;
}
