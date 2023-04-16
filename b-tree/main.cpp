#include <iostream>
using namespace std;

const int BranchingFactor = 2;

class Node{
    int n_keys;
    int n_child;
    int* keys;
    Node** child;
    Node* parent;
    bool isLeaf;
public:
    //static int BranchingFactor;
    Node();
    Node(int key);
    Node(Node* parentNode);
    int keySize()const;
    void insertKey(int key);
    friend class Btree;
};

class Btree{
    Node* root;
public:
    Btree();
    void insertElement(int toInsert);
    void insertElement(int toInsert, Node* currentNode);
    bool searchElement(int toSearch);
};

//int Node::BranchingFactor = 2;


int main()
{
    Btree b_tree;
    b_tree.insertElement(120);

    return 0;
}

Node::Node()
{
    n_keys = 0;
    keys = new int[2*BranchingFactor - 1];
    child = new Node*[2*BranchingFactor];
    isLeaf = true;
    parent = nullptr;
}

Node::Node(int key)
{
    n_keys = 1;
    keys = new int[2*BranchingFactor - 1];
    keys[0] = key;
    child = new Node*[2*BranchingFactor];
    isLeaf = true;
    parent = nullptr;
}

Node::Node(Node * parentNode)
{
    n_keys = 0;
    keys = new int[2*BranchingFactor - 1];
    child = new Node*[2*BranchingFactor];
    isLeaf = true;
    this->parent = parentNode;
}

int Node::keySize() const
{
    return n_keys;
}

Btree::Btree()
{
    root = nullptr;
}

void Btree::insertElement(int toInsert)
{
    if(root == nullptr){
        root = new Node(toInsert);
    }
    else{
        insertElement(toInsert, root);
    }
}

void Btree::insertElement(int toInsert, Node* currentNode)
{
    if(currentNode.isLeaf == true){


    }
    else{
        int i = 0;
        while(i <= currentNode->keySize() && toInsert > currentNode->keys[i]){
            i++;
        }
        insertElement(toInsert, currentNode->child[i]);
    }
}
