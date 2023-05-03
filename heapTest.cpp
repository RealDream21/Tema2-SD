#include <iostream>
#include <vector>
#include <fstream>

using namespace std;



class Heap{
    int dim;
    std::vector<int> v;
    void urca(int i);
    void coboara();
public:
    Heap() = default;
    void pushToHeap(const int x);
    int popMax();
    void mergeHeaps(Heap * ptrOther);
};

int main()
{
    Heap * a = new Heap();
    Heap ** multimi = new Heap*[102];
    int N, Q;
    ifstream fin("mergeheap.in");
    ofstream fout("mergeheap.out");
    fin >> N >> Q;
    for(int i = 1; i <= N; i++)
        multimi[i] = new Heap();

    while(Q)
    {
        int operatie;
        fin >> operatie;
        if(operatie == 1){
            int m, X;
            fin >> m >> X;
            if(multimi[m] == nullptr){
                multimi[m] = new Heap();
            }
            multimi[m]->pushToHeap(X);
        }
        else if(operatie == 2){
            int m;
            fin >> m;
            fout << multimi[m]->popMax() << endl;
        }
        else if(operatie == 3){
            int a, b;
            fin >> a >> b;
            multimi[a]->mergeHeaps(multimi[b]);
            multimi[b] = nullptr;
        }
        Q--;
    }
    return 0;
}

void Heap::urca(int i)
{
    while(i){
        int tata = (i - 1)/2;
        if(v[tata] < v[i]){
            swap(v[tata], v[i]);
            i = tata;
        }
        else break;
    }
}

void Heap::coboara()
{
    int i = 0;
    while(i * 2 + 2 < v.size()){

        int fiu_st = i * 2 + 1;
        int fiu_dr = i * 2 + 2;
        if (v[fiu_st] >= v[fiu_dr] && v[fiu_st] > v[i]){
            swap(v[i], v[fiu_st]);
            i = fiu_st;
        }
        else if(v[fiu_dr] > v[fiu_st] && v[fiu_dr] > v[i]){
            swap(v[i], v[fiu_dr]);
            i = fiu_dr;
        }
        else {
            break;
        }
    }
}

void Heap::pushToHeap(const int x){
    v.push_back(x);
    urca(v.size() - 1);
}

int Heap::popMax()
{
    int toReturn = v[0];
    v[0] = v[v.size() - 1];
    coboara();
    v.pop_back();
    return toReturn;
}

void Heap::mergeHeaps(Heap* other)
{
    for(int i = 0; i < other->v.size(); i++)
        pushToHeap(other->v[i]);
    delete other;
    return;
}
