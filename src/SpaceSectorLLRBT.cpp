#include "SpaceSectorLLRBT.h"
#include <algorithm>

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison criteria based on the sector coordinates.

    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            istringstream iss(line);
            vector<string> tokens;
            string token;

            // Split the line into tokens based on commas
            while (getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            int x = stoi(tokens[0]);
            int y = stoi(tokens[1]);
            int z = stoi(tokens[2]);

            insertSectorByCoordinates(x, y, z);

            Sector sector(x, y, z);
            allSectors.push_back(sector);

        }
        file.close();
    }
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    root = deleteTree(root);
    allSectors.clear();
    earth = nullptr;
    delete earth;

}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map
    // according to the coordinates-based comparison criteria.
    root = insert(root, x,y,z);
    if (earth_count == 1) {
        earth = root;
    }
    root->color = BLACK; // Ensure the root is always black
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors
    // to STDOUT in the given format.
    cout<<"Space sectors inorder traversal:"<<endl;
    inorder(root);
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors preorder traversal:"<<endl;
    preorder(root);
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors postorder traversal:"<<endl;
    postorder(root);
    cout << endl;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    Sector* sectorFound;
    std::vector<Sector*> path2;
    bool found = false;
    for (auto& sec : allSectors) {

        if (sec.sector_code == sector_code) {
            sectorFound = findSectorCode(root, sec);
            found = true;
            break;
        }
    }if (found) {
        findPath(earth, sectorFound, path, path2);
    }

    return path;
}


Sector* SpaceSectorLLRBT::commonParent(Sector* earthSector, Sector* elara) {
    if (earthSector == nullptr || elara == nullptr) {
        return nullptr;  // Handle the case where either sector is nullptr
    }

    // Reset vectors before each call
    earthParent.clear();
    elaraParent.clear();

    while (earthSector != nullptr) {
        earthParent.push_back(earthSector);
        earthSector = earthSector->parent;
    }

    while (elara != nullptr) {
        elaraParent.push_back(elara);
        elara = elara->parent;
    }

    Sector* temp;

    for (auto earthP : earthParent) {
        for (auto elaraP : elaraParent) {
            if (earthP == elaraP) {
                temp = elaraP;
                return temp;
            }
        }
    }

    return nullptr;
}
void SpaceSectorLLRBT::findPath(Sector* earthSector, Sector* elara, std::vector<Sector*>& path, std::vector<Sector*>& path2) {
    Sector* common = commonParent(earthSector, elara);

    if (earthSector == elara) {
        path.push_back(earthSector);
        return;
    } else if (common != nullptr) {
        // Path from earthSector to common parent
        while (earthSector != common) {
            path.push_back(earthSector);
            earthSector = earthSector->parent;
        }

        // Include the common sector in the path
        path.push_back(common);

        // Path from elara to common parent
        while (elara != common) {
            path2.push_back(elara);
            elara = elara->parent;
        }

        // Reverse the second path
        std::reverse(path2.begin(), path2.end());

        // Combine the two paths
        path.insert(path.end(), path2.begin(), path2.end());
    }
}


void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function
    // to STDOUT in the given format.
    if (!path.empty()) {
        cout << "The stellar path to Dr. Elara: ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i]->sector_code;
            if (i < path.size() - 1) {
                cout << "->";
            }
        }   cout << endl<<endl;
    } else {
        cout<<"A path to Dr. Elara could not be found."<<endl<<endl;
    }
}

Sector* SpaceSectorLLRBT::insert(Sector* currentNode, int x, int y, int z) {
    if (currentNode == nullptr) {
        earth_count++;
        return new Sector(x, y, z);
    }


    if (x < currentNode->x) {
        currentNode->left = insert(currentNode->left, x, y, z);
        currentNode->left->parent = currentNode;

    } else if (x > currentNode->x) {
        currentNode->right = insert(currentNode->right, x, y, z);
        currentNode->right->parent = currentNode;

    } else {
        if (y < currentNode->y) {
            currentNode->left = insert(currentNode->left, x, y, z);
            currentNode->left->parent = currentNode;

        } else if (y > currentNode->y) {
            currentNode->right = insert(currentNode->right, x, y, z);
            currentNode->right->parent = currentNode;

        } else {
            if (z < currentNode->z) {
                currentNode->left = insert(currentNode->left, x, y, z);
                currentNode->left->parent = currentNode;

            } else if (z > currentNode->z) {
                currentNode->right = insert(currentNode->right, x, y, z);
                currentNode->right->parent = currentNode;

            } else {
                cout<<"Can't two coordinates be same."<<endl;
            }
        }
    } if (currentNode->right != nullptr && currentNode->right->color) {
        if (currentNode->left != nullptr && !currentNode->left->color) {
            currentNode = rotate_left(currentNode);
        } else if (currentNode->left == nullptr) {
            currentNode = rotate_left(currentNode);
        }
    } if (currentNode->left->left != nullptr && currentNode->left != nullptr && currentNode->left->color && currentNode->left->left->color) {
        currentNode = rotate_right(currentNode);
    } if (currentNode->left != nullptr && currentNode->right != nullptr && currentNode->right->color && currentNode->left->color) {
        flip_color(currentNode);
    }

return currentNode;
}

Sector* SpaceSectorLLRBT::rotate_left (Sector* currentNode) {
    Sector* tempParent = currentNode->parent;
    Sector* temp = currentNode->right;
    currentNode->parent = temp;
    currentNode->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = currentNode;
    }
    temp->left = currentNode;
    temp->parent = tempParent;
    temp->color = currentNode->color;
    currentNode->color = RED;
    return temp;
}

Sector* SpaceSectorLLRBT::rotate_right (Sector* currentNode) {
    Sector* tempParent = currentNode->parent;
    Sector* temp = currentNode->left;
    currentNode->parent = temp;
    currentNode->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = currentNode;
    }
    temp->right = currentNode;
    temp->parent = tempParent;
    temp->color = currentNode->color;
    currentNode->color = RED;
    return temp;
}

void SpaceSectorLLRBT::flip_color (Sector* currentNode) {
    currentNode->color = RED;
    currentNode->right->color = BLACK;
    currentNode->left->color = BLACK;

}

void SpaceSectorLLRBT::inorder(Sector* currentNode) {
    if(currentNode == nullptr)
        return;
    inorder(currentNode->left);
    cout << printColor(currentNode->color) << " sector: " << currentNode->sector_code << endl;
    inorder(currentNode->right);
}

void SpaceSectorLLRBT::preorder(Sector* currentNode) {
    if(currentNode == nullptr)
        return;
    cout << printColor(currentNode->color) << " sector: " << currentNode->sector_code << endl;
    preorder(currentNode->left);
    preorder(currentNode->right);
}

void SpaceSectorLLRBT::postorder(Sector* currentNode) {
    if (currentNode == nullptr)
        return;
    postorder(currentNode->left);
    postorder(currentNode->right);
    cout << printColor(currentNode->color) << " sector: " << currentNode->sector_code << endl;
}

string SpaceSectorLLRBT::printColor(bool &color) {
    if (color)
        return "RED";
    else
        return "BLACK";
}


Sector* SpaceSectorLLRBT::findSectorCode (Sector* treeNode, const Sector& findNode) {
    if (treeNode == nullptr) {
        return nullptr;
    }

    if (findNode.x < treeNode->x) {
        return findSectorCode(treeNode->left, findNode);
    } else if (findNode.x > treeNode->x) {
        return findSectorCode(treeNode->right, findNode);
    } else {
        if (findNode.y < treeNode->y) {
            return findSectorCode(treeNode->left, findNode);
        } else if (findNode.y > treeNode->y) {
            return findSectorCode(treeNode->right, findNode);
        } else {
            if (findNode.z < treeNode->z) {
                return findSectorCode(treeNode->left, findNode);
            } else if (findNode.z > treeNode->z) {
                return findSectorCode(treeNode->right, findNode);
            }
        }
    }
   return treeNode;
}



Sector* SpaceSectorLLRBT::deleteTree(Sector* currentNode) {
    if (currentNode == nullptr) {
        return nullptr;
    } else {

        currentNode->left = deleteTree(currentNode->left);
        currentNode->right = deleteTree(currentNode->right);

        // If you maintain parent pointers, update them here
        if (currentNode->left != nullptr) {
            currentNode->left->parent = currentNode;
        }
        if (currentNode->right != nullptr) {
            currentNode->right->parent = currentNode;
        }

        delete currentNode;
        return nullptr;
    }
}
