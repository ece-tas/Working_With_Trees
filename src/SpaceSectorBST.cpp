#include "SpaceSectorBST.h"
#include <algorithm>
using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
 //   deleteSubtree(root);
    root = deleteTree(root);
    allSectors.clear();

}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
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

            Sector sector(x,y,z);
            allSectors.push_back(sector);

        }

        file.close();

    } else {
        ostringstream errorMsg;
        errorMsg << "Cannot open the file " << filename;
        cout << errorMsg.str() << endl;
    }
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
    root = insert(root, x, y, z);

}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.

    for (auto& sec : allSectors) {

        if (sec.sector_code == sector_code) {
            root = toDelete(root, sec.x, sec.y, sec.z);

            break;
        }

    }

    allSectors.erase(
            std::remove_if(allSectors.begin(), allSectors.end(),
                           [sector_code](const Sector& sec) {
                               return sec.sector_code == sector_code;
                           }
            ),
            allSectors.end()
    );
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.

    cout<<"Space sectors inorder traversal:"<<endl;
    inorder(root);
    cout << endl;
}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors preorder traversal:"<<endl;
    preorder(root);
    cout << endl;
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout<<"Space sectors postorder traversal:"<<endl;
    postorder(root);
    cout << endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!

    for (auto& sec : allSectors) {
        if (sec.sector_code == sector_code) {
            findSectorCode(root, sec, path);
            break;
        }
    }
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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


Sector* SpaceSectorBST::deleteTree(Sector* currentNode) {
    if(currentNode == nullptr)
        return nullptr;

    deleteTree(currentNode->left);
    deleteTree(currentNode->right);
    delete currentNode;
    return nullptr;


}


Sector* SpaceSectorBST::insert(Sector *currentNode, int x, int y, int z) {
    if (currentNode == nullptr) {
        currentNode =  new Sector(x, y, z);
    }
    else {
        if (x < currentNode->x) {
            currentNode->left = insert(currentNode->left, x, y, z);

        } else if (x > currentNode->x) {
            currentNode->right = insert(currentNode->right, x, y, z);

        } else {
            if (y < currentNode->y) {
                currentNode->left = insert(currentNode->left, x, y, z);

            } else if (y > currentNode->y) {
                currentNode->right = insert(currentNode->right, x, y, z);

            } else {
                if (z < currentNode->z) {
                    currentNode->left = insert(currentNode->left, x, y, z);

                } else if (z > currentNode->z) {
                    currentNode->right = insert(currentNode->right, x, y, z);

                } else {
                    cout<<"Can't two coordinates be same."<<endl;
                }
            }
        }
    }
    return currentNode;
}

void SpaceSectorBST::inorder(Sector* currentNode) {
    if(currentNode == nullptr)
        return;
    inorder(currentNode->left);
    cout << currentNode->sector_code << endl;
    inorder(currentNode->right);
}

void SpaceSectorBST::preorder(Sector* currentNode) {
    if(currentNode == nullptr)
        return;
    cout << currentNode->sector_code << endl;
    preorder(currentNode->left);
    preorder(currentNode->right);
}

void SpaceSectorBST::postorder(Sector* currentNode) {
    if (currentNode == nullptr)
        return;
    postorder(currentNode->left);
    postorder(currentNode->right);
    cout << currentNode->sector_code << endl;
}

void SpaceSectorBST::findSectorCode (Sector* treeNode, const Sector& findNode, vector<Sector*> &path) {
    if (treeNode == nullptr) {
        return;
    }

    path.push_back(treeNode);  // Always add the current node to the path

    if (findNode.x < treeNode->x) {
        findSectorCode(treeNode->left, findNode, path);
    } else if (findNode.x > treeNode->x) {
        findSectorCode(treeNode->right, findNode, path);
    } else {
        if (findNode.y < treeNode->y) {
            findSectorCode(treeNode->left, findNode, path);
        } else if (findNode.y > treeNode->y) {
            findSectorCode(treeNode->right, findNode, path);
        } else {
            if (findNode.z < treeNode->z) {
                findSectorCode(treeNode->left, findNode, path);
            } else if (findNode.z > treeNode->z) {
                findSectorCode(treeNode->right, findNode, path);
            }
        }
    }
}



Sector* SpaceSectorBST::toDelete(Sector*& currentNode, int x, int y, int z) {
    Sector* temp;
    if (currentNode == nullptr) {
        return nullptr;
    }

    if (x < currentNode->x) {
        currentNode->left = toDelete(currentNode->left, x, y, z);
    } else if (x > currentNode->x) {
        currentNode->right = toDelete(currentNode->right, x, y, z);
    } else {
        if (y < currentNode->y) {
            currentNode->left = toDelete(currentNode->left, x, y, z);
        } else if (y > currentNode->y) {
            currentNode->right = toDelete(currentNode->right, x, y, z);
        } else {
            if (z < currentNode->z) {
                currentNode->left = toDelete(currentNode->left, x, y, z);
            } else if (z > currentNode->z) {
                currentNode->right = toDelete(currentNode->right, x, y, z);
            } else {

                // Case 1: Node has two children
                if (currentNode->left && currentNode->right) {
                    temp = findMin(currentNode->right);
                    *currentNode = *temp;  // Use the assignment operator for a deep copy
                    currentNode->distance_from_earth = temp->distance_from_earth;
                    currentNode->right = toDelete(currentNode->right, currentNode->x, currentNode->y, currentNode->z);
                }
                    // Case 2: Node has one child (left or right) or none
                else {
                    temp = currentNode;
                    if (currentNode->left == nullptr) {
                        currentNode = currentNode->right;
                    } else if (currentNode->right == nullptr) {
                        currentNode = currentNode->left;
                    }
                    delete temp;
                }
            }
        }
    }

    return currentNode;
}

// Helper function to find the node with the minimum value in a BST
Sector* SpaceSectorBST::findMin(Sector* currentNode) {
    if(currentNode == nullptr)
        return nullptr;
    else if(currentNode->left == nullptr)
        return currentNode;
    else
        return findMin(currentNode->left);
}


