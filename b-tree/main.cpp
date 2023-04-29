#include <iostream>
using namespace std;

const int BranchingFactor = 2;

class Node{
public:
    int min_keys;
    int n_keys;
    int n_child;
    int* keys;
    Node** child;
    Node* parent;
    bool isLeaf;

    Node();
    Node(int key);
    Node(Node* parentNode);
    int keySize()const;
    void insertKey(int key);
    void traverse()const; // to be deleted after
    void deleteLeafPos(int PosToDelete);
    void deleteNonLeafPos(int PosToDelete);
    void deleteElement(int toDelete);
    int getLower(int pos);//numarul lower < keys[pos];
    int getHigher(int pos);//numarul higher > keys[pos];
    void mergeNode(int pos);//merge cu urmatorul nod
    void fixChild(int pos);
    void borrowNext(int pos);//child[i] ia de la child[i + 1] daca are destule chei
    void borrowPrev(int pos);
    friend class Btree;
};

class Btree{
    int min_keys;
public:
    Node* root;
    Btree();
    void insertElement(int toInsert);
    void insertElement(int toInsert, Node* currentNode);
    void deleteElement(int toDelete);
    bool searchElement(int toSearch);
    bool searchElement(int toSearch, Node* currentNode);
    int cerinta4(int X);
    int cerinta5(int X);
    void show();
};

//int Node::BranchingFactor = 2;


int main()
{
    Btree b_tree;
    b_tree.insertElement(5);
    b_tree.insertElement(7);
    b_tree.deleteElement(7);
    b_tree.insertElement(8);
    b_tree.insertElement(10);
    cout << b_tree.cerinta5(6);



    return 0;
}

Node::Node()
{
    min_keys = BranchingFactor; //??????????????????
    /*if(BranchingFactor % 2 == 0)
        min_keys = BranchingFactor/2;
    else
        min_keys = (BranchingFactor + 1)/2;*/
    n_keys = 0;
    keys = new int[2*BranchingFactor - 1];
    child = new Node*[2*BranchingFactor];
    isLeaf = true;
    parent = nullptr;
}

Node::Node(int key)
{
    min_keys = BranchingFactor; //?????????????????
    /*if(BranchingFactor % 2 == 0)
        min_keys = BranchingFactor/2;
    else
        min_keys = (BranchingFactor + 1)/2;*/
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

void Node::traverse() const
{
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

void Node::deleteLeafPos(int PosToDelete)
{
    bool deletion = false;
    for(int i = PosToDelete; i < n_keys - 1; i++)
        keys[i] = keys[i + 1];
    n_keys--;
    return;
}

void Node::deleteNonLeafPos(int PosToDelete)
{
    int aux = keys[PosToDelete];

    if(child[PosToDelete]->n_keys >= min_keys){
        //pot sa ma imprumut din dreapta
        int lower = getLower(PosToDelete);
        keys[PosToDelete] = lower;
        child[PosToDelete]->deleteElement(lower);
    }
    else if(child[PosToDelete + 1]->n_keys >= min_keys){
        int higher = getHigher(PosToDelete);
        keys[PosToDelete] = higher;
        child[PosToDelete + 1]->deleteElement(higher);
    }
    else{
        mergeNode(PosToDelete);
        child[PosToDelete]->deleteElement(PosToDelete);
    }
    return;
}

void Node::deleteElement(int toDelete)
{
    int i = 0;
    while(i < this->n_keys && toDelete > this->keys[i])
        i++;

    if(i < this-> n_keys && keys[i] == toDelete){
        if(this->isLeaf)
            this->deleteLeafPos(i);
        else
            this->deleteNonLeafPos(i);
    }
    else{
        if(this->isLeaf)
            return;
        bool isFound = false;
        if(i == this->n_keys) isFound = true;

        if(this->child[i]->n_keys < min_keys)
            fixChild(i);

        if(isFound && i > this->n_keys)
            this->child[i - 1]->deleteElement(toDelete);
        else
            this->child[i]->deleteElement(toDelete);
    }
    return;
}


Btree::Btree()
{
    min_keys = BranchingFactor;// ?????????????

    /*if(BranchingFactor % 2 == 0)
        min_keys = BranchingFactor/2;
    else
        min_keys = (BranchingFactor + 1)/2;*/
    root = nullptr;
}

void Node::insertKey(int toInsert)
{
    int i = this->n_keys - 1;

    if(this->isLeaf == true)
    {

        while(i >= 0 && toInsert < keys[i])
        {
            //caut locul cheii in timp ce ii si fac loc
            this->keys[i + 1] = keys[i];
            i--;
        }
        this->keys[i + 1] = toInsert;
        this->n_keys++;
    }
    else
    {
        while(i >= 0 && this->keys[i] > toInsert)
            i--;

        if(this->child[i + 1]->n_keys == 2*BranchingFactor - 1)
        {
            Node* newNode = new Node();
            newNode->isLeaf = this->child[i + 1]->isLeaf;
            newNode->n_keys = BranchingFactor - 1;

            for(int j = 0; j < BranchingFactor - 1; j++)
                newNode->keys[j] = this->child[i + 1]->keys[j + BranchingFactor];

            if(this->child[i + 1]->isLeaf == false)
                for(int j = 0; j < BranchingFactor; j++) // changed from BranchingFactor - 1
                    newNode->child[j] = this->child[i + 1]->child[j + BranchingFactor];

            this->child[i + 1]->n_keys = BranchingFactor - 1;

            for(int j = this->n_keys; j >= i + 2; j--) // changed from i + 1
                this->child[j] = this->child[j - 1];
            this->child[i + 2] = newNode; // changed from i + 1

            for(int j = this->n_keys - 1; j >= i + 1; j--) // changed from i
                this->keys[j + 1] = this->keys[j]; // changed from keys[i] and changed from keys[i + 1]


            this->keys[i + 1] = this->child[i + 1]->keys[BranchingFactor - 1]; //changed from keys[i]
            this->n_keys++;

            if(this->keys[i + 1] < toInsert)
                i++;
        }
        this->child[i + 1]->insertKey(toInsert);
    }
}

void Btree::insertElement(int toInsert)
{
    Node* currentNode = root;
    if(root == nullptr)
        root = new Node(toInsert);
    else{
        if(root->n_keys == 2*BranchingFactor - 1)
        {
            Node * newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->child[0] = root;

            Node * newChild = new Node();
            newChild->isLeaf = root->isLeaf;
            newChild->n_keys = BranchingFactor - 1;

            for(int j = 0; j < BranchingFactor - 1; j++)
                newChild->keys[j] = root->keys[j + BranchingFactor];
            //nu e root => are copii de copiat deodata cu keys
            if(root->isLeaf == false)
                for(int j = 0; j < BranchingFactor; j++)
                    newChild->child[j] = root->child[j + BranchingFactor];

            root->n_keys = BranchingFactor - 1;

            for(int j = newRoot->n_keys + 1; j >= 2; j--)
                newRoot->child[j] = newRoot->child[j - 1];
            newRoot->child[1] = newChild;

            for(int j = newRoot->n_keys; j >= 1; j--)
                newRoot->keys[j] = newRoot->keys[j - 1];

            newRoot->keys[0] = root->keys[BranchingFactor - 1];

            newRoot->n_keys++;

            int i = 0;
            if(newRoot->keys[0] < toInsert)
                i++;
            newRoot->child[i]->insertKey(toInsert);
            root = newRoot;
        }
        else{
            root->insertKey(toInsert);
        }
    }
}


void Node::fixChild(int pos)
{
    //ma pot imprumuta din stanga
    if(pos != 0 && child[pos - 1]->n_keys >= min_keys)
        borrowPrev(pos);
    else if(pos != n_keys && child[pos + 1]->n_keys >= min_keys)
        borrowNext(pos);
    else{
        if(pos != n_keys)
            mergeNode(pos);
        else
            mergeNode(pos - 1);
    }
    return;
}

int Node::getLower(int pos)
{
    Node* curentNode = child[pos];
    while(!curentNode->isLeaf)
        curentNode = curentNode->child[curentNode->n_keys];
    return curentNode->keys[n_keys - 1];
}

int Node::getHigher(int pos)
{
    Node* curentNode = child[pos + 1];
    while(!curentNode->isLeaf)
        curentNode = curentNode->child[0];
    return curentNode->keys[0];
}

void Node::mergeNode(int pos)
{
    Node* mergeHere = child[pos];
    Node* mergeFrom = child[pos + 1];

    mergeHere->keys[min_keys - 1] = keys[pos];

    for(int i = 0; i < mergeFrom->n_keys; i++)
        mergeHere->keys[min_keys + i] = mergeFrom->keys[i];

    if(!mergeHere->isLeaf){
        for(int i = 0; i <= mergeFrom->n_keys; i++)
            mergeHere->child[i + min_keys] = mergeFrom->child[i];
    }

    for(int i = pos; i < n_keys - 1; i++)
        keys[i] = keys[i + 1];

    for(int i = pos + 1; i < n_keys; i++)
        child[i] = child[i + 1];
    mergeHere->n_keys += mergeFrom->n_keys + 1;
    n_keys--;
    delete mergeFrom;
    return;
}

void Node::borrowNext(int pos)
{
    Node *dest = child[pos];
    Node* source = child[pos + 1];

    dest->keys[dest->n_keys] = keys[pos];

    if(!dest->isLeaf)
        dest->child[dest->n_keys + 1] = source->child[0];

    keys[pos] = source->keys[0];

    for(int i = 0; i < source->n_keys - 1; i++)
        source->keys[i] = source->keys[i + 1];

    if(!source->isLeaf){
        for(int i = 0; i < source->n_keys; i++)
            source->child[i] = source->child[i + 1];
    }

    dest->n_keys++;
    source->n_keys--;
    return;
}

void Node::borrowPrev(int pos)
{
    Node* dest = child[pos];
    Node* source = child[pos - 1];

    for(int i = dest->n_keys; i >= 1; i--)
        dest->keys[i] = dest->keys[i - 1];

    if(!dest->isLeaf)
        for(int i = dest->n_keys + 1; i >= 1; i--)
            dest->child[i] = dest->child[i - 1];

    dest->keys[0] = keys[pos - 1];
    if(!dest->isLeaf)
        dest->child[0] = source->child[dest->n_keys];

    keys[pos - 1] = source->keys[source->n_keys - 1];

    dest->n_keys++;
    source->n_keys--;

    return;
}

bool Btree::searchElement(int toSearch)
{
    return searchElement(toSearch, root);
}

bool Btree::searchElement(int toSearch, Node* currentNode)
{
    int i = 0;

    if(currentNode == nullptr)
        return false;

    if(currentNode->n_keys == 0)
        return false;

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

void Btree::deleteElement(int toDelete)
{
    if(root->isLeaf && toDelete == root->keys[0] && root->n_keys == 1)
        root = nullptr;
    if(root == nullptr)
        return;
    root->deleteElement(toDelete);

    if(root->n_keys == 0)
    {
        Node* aux = root;
        if(root->isLeaf)
            root = nullptr;
        else
            root = root->child[0];
        delete aux;
    }
    return;
}


void Btree::show()
{
    root->traverse();
}

int Btree::cerinta4(int X)
{
    Node* currentNode = root;
    int largest_smaller;

    while (currentNode != nullptr) {
        int i = 0;
        while (i < currentNode->n_keys && currentNode->keys[i] < X) {
            largest_smaller = currentNode->keys[i];
            i++;
        }
        if(currentNode->keys[i] == X) return X;
        if(currentNode->isLeaf) currentNode = nullptr;
        else currentNode = currentNode->child[i];
    }

    return largest_smaller;
}

int Btree::cerinta5(int X)
{
    Node* currentNode = root;
    int smallest_larger;

    while (currentNode != nullptr) {
        int i = 0;
        while (i < currentNode->n_keys && currentNode->keys[i] < X)
        {
            if(i < currentNode->n_keys - 1)
                smallest_larger = currentNode->keys[i + 1];
            i++;
        }
        if(i < currentNode->n_keys && currentNode->keys[i] == X) return X;
        if (i < currentNode->n_keys && currentNode->keys[i] < smallest_larger)
            smallest_larger = currentNode->keys[i];
        if (currentNode->isLeaf)
            currentNode = nullptr;
        else
            currentNode = currentNode->child[i];
    }
    return smallest_larger;
}




