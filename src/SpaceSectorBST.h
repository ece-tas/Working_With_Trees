#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    //void deleteSubtree(Sector* node);
    Sector* insert(Sector *currentNode, int x, int y, int z);
    void inorder(Sector* currentNode);
    void preorder(Sector* currentNode);
    void postorder(Sector* currentNode);
    Sector* deleteTree(Sector* currentNode);
    std::vector<Sector> allSectors;
    void findSectorCode (Sector* treeNode, const Sector& findNode, std::vector<Sector*> &path);
    Sector* toDelete (Sector*& currentNode, int x, int y, int z);
    Sector* findMin(Sector* currentNode);

};

#endif // SPACESECTORBST_H
