#include "Octree.h"

void Octree::insert(RigidBody* rb) {
    insertRecursive(m_root, rb);
}

void Octree::insertRecursive(OctreeNode* node, RigidBody* rb) {
    // If the rigidbody is outside the node's bounding box, ignore it
    if (!rigidBodyInNode(node, rb)) return;

    // If the node is a leaf, insert the point
    if (node->children[0] == nullptr) {
        node->rbs.push_back(rb);

        // Split the node if it has too many points (you can adjust this threshold)
        if (node->rbs.size() > m_maxCount) {
            splitNode(node);
        }
    }
    else {
        // Recursively insert into the appropriate child node
        for (int i = 0; i < 8; ++i) {
            insertRecursive(node->children[i], rb);
        }
    }
}

bool Octree::rigidBodyInNode(OctreeNode* node, const RigidBody* rb)
{
    Vector3D position = rb->getPosition();

    Vector3D halfAxisRight = Vector3D(10, 0, 0);
    Vector3D halfAxisTop = Vector3D(0, 10, 0);
    Vector3D halfAxisForward = Vector3D(0, 0, 10);

    // TODO : Use the vector of the collision box to get the 8 corners
    // The current points are arbitrarily fixed at a certain distance from the object center

    Vector3D corners[8] =
    {
        ((position + halfAxisRight) + halfAxisTop) + halfAxisForward,
        ((position + halfAxisRight) + halfAxisTop) - halfAxisForward,
        ((position + halfAxisRight) - halfAxisTop) + halfAxisForward,
        ((position + halfAxisRight) - halfAxisTop) - halfAxisForward,
        ((position - halfAxisRight) + halfAxisTop) + halfAxisForward,
        ((position - halfAxisRight) + halfAxisTop) - halfAxisForward,
        ((position - halfAxisRight) - halfAxisTop) + halfAxisForward,
        ((position - halfAxisRight) - halfAxisTop) - halfAxisForward,
    };

    for (Vector3D corner : corners)
    {
        // If the corner isn't in the node, we skip the end of the for loop
        if (corner.x() < node->min.x() || corner.x() > node->max.x() ||
            corner.y() < node->min.y() || corner.y() > node->max.y() ||
            corner.z() < node->min.z() || corner.z() > node->max.z())
        {
            continue;
        }

        // else, we return true because the object is at least partially in the node
        return true;
    }

    // If no corner was found in the node, we return false
    return false;
}

void Octree::splitNode(OctreeNode* node) {
    Vector3D mid = { (node->min.x() + node->max.x()) / 2,
                  (node->min.y() + node->max.y()) / 2,
                  (node->min.z() + node->max.z()) / 2};

    // Create eight children
    for (int i = 0; i < 8; ++i) {
        Vector3D childMin, childMax;

        childMin.x((i & 1) ? mid.x() : node->min.x());
        childMax.x((i & 1) ? node->max.x() : mid.x());

        childMin.y((i & 2) ? mid.y() : node->min.y());
        childMax.y((i & 2) ? node->max.y() : mid.y());

        childMin.z((i & 4) ? mid.z() : node->min.z());
        childMax.z((i & 4) ? node->max.z() : mid.z());

        node->children[i] = new OctreeNode(childMin, childMax);
    }

    // Distribute points to the children
    for (const auto& point : node->rbs) {
        insertRecursive(node, point);
    }
    node->rbs.clear();
}

void Octree::draw()
{
    draw(m_root);
}

void Octree::draw(OctreeNode* node)
{
    // If the node is a leaf
    if (node->children[0] == nullptr)
    {
        // Thend we draw it
        float dimension = node->max.x() - node->min.x();
        Vector3D nodeCenterPosition = Vector3D(node->min.x() + dimension / 2, node->min.y() + dimension / 2, node->min.z() + dimension / 2);

        ofSetColor(ofColor(0, 255, 255));
        ofDrawBox(nodeCenterPosition.v3(), dimension);

        return;
    }

    // else we draw its children
    for (OctreeNode* child : node->children)
    {
        draw(child);
    }
}

list<OctreeNode*> Octree::getLeaves()
{
    return getLeaves(m_root);
}

list<OctreeNode*> Octree::getLeaves(OctreeNode* node)
{
    list<OctreeNode*> leaves = list<OctreeNode*>();
    // If node is a leaf
    if (node->children[0] == nullptr) {
        // Then we return it
        leaves.push_back(node);
        return leaves;
    }

    // Else add children's leaves to node's
    for (OctreeNode* child : node->children) {
        leaves.merge(getLeaves(child));
    }

    return leaves;
}