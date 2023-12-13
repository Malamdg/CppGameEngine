#pragma once

#include "Vector3D.h"
#include "RigidBody.h"

// Node structure for the octree
struct OctreeNode {
    Vector3D min, max;
    list<RigidBody*> rbs;
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
    int m_maxCount = 1;

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
    void insert(RigidBody* rb);

    /*
    To draw the octree
    */
    void draw();

    list<OctreeNode*> getLeaves();

private:
    OctreeNode* m_root;

    /*
    Recursive function to insert a point into the octree

    @param node, the node where the RigidBody is added
    @param rb, the RigidBody to add
    */
    void insertRecursive(OctreeNode* node, RigidBody* rb);

    /*
    Function to determine if a RigidBody is in a node

    @param node, the node checked
    @param rb, the RigidBody to check
    @return true if the rigidbody is in the node
    */
    bool rigidBodyInNode(OctreeNode* node, const RigidBody* rb);

    /*
    Function to split the node in eight

    @param node, the node to split
    */
    void splitNode(OctreeNode* node);

    /*
    To draw the octree
    */
    void draw(OctreeNode* node);

    list<OctreeNode*> getLeaves(OctreeNode* node);
};
