#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

class Node
{
public:
    int value;
    Node* left;
    Node* right;
    Node();
    Node(int valueInit);
    bool isLeaf();
    friend class BinarySearchtree;
};

class BinarySearchtree
{
public:
    Node* root;
    BinarySearchtree();
    void insertElement(int toInsert);
    void showInorder();
    void showInorder(Node* curentNode);
    bool searchElement(int toSearch);
    int cerinta4(int X);
    int cerinta5(int X);
    void deleteElement(int toDelete);
};

int main()
{
    BinarySearchtree tree;

    tree.insertElement(-999999999);
    tree.insertElement(999999999);
    tree.insertElement(32429);
    tree.insertElement(29038);
    tree.deleteElement(32429);
    cout << tree.searchElement(29038) << endl;
    tree.insertElement(7929);
    tree.insertElement(28240);
    tree.insertElement(11671);
    tree.deleteElement(7929);
    cout << tree.searchElement(11671) << endl;


    /*tree.insertElement(5);
    tree.insertElement(3);
    tree.insertElement(12);
    tree.insertElement(13);
    tree.deleteElement(12);*/




    tree.showInorder();


    fin.close();
    fout.close();

    return 0;
}

BinarySearchtree::BinarySearchtree()
{
    root = nullptr;
}

void BinarySearchtree::insertElement(int toInsert)
{
    if(root == nullptr)
    {
        root = new Node(toInsert);
    }
    else
    {
        Node* curentNode = root;
        Node* parentNode = nullptr;
        while(true)
        {
            if(toInsert > curentNode->value)
            {
                if(curentNode->right == nullptr)
                {
                    curentNode->right = new Node(toInsert);
                    break;
                }
                else
                {
                    curentNode = curentNode->right;
                }
            }
            if(toInsert < curentNode->value)
            {
                if(curentNode->left == nullptr)
                {
                    curentNode->left = new Node(toInsert);
                    break;
                }
                else
                {
                    curentNode = curentNode->left;
                }
            }
        }
    }
}

bool BinarySearchtree::searchElement(int toSearch)
{
    if(root == nullptr)
        return false;
    Node* curentNode = root;
    while(true)
    {
        if(toSearch == curentNode->value)
            return true;
        if(toSearch > curentNode->value)
        {
            if(curentNode->right == nullptr)
                return false;
            else
            {
                curentNode = curentNode->right;
            }
        }
        else if(toSearch < curentNode->value)
        {
            if(curentNode->left == nullptr)
                return false;
            else
            {
                curentNode = curentNode->left;
            }
        }
    }
}

void BinarySearchtree::deleteElement(int toDelete)
{
    if(root == nullptr)
        return;

    bool found = false;
    Node* curentNode = root;
    Node* parentNode = nullptr;
    while(true)
    {
        if(toDelete == curentNode->value)
        {
            found = true;
            break;
        }
        if(toDelete > curentNode->value)
        {
            if(curentNode->right == nullptr)
                break;
            else
            {
                parentNode = curentNode;
                curentNode = curentNode->right;
            }
        }
        else if(toDelete < curentNode->value)
        {
            if(curentNode->left == nullptr)
                break;
            else
            {
                parentNode = curentNode;
                curentNode = curentNode->left;
            }
        }
    }

    if(found == false) return;

    if(curentNode->isLeaf() && curentNode == root)
    {
        root = nullptr;
        return;
    }

    if(curentNode->isLeaf() == true)
    {
        if(parentNode->left == curentNode)
        {
            parentNode->left = nullptr;
        }
        else if(parentNode->right == curentNode)
        {
            parentNode->right = nullptr;
        }
    }
    else
    {
        if (curentNode->left == nullptr || curentNode->right == nullptr)
        {
            Node* childNode = nullptr;
            if (curentNode->left == nullptr){
                childNode = curentNode->right;
            }
            else{
                childNode = curentNode->left;
            }
            if (parentNode == nullptr){
                root = childNode;
            }
            else if (parentNode->left == curentNode){
                parentNode->left = childNode;
            }
            else{
                parentNode->right = childNode;
            }
            delete curentNode;
        }
        else{
            Node* replacementNode = curentNode->right;
            Node* parentReplacementNode = curentNode;
            while (replacementNode->left != nullptr){
                parentReplacementNode = replacementNode;
                replacementNode = replacementNode->left;
            }
            curentNode->value = replacementNode->value;
            if (parentReplacementNode->left == replacementNode){
                parentReplacementNode->left = replacementNode->right;
            }
            else{
                parentReplacementNode->right = replacementNode->right;
            }
            delete replacementNode;
        }
    }
}

int BinarySearchtree::cerinta4(int X)
{
    int ans;
    Node* currentNode = root;

    while(currentNode != nullptr){
        if(currentNode->value < X){
            ans = currentNode->value;
            currentNode = currentNode->right;
        }
        else{
            currentNode = currentNode->left;
        }
    }
    return ans;
}

int BinarySearchtree::cerinta5(int X)
{
    int ans;
    Node* currentNode = root;

    while(currentNode != nullptr){
        if(currentNode->value > X){
            ans = currentNode->value;
            currentNode = currentNode->left;
        }
        else{
            currentNode = currentNode->right;
        }
    }

    return ans;
}

void BinarySearchtree::showInorder()
{
    showInorder(root);
    cout << endl;
}

void BinarySearchtree::showInorder(Node* currentNode)
{
    if(currentNode != nullptr)
    {
        showInorder(currentNode->left);
        cout << currentNode->value << " ";
        showInorder(currentNode->right);
    }
}

Node::Node()
{
    left = nullptr;
    right = nullptr;
}

Node::Node(int valueInit): value(valueInit)
{
    left = nullptr;
    right = nullptr;
}

bool Node::isLeaf()
{
    if(left == nullptr && right == nullptr)
        return true;
    return false;
}


