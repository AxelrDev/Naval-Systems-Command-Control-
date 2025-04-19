#ifndef BREESHIP_H
#define BTREESHIP_H

#include "Ship.h"
#include "Includes.h"

#define MAX 4
#define MIN 2

class BTreeShip : public Ship {
    private:
        struct BTreeNode {
            int val[MAX + 1], count;
            BTreeNode* link[MAX + 1];
        };
    
        BTreeNode* root;
        std::vector<int> elements;
    
        BTreeNode* createNode(int val, BTreeNode* child);
        void addValToNode(int val, int pos, BTreeNode* node, BTreeNode* child);
        void splitNode(int val, int* pval, int pos, BTreeNode* node, BTreeNode* child, BTreeNode** newNode);
        int setValueInNode(int val, int* pval, BTreeNode* node, BTreeNode** child);
        int delValFromNode(int val, BTreeNode* myNode);
    
        void copySuccessor(BTreeNode* myNode, int pos);
        void removeVal(BTreeNode* myNode, int pos);
        void doRightShift(BTreeNode* myNode, int pos);
        void doLeftShift(BTreeNode* myNode, int pos);
        void mergeNodes(BTreeNode* myNode, int pos);
        void adjustNode(BTreeNode* myNode, int pos);
        void searchingRecursive(int val, int* pos, BTreeNode* myNode);
        void traversal(BTreeNode* myNode);
    
    public:
        BTreeShip(std::string name, int price);
        ~BTreeShip();
    
        int search(int target) override;
        void insert(int element) override;
        void remove(int element) override;
    };



#endif