//
// Created by malam on 05/09/2023.
//

#include "Vector.h"
#include "ofMain.h"

Vector::Vector(float x, float y, float z, float w) : 
    x(x), y(y), z(z), w(w)
{ }

/**
 * Getter of param x
 *
 * @return float
 */
float Vector::getX() const {
    return x;
}

/**
 * Setter for param x
 *
 * @param float x_
 */
void Vector::setX(float x_) {
    this->x = x_;
}

/**
 * Getter of param y
 *
 * @return float
 */
float Vector::getY() const {
    return y;
}

/**
 * Setter for param y
 *
 * @param float y_
 */
void Vector::setY(float y_) {
    this->y = y_;
}

/**
 * Getter of param z
 *
 * @return float
 */
float Vector::getZ() const {
    return z;
}

/**
 * Setter for param z
 *
 * @param float z_
 */
void Vector::setZ(float z_) {
    this->z = z_;
}

/**
 * Getter of param W
 *
 * @return float
 */
float Vector::getW() const {
    return z;
}

/**
 * Setter for param w
 *
 * @param float w_
 */
void Vector::setW(float w_) {
    this->w = w_;
}

/**
 * Return norm of this
 *
 * @return float
 */
float Vector::norm() const {
    return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
}

/**
 * Return squared value of vector norm
 *
 * @return float
 */
float Vector::squaredNorm() const {
    return this->norm();
}

/**
 * Normalize this, if (0, 0, 0) return
 */
void Vector::normalize() {
    // Prevent division by zero
    if (this->norm() == 0) {
        return;
    }

    this->operator*(1/this->norm());
}


/**
 * Multiply this by a scalar k
 *
 * @param float k
 */
Vector Vector::operator*(float k) {
    return {
        k * this->getX(),
        k * this->getY(),
        k * this->getZ(),
        this->getW()
    };
}

/**
 * Return the scalar product between this and another vector
 *
 * @param v
 * @return
 */
float Vector::operator*(Vector v) {
    return this->getX() * v.getX()
        + this->getY() * v.getY()
        + this->getZ() * v.getZ()
    ;
}

/**
 * Add other vector v to this
 *
 * @param Vector v
 */
Vector Vector::operator+(Vector v) {
    return {
        this->getX() + v.getX(),
        this->getY() + v.getY(),
        this->getZ() + v.getZ(),
        this->getW()
    };
}

/**
 * Subtract other vector v from this
 *
 * @param Vector v
 */
Vector Vector::operator-(Vector v) {
    return {
        this->getX() - v.getX(),
        this->getY() - v.getY(),
        this->getZ() - v.getZ(),
        this->getW()
    };
}

/**
 * Return the result of vectorial product between this and an other vector v
 * i.e : this ^ v
 *
 * @param Vector v
 * @return Vector
 */
Vector Vector::operator^(Vector v) {
    return
        {
            this->getY()*v.getZ() - v.getY()*this->getZ(),
            this->getZ()*v.getX() - v.getZ()*this->getX(),
            this->getX()*v.getY() - v.getX()*this->getY()
        }
    ;
}

/**
* += operator
*/
void Vector::operator+=(Vector v) {
    Vector u = this->operator+(v);
    this->setX(u.getX());
    this->setY(u.getY());
    this->setZ(u.getZ());
}

/**
* -= operator
*/
void Vector::operator-=(Vector v) {
    Vector u = this->operator-(v);
    this->setX(u.getX());
    this->setY(u.getY());
    this->setZ(u.getZ());
}

/**
* *= operator
*/
void Vector::operator*=(Vector v) {
    Vector u = this->operator*(v);
    this->setX(u.getX());
    this->setY(u.getY());
    this->setZ(u.getZ());
}

/**
* == operator
*/
bool Vector::operator==(Vector v) {
    return this->getX() == v.getX() && this->getY() == v.getY() && this->getZ() == v.getZ();
}


glm::vec3 Vector::v3() {
    return glm::vec3(this->getX(), this->getY(), this->getZ());
}