#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

class Node{
    int value;
    Node* left;
    Node* right;
    Node();
    Node(int valueInit);
public:
    bool isLeaf();
    friend class BinarySearchtree;
};

class BinarySearchtree{
    Node* root;
public:
    BinarySearchtree();
    void insertElement(int toInsert);
    void showInorder();
    void showInorder(Node* curentNode);
    bool searchElement(int toSearch);
    int cerinta4(int X);
    int cerinta5(int X);
    void deleteElement(int toDelete);
    void cerinta6(int X, int Y, ofstream& f);
    void cerinta6(Node* currentNode, int X, int Y, ofstream& f);
};

int main()
{
    BinarySearchtree tree;

    int operatie, X, t;
    fin >> t;
    while(t)
    {
        fin >> operatie >> X;
        if(operatie == 1){
            tree.insertElement(X);
        }
        if(operatie == 2){
            tree.deleteElement(X);
        }
        if(operatie == 3){
            fout << tree.searchElement(X) << endl;
        }
        if(operatie == 4){
            fout << tree.cerinta4(X) << endl;
        }
        if(operatie == 5){
            fout << tree.cerinta5(X) << endl;
        }
        if(operatie == 6){
            int Y;
            fin >> Y;
            tree.cerinta6(X, Y, fout);
        }
        t--;
    }

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
    if(root == nullptr){
        root = new Node(toInsert);
    }
    else{
        Node* curentNode = root;
        Node* parentNode = nullptr;
        while(true){
            if(toInsert > curentNode->value){
                if(curentNode->right == nullptr){
                    curentNode->right = new Node(toInsert);
                    break;
                }
                else{
                    curentNode = curentNode->right;
                }
            }
            if(toInsert < curentNode->value){
                if(curentNode->left == nullptr){
                    curentNode->left = new Node(toInsert);
                    break;
                }
                else{
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
    while(true){
        if(toSearch == curentNode->value)
            return true;
        if(toSearch > curentNode->value){
            if(curentNode->right == nullptr)
                return false;
            else{
                curentNode = curentNode->right;
            }
        }
        else if(toSearch < curentNode->value){
            if(curentNode->left == nullptr)
                return false;
            else{
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
    while(true){
        if(toDelete == curentNode->value){
            found = true;
            break;
        }
        if(toDelete > curentNode->value){
            if(curentNode->right == nullptr)
                break;
            else{
                parentNode = curentNode;
                curentNode = curentNode->right;
            }
        }
        else if(toDelete < curentNode->value){
            if(curentNode->left == nullptr)
                break;
            else{
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
            parentNode->left = nullptr;
        else if(parentNode->right == curentNode)
            parentNode->right = nullptr;
    }
    else
    {
        if (curentNode->left == nullptr || curentNode->right == nullptr)
        {
            Node* childNode = nullptr;
            if (curentNode->left == nullptr)
                childNode = curentNode->right;
            else
                childNode = curentNode->left;
            if (parentNode == nullptr)
                root = childNode;
            else if (parentNode->left == curentNode)
                parentNode->left = childNode;
            else
                parentNode->right = childNode;
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

void BinarySearchtree::showInorder()
{
    showInorder(root);
    cout << endl;
}

void BinarySearchtree::showInorder(Node* currentNode)
{
    if(currentNode != nullptr){
        showInorder(currentNode->left);
        cout << currentNode->value << " ";
        showInorder(currentNode->right);
    }
}

int BinarySearchtree::cerinta4(int X)
{
    Node* currentNode = root;
    int largest_smaller;

    while (currentNode != nullptr) {
        if (currentNode->value <= X) {
            largest_smaller = currentNode->value;
            currentNode = currentNode->right;
        }
        else {
            currentNode = currentNode->left;
        }
    }
    return largest_smaller;
}

int BinarySearchtree::cerinta5(int X)
{
    Node* currentNode = root;
    int smallest_larger;

    while (currentNode != nullptr) {
        if (X <= currentNode->value) {
            smallest_larger = currentNode->value;
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }
    return smallest_larger;
}

void BinarySearchtree::cerinta6(int X, int Y, ofstream& f)
{
    cerinta6(root, X, Y, f);
    f << endl;
}

void BinarySearchtree::cerinta6(Node* currentNode, int X, int Y, ofstream& f)
{
    if(currentNode == nullptr)
        return;
    if(currentNode->value >= X && currentNode->value <= Y){
        cerinta6(currentNode->left, X, Y, f);
        f << currentNode->value << " ";
        cerinta6(currentNode->right, X, Y, f);
    }
    else if(currentNode->value < X)
        cerinta6(currentNode->right, X, Y, f);
    else if(currentNode->value > Y)
        cerinta6(currentNode->left, X, Y, f);
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