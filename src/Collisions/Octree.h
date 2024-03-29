#pragma once

#include "Vector3D.h"
#include "GameObject.h"

// Node structure for the octree
struct OctreeNode {
    Vector3D min, max;
    list<GameObject*> gameObjects;
    // There is 8 children because we are in 3D
    OctreeNode* children[8];

    OctreeNode(const Vector3D& min, const Vector3D& max) : min(min), max(max) {
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }
};

class Octree
{
private:
    int m_maxCount = 8;

public:
    /*
    Empty Constructor
    */
    Octree() : m_root(nullptr) {}

    /*
    Class Constructor

    @param min, the initial lower boundary of the octree
    @param max, the initial upper boundary of the octree
    */
    Octree(const Vector3D& min, const Vector3D& max) : m_root(new OctreeNode(min, max)) {}

    /*
    To insert a RigidBody in the Octree

    @param rb, the RigidBody to add
    */
    void insert(GameObject* rb);

    /*
    To draw the octree
    */
    void draw();

    /*
    to get the leaves of the curent octree's root

    @return a list of the leaves of the root
    */
    list<OctreeNode*> getLeaves();

private:
    /*
    the first node
    */
    OctreeNode* m_root;

    /*
    Recursive function to insert a point into the octree

    @param node, the node where the RigidBody is added
    @param rb, the RigidBody to add
    */
    void insertRecursive(OctreeNode* node, GameObject* rb);

    /*
    Function to determine if a RigidBody is in a node

    @param node, the node checked
    @param rb, the RigidBody to check
    @return true if the rigidbody is in the node
    */
    bool gameObjectInNode(OctreeNode* node, GameObject* rb);

    /*
    Function to split the node in eight

    @param node, the node to split
    */
    void splitNode(OctreeNode* node);

    /*
    To draw the octree
    */
    void draw(OctreeNode* node);

     /*
    to get the leaves of the specified octree's node

    @return a list of the leaves of the specified node
    */
    list<OctreeNode*> getLeaves(OctreeNode* node);
};
