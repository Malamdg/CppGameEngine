#pragma once

#include "Vector3D.h"
#include "RigidBody.h"

// Node structure for the octree
struct OctreeNode {
    Vector3D min, max;
    list<RigidBody*> rbs;
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
    Octree() : m_root(nullptr) {}
    Octree(const Vector3D& min, const Vector3D& max) : m_root(new OctreeNode(min, max)) {}

    // Insert a point into the octree
    void insert(RigidBody* rb);

    void draw();

    list<OctreeNode*> getLeaves();

private:
    OctreeNode* m_root;

    // Recursive function to insert a point into the octree
    void insertRecursive(OctreeNode* node, RigidBody* rb);

    bool rigidBodyInNode(OctreeNode* node, const RigidBody* rb);

    // Split a node into eight children
    void splitNode(OctreeNode* node);

    void draw(OctreeNode* node);

    list<OctreeNode*> getLeaves(OctreeNode* node);
};
