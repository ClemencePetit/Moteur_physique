

#ifndef CONTACT
#define CONTACT

#include "Vector3D.h"
#include "Shape.h"

class Contact
{
public:
	bool hasContact_;
	float dPene_;
	Vector3D n_;

	Contact(float dPene, Vector3D n) : hasContact_(true), dPene_(dPene), n_(n) {

	}

	Contact() : hasContact_(false), dPene_(0), n_(Vector3D()) {

	}

	~Contact() {}

	static Contact getContact(Sphere sphere1, Sphere sphere2);
	static Contact getContact(Rect3D rect1, Rect3D rect2);
	static Contact getContact(Sphere sphere, Rect3D rect);
	static Contact getContact(Rect3D rect, Sphere sphere);

};

#endif

