#include "Octree.h"

void Octree::insert(GameObject* rb) {
    insertRecursive(m_root, rb);
}

void Octree::insertRecursive(OctreeNode* node, GameObject* rb) {
    // If the rigidbody is outside the node's bounding box, ignore it
    if (!gameObjectInNode(node, rb)) return;

    // If the node is a leaf, insert the point
    if (node->children[0] == nullptr) {
        node->gameObjects.push_back(rb);

        // Split the node if it has too many points (you can adjust this threshold)
        if (node->gameObjects.size() > m_maxCount) {
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

bool Octree::gameObjectInNode(OctreeNode* node, GameObject* rb)
{
    Sphere* encompassingSphere = rb->getSphere();
    Vector3D position = encompassingSphere->getPosition();

    float nodeDimension = node->max.x() - node->min.x();
    Vector3D nodeCenter = node->min + Vector3D(nodeDimension / 2, nodeDimension / 2, nodeDimension / 2);

    // Get the point on the surface of the sphere closest to the center of the node
    Vector3D sphereToNode = nodeCenter - encompassingSphere->getPosition();
    sphereToNode.Normalize();
    sphereToNode = sphereToNode * encompassingSphere->getRadius();
    Vector3D closestPoint = encompassingSphere->getPosition() + sphereToNode;

    // If the point is in the node, we return true
    if (closestPoint.x() > node->min.x() && closestPoint.x() < node->max.x() &&
        closestPoint.y() > node->min.y() && closestPoint.y() < node->max.y() &&
        closestPoint.z() > node->min.z() && closestPoint.z() < node->max.z())
    {
        return true;
    }
    
    // else we return false
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

    // else we draw it's children
    for (OctreeNode* child : node->children)
    {
        draw(child);
    }
}