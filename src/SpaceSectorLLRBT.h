#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    std::vector<Sector> allSectors;
    Sector* insert(Sector* currentNode, int x, int y, int z);
    Sector* rotate_left (Sector* currentNode);
    Sector* rotate_right (Sector* currentNode);
    void flip_color (Sector* currentNode);
    void inorder(Sector* currentNode);
    void preorder(Sector* currentNode);
    void postorder(Sector* currentNode);
    std::string printColor(bool &color);
    Sector* findSectorCode (Sector* treeNode, const Sector& findNode);
    Sector* deleteTree(Sector* currentNode);
    int earth_count = 0;
    Sector* earth = nullptr;
    void findPath(Sector* earthSector, Sector* elara, std::vector<Sector*> &path, std::vector<Sector*> &path2);
    Sector* commonParent(Sector* earthSector, Sector* elara);

    std::vector<Sector*> earthParent;
    std::vector<Sector*> elaraParent;

};

#endif // SPACESECTORLLRBT_H
