#include <Contact.h>


Contact::Contact()
	:
	m_contact(false),
	m_contactPoint(nullptr),
	m_normal(nullptr),
	m_penetration(0),
	m_body1(nullptr),
	m_body2(nullptr),
	m_restitution(0),
	m_friction(0)
{ }


Contact::Contact(Vector3D* contactPosition,
	Vector3D* normalContact,
	float penetration,
	RigidBody* body1,
	RigidBody* body2)
	:
	m_contact(true),
	m_contactPoint(contactPosition),
	m_normal(normalContact),
	m_penetration(penetration),
	m_body1(body1),
	m_body2(body2)
{
	m_restitution = calculateRestitution();
	m_friction = calculateFriction();
}

Contact::~Contact()
{
	delete m_contactPoint;
	delete m_normal;
	delete m_body1;
	delete m_body2;
}


bool Contact::hasContact() const { return m_contact; }
Vector3D* Contact::getContactPoint() const { return m_contactPoint; }
Vector3D* Contact::getNormal() const { return m_normal; }
float Contact::getPenetration() const { return m_penetration; }
RigidBody* Contact::getBody(int i) const 
{ 
	if (i == 1) return m_body2;
	return m_body1; 
}
float Contact::getRestitution() const { return m_restitution; }
float Contact::getFriction() const { return m_friction; }

float calculateRestitution()
{
	//TODO
	return 0;
}
float calculateFriction()
{
	//TODO
	return 0;
}
