//
// Created by malam on 05/09/2023.
//

#ifndef CPP_VECTOR_H
#define CPP_VECTOR_H

#include "ofMain.h"

class Vector {
    //////////////////
    /// Attributes ///
    //////////////////
    private: float x, y, z, w;

    /////////////////
    /// Functions ///
    /////////////////
    public: Vector(float x=0, float y=0, float z=0, float w=0);

    // Attributes getters and setters
    public: float getX() const;
    public: void setX(float x_);
    public: float getY() const;
    public: void setY(float y_);
    public: float getZ() const;
    public: void setZ(float z_);    
    public: float getW() const;
    public: void setW(float w_);

    // Basic operations on vectors
    // In place operations - update attributes
    public: Vector operator*(float k);
    public: float operator*(Vector v);
    public: Vector operator+(Vector v);
    public: Vector operator-(Vector v);
    public: Vector operator^(Vector v);

    public: void operator+=(Vector v);
    public: void operator-=(Vector v);
    public: void operator*=(Vector v);
    public: bool operator==(Vector v);

    public: float norm() const;
    public: float squaredNorm() const;
    public: void normalize();

    public: glm::vec3 v3();

    // Products
    public: float scalarProduct(Vector v) const;
    public: Vector vectorProduct(Vector v) const;
};

#endif //CPP_VECTOR_H
