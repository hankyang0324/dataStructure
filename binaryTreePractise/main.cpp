#include <iostream>

using namespace std;

class binaryTree
{
private:
    class Node
    {
    public:
        int val;
        Node* left;
        Node* right;
        Node(int val):val(val),left(nullptr),right(nullptr){}
        ~Node()
        {
            delete left;
            delete right;
        }
        void inorder()
        {
            if(left!=nullptr)
                left->inorder();
            cout<<val<<" ";
            if(right!=nullptr)
                right->inorder();
        }
        void preorder()
        {
            cout<<val<<" ";
            if(left!=nullptr)
                left->preorder();
            if(right!=nullptr)
                right->preorder();
        }
        void postorder()
        {
            if(left!=nullptr)
                left->postorder();
            if(right!=nullptr)
                right->postorder();
            cout<<val<<" ";
        }
        void addRecursive(int v)
        {
            if(v>val)
            {
                if(right==nullptr)
                {
                    right=new Node(v);
                    return;
                }
                right->addRecursive(v);
            }
            else
            {
                if(left==nullptr)
                {
                    left=new Node(v);
                    return;
                }
                left->addRecursive(v);
            }
        }
    };
    Node* root;
public:
    binaryTree()
    {
        root=nullptr;
    }
    void add(int v)
    {
        if(root==nullptr)
        {
            root=new Node(v);
            return;
        }
        Node* p=root;
        while(true)
        {
            if(v<=p->val)
            {
                if(p->left==nullptr)
                {
                    p->left=new Node(v);
                    return;
                }
                else
                    p=p->left;
            }
            else
            {
                if(p->right==nullptr)
                {
                    p->right=new Node(v);
                    return;
                }
                else
                    p=p->right;
            }
        }
        //上面p->left先指向一个计算机给其分配的地址a，如果p->left==nullptr，在地址a创建new Node
        //下面p=p->left然后如果p->left==nullptr，p的地址会指向nullptr的地址0x0,在0x0创建new Node,不能这么玩，马德有毒！
//        while(true)
//        {
//            if(v<p->val)
//                p=p->left;
//            else
//                p=p->right;
//            if(p==nullptr)
//            {
//                p=new Node(v);
//                return;
//            }
//        }
    }
    void addRecursive(int v)
    {
        if(root==nullptr)
        {
            root=new Node(v);
            return;
        }
        root->addRecursive(v);
    }
    void inorder()
    {
        if(root!=nullptr)
            root->inorder();
    }
    void preorder()
    {
        if(root!=nullptr)
            root->preorder();
    }
    void postorder()
    {
        if(root!=nullptr)
            root->postorder();
    }
};

int main()
{
    binaryTree bt;
    bt.add(5);
    for(int i=0;i<10;i++)
        bt.add(i);
    bt.inorder();
    cout<<endl;
    bt.preorder();
    cout<<endl;
    bt.postorder();
    cout<<endl;
    binaryTree btr;
    btr.addRecursive(5);
    for(int i=0;i<10;i++)
        btr.addRecursive(i);
    btr.inorder();
    cout<<endl;
    btr.preorder();
    cout<<endl;
    btr.postorder();
    cout<<endl;
}
