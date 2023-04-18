#include <iostream>
using namespace std;

const int BranchingFactor = 2;

class Node{
public:
    int n_keys;
    int n_child;
    int* keys;
    Node** child;
    Node* parent;
    bool isLeaf;
    //static int BranchingFactor;
    Node();
    Node(int key);
    Node(Node* parentNode);
    int keySize()const;
    void insertKey(int key);
    void traverse()const; // to be deleted after
    friend class Btree;
};

class Btree{
public:
    Node* root;
    Btree();
    void insertElement(int toInsert);
    void insertElement(int toInsert, Node* currentNode);
    bool searchElement(int toSearch);
    bool searchElement(int toSearch, Node* currentNode);
    void show();
};

//int Node::BranchingFactor = 2;


int main()
{
    Btree b_tree;
    b_tree.insertElement(5);
    b_tree.insertElement(7);
    b_tree.insertElement(8);
    b_tree.insertElement(10);
    b_tree.show();
    cout << endl;

    cout << b_tree.searchElement(5);

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
    child = new Node*[2*BranchingFactor];
    keys[0] = key;
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

void Node::traverse() const {
    int i;
    for (i = 0; i < n_keys; i++) {
        if (!isLeaf) {
            if (child[i] != nullptr)
                child[i]->traverse();
            else
                cout << " nullptr";
        }
        cout << " " << keys[i];
    }
    if (!isLeaf)
        child[i]->traverse();
}

Btree::Btree()
{
    root = nullptr;
}

void Btree::insertElement(int toInsert)
{
    if(root != nullptr)
    {
        cout << endl;
        cout << "Traversing: ";
        root->traverse();
        cout << endl;
    }
    if(root == nullptr){
        root = new Node(toInsert);
        cout << toInsert << ": " << "if root == nullptr\n";
    }
    else{
        cout << toInsert << ": " << "else\n";
        Node* currentNode = root;
        Node* parentNode = nullptr;

        while(currentNode->isLeaf == false){
            cout << toInsert << ": " << "While currentNode->isLeaf == false\n";
            //parcurg nodurile pana dau de o frunza
            parentNode = currentNode;
            parentNode->isLeaf = false; // ???????
            int i = 0;
            while(i < currentNode->n_keys && toInsert > currentNode->keys[i]){
                i++;
                cout << toInsert << ": " << "while(i < currentNode->n_keys && toInsert > currentNode->keys[i])\n";
            }
            currentNode = currentNode->child[i];
        }
        currentNode->insertKey(toInsert);
        //inserez, daca e full => split
        while(currentNode->n_keys == 2*BranchingFactor - 1){
            cout << toInsert << ": " << "while(currentNode->n_keys == 2*BranchingFactor - 1)\n";
            if(currentNode == root){
                for(int i = 0; i < currentNode->n_keys; i++)
                    cout << currentNode->keys[i] << " ";

                cout << toInsert << ": " << "if(currentNode == root)\n";
                //daca e radacina => fac o radacina noua
                Node* newRoot = new Node(currentNode->keys[BranchingFactor - 1]);
                //urc elementul din mijloc
                newRoot->isLeaf = false;
                newRoot->child[0] = currentNode;
                Node* newNode = new Node();
                newNode->isLeaf = currentNode->isLeaf; // error because of this
                newNode->n_keys = BranchingFactor - 1;

                for(int i = 0; i < BranchingFactor - 1; i++)
                    newNode->keys[i] = currentNode->keys[i + BranchingFactor];

                for(int i = 0; i <= newNode->n_keys; i++)
                    newNode->child[i] = currentNode->child[i + BranchingFactor];

                currentNode->n_keys = BranchingFactor - 1;
                newRoot->child[1] = newNode;
                currentNode = newRoot;
                root = newRoot;
                parentNode = nullptr;
            }
            else{
                cout << toInsert << ": " << "else\n";
                //split si urc mijlocul la parent
                Node* newNode = new Node();
                newNode->isLeaf = currentNode->isLeaf; // changed from = true;
                newNode->n_keys = BranchingFactor - 1;
                for(int i = 0; i < BranchingFactor - 1; i++)
                    newNode->keys[i] = currentNode->keys[i + BranchingFactor];

                currentNode->n_keys = BranchingFactor - 1;

                for(int i = 0; i <= newNode->n_keys; i++)
                    newNode->child[i] = currentNode->child[i + BranchingFactor];

                int keyToParent = currentNode->keys[BranchingFactor - 1];
                int i = parentNode->n_keys;
                //de la dreapta la stanga fac loc pentru cheie in timp ce ii gasesc pozitia potrivita
                while(i > 0 && keyToParent < parentNode->keys[i - 1]){
                        parentNode->keys[i] = parentNode->keys[i - 1];
                        parentNode->child[i + 1] = parentNode->child[i];
                        i--;
                }
                parentNode->keys[i] = keyToParent;
                parentNode->child[i + 1] = newNode;
                parentNode->n_keys++;

                currentNode = parentNode;
            }
        }
    }
}


void Node::insertKey(int toInsert)
{
    int i = n_keys - 1;
    while(i >= 0 && keys[i] > toInsert){
        keys[i + 1] = keys[i];
        i--;
    }
    keys[i + 1] = toInsert;
    n_keys++;
}


bool Btree::searchElement(int toSearch)
{
    return searchElement(toSearch, root);
}

bool Btree::searchElement(int toSearch, Node* currentNode)
{
    int i = 0;
    while(i < currentNode->n_keys && toSearch > currentNode->keys[i])
        i++;
    if(currentNode->keys[i] == toSearch){
        return true;
    }
    else if(currentNode->isLeaf == true){
        return false;
    }
    else{
        return searchElement(toSearch, currentNode->child[i]);
    }
}


void Btree::show()
{
    root->traverse();
}
