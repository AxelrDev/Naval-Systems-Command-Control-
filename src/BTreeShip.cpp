#include "BTreeShip.hpp"
#include <iostream>
using namespace std;

BTreeNode::BTreeNode(bool _leaf) : n(0), leaf(_leaf) {
    for(int i = 0; i < 2*T; ++i)
        C[i] = nullptr;
}

BTreeNode::~BTreeNode() {
    if (!leaf) {
        for (int i = 0; i <= n; ++i) {
            delete C[i];
        }
    }
}

void BTreeNode::traverse() {
    int i;
    for(i = 0; i < n; ++i) {
        if(!leaf) C[i]->traverse();
        cout << keys[i] << " ";
    }
    if(!leaf) C[i]->traverse();
}

BTreeNode* BTreeNode::searching(int k,int &iterationCount) {
    int i = 0;
    while(i < n && k > keys[i]){
        ++i;
        iterationCount++;
    }
    if(i < n && keys[i] == k) return this;
    if(leaf) return nullptr;
    return C[i]->searching(k,iterationCount);
}

void BTreeNode::insertNonFull(int k,int &iterationCount) {
    int i = n - 1;
    iterationCount++;
    if(leaf) {
        while(i >= 0 && keys[i] > k) {
            iterationCount++;
            keys[i+1] = keys[i];
            --i;
        }
        keys[i+1] = k;
        ++n;
    } else {
        while(i >= 0 && keys[i] > k){
            --i;
            iterationCount++;
        } 
        if(C[i+1]->n == 2*T - 1) {
            splitChild(i+1, C[i+1],iterationCount);
            if(keys[i+1] < k) ++i;
        }
        C[i+1]->insertNonFull(k,iterationCount);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y,int &iterationCount) {
    BTreeNode* z = new BTreeNode(y->leaf);
    z->n = T - 1;
    for(int j = 0; j < T - 1; ++j){
        z->keys[j] = y->keys[j + T];
        iterationCount++;
    }
    if(!y->leaf) {
        for(int j = 0; j < T; ++j){
            z->C[j] = y->C[j + T];
            iterationCount++;
        }
    }
    y->n = T - 1;
    for(int j = n; j >= i+1; --j){
        C[j+1] = C[j];
        iterationCount++;
    }
    C[i+1] = z;
    for(int j = n - 1; j >= i; --j){
        keys[j+1] = keys[j];
        iterationCount++;
    }
    keys[i] = y->keys[T - 1];
    ++n;
}

int BTreeNode::findKey(int k, int &iterationCount) {
    int idx = 0;
    while(idx < n && keys[idx] < k){
        ++idx;
        iterationCount++;
    }
    return idx;
}

void BTreeNode::remove(int k,int &iterationCount) {
    int idx = findKey(k,iterationCount);
    if(idx < n && keys[idx] == k) {
        if(leaf) removeFromLeaf(idx,iterationCount);
        else removeFromNonLeaf(idx, iterationCount);
    } else {
        if(leaf) {
            cout << "La clave " << k << " no existe en el árbol\n";
            return;
        }
        bool flag = (idx == n);
        if(C[idx]->n < T) fill(idx,iterationCount);
        if(flag && idx > n) C[idx-1]->remove(k,iterationCount);
        else C[idx]->remove(k,iterationCount);
    }
}

void BTreeNode::removeFromLeaf(int idx,int &iterationCount) {
    for(int i = idx+1; i < n; ++i){
        keys[i-1] = keys[i];
        iterationCount++;
    }
    --n;
}

void BTreeNode::removeFromNonLeaf(int idx,int &iterationCount) {
    int k = keys[idx];
    if(C[idx]->n >= T) {
        int pred = getPred(idx,iterationCount);
        keys[idx] = pred;
        iterationCount++;
        C[idx]->remove(pred,iterationCount);
    } else if(C[idx+1]->n >= T) {
        int succ = getSucc(idx,iterationCount);
        keys[idx] = succ;
        iterationCount++;
        C[idx+1]->remove(succ,iterationCount);
    } else {
        merge(idx,iterationCount);
        C[idx]->remove(k,iterationCount);
    }
}

int BTreeNode::getPred(int idx,int &iterationCount) {
    BTreeNode* cur = C[idx];
    while(!cur->leaf){
        cur = cur->C[cur->n];
        iterationCount++;
    } 
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSucc(int idx,int &iterationCount) {
    BTreeNode* cur = C[idx+1];
    while(!cur->leaf){
        cur = cur->C[0];
        iterationCount++;
    }
    return cur->keys[0];
}

void BTreeNode::fill(int idx,int &iterationCount) {
    if(idx != 0 && C[idx-1]->n >= T) borrowFromPrev(idx,iterationCount);
    else if(idx != n && C[idx+1]->n >= T) borrowFromNext(idx,iterationCount);
    else {
        if(idx != n) merge(idx,iterationCount);
        else merge(idx-1,iterationCount);
    }
}

void BTreeNode::borrowFromPrev(int idx, int &iterationCount) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx-1];
    for(int i = child->n - 1; i >= 0; --i){
        child->keys[i+1] = child->keys[i];
        iterationCount++;
    }   
    
    if(!child->leaf) {
        for(int i = child->n; i >= 0; --i){
            child->C[i+1] = child->C[i];
            iterationCount++;
        }
    }
    child->keys[0] = keys[idx-1];
    if(!child->leaf) child->C[0] = sibling->C[sibling->n];
    keys[idx-1] = sibling->keys[sibling->n - 1];
    ++child->n;
    --sibling->n;
}

void BTreeNode::borrowFromNext(int idx,int &iterationCount) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx+1];
    child->keys[child->n] = keys[idx];
    if(!child->leaf) child->C[child->n+1] = sibling->C[0];
    keys[idx] = sibling->keys[0];
    for(int i = 1; i < sibling->n; ++i){
        sibling->keys[i-1] = sibling->keys[i];
        iterationCount++;
    } 
    if(!sibling->leaf) {
        for(int i = 1; i <= sibling->n; ++i){
            sibling->C[i-1] = sibling->C[i];
            iterationCount++;
        }
    }
    ++child->n;
    --sibling->n;
}

void BTreeNode::merge(int idx, int &iterationCount) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx+1];
    child->keys[T - 1] = keys[idx];
    for(int i = 0; i < sibling->n; ++i){
        child->keys[i+T] = sibling->keys[i];
        iterationCount++;
    } 
    if(!child->leaf) {
        for(int i = 0; i <= sibling->n; ++i){
            child->C[i+T] = sibling->C[i];
            iterationCount++;
        } 
    }
    for(int i = idx+1; i < n; ++i){
        keys[i-1] = keys[i];
        iterationCount++;
    }
    for(int i = idx+2; i <= n; ++i){
        C[i-1] = C[i];
        iterationCount++;
    }
    child->n += sibling->n + 1;
    --n;
    delete sibling;
}

// Métodos de BTree
BTreeShip::BTreeShip() :Ship("Btree", 300), root(nullptr) {
    generateElements();
}
BTreeShip::~BTreeShip() {
    delete root; // Esto llama a ~BTreeNode() recursivamente
}

void BTreeShip::traverse() {
    if(root) root->traverse();
}

BTreeNode* BTreeShip::searching(int k,int &iterationCount) {
    return (root == nullptr) ? nullptr : root->searching(k, iterationCount);
}

void BTreeShip::insert(int k) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    if(root == nullptr) {
        root = new BTreeNode(true);
        root->keys[0] = k;
        root->n = 1;
        iterationCount++;
    } else {
        if(root->n == 2*T - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->C[0] = root;
            s->splitChild(0, root,iterationCount);
            int i = 0;
            if(s->keys[0] < k) ++i;
            s->C[i]->insertNonFull(k,iterationCount);
            root = s;
        } else {
            root->insertNonFull(k,iterationCount);
        }
    }
    elementSet.insert(k);
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("Insert", iterationCount, execTime);
}

void BTreeShip::remove(int k) {
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    if(!root) {
        cout << "El árbol está vacío\n";
        return;
    }
    root->remove(k,iterationCount);
    if(root->n == 0) {
        BTreeNode* tmp = root;
        if(root->leaf) root = nullptr;
        else root = root->C[0];
        delete tmp;
    }
    elementSet.erase(k);
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("Remove", iterationCount, execTime);
}

void BTreeShip::generateElements(){
    int elements = 0;
    while(elements < NUM_OF_ELEMENTS){
      int value = generateRandom(0,MAX_NUM_ELEMENTS);
      if(elementSet.find(value) == elementSet.end()){
        insert(value);
        elements ++;
      }
    }
  }

  int BTreeShip::search(int k){
    int iterationCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    searching(k, iterationCount);
    auto endTime = std::chrono::high_resolution_clock::now();
    double execTime = std::chrono::duration<double>(endTime - startTime).count();
    logOperation("Search", iterationCount, execTime);
    return iterationCount;
  }
