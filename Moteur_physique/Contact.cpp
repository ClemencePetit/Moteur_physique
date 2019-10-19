#include "Contact.h"

Contact Contact::getContact(Sphere s1, Sphere s2)
{
	float restit = 0.95f;

	float distAB = s1.getPos().distanceWith(s2.getPos());
	float cumulatedRadius = s1.getRadius() + s2.getRadius();

	if (distAB < cumulatedRadius) {

		//PARAMETERS, TO MOVE

		float dPene = cumulatedRadius - distAB;
		Vector3D n = s2.getPos() - s1.getPos();

		return Contact(dPene, n); //use restit?

	}
	else {
		return Contact();
	}

}

Contact Contact::getContact(Rect3D rect1, Rect3D rect2)
{
	return Contact();
}

Contact Contact::getContact(Sphere sphere, Rect3D rect)
{
	float restit = 0.75f;

	//sphere and rect
	Vector3D minRect = rect.getMinPos();
	Vector3D maxRect = rect.getMaxPos();

	Vector3D nearestPoint(
		std::fmaxf(minRect.x, std::fminf(sphere.getPos().x, maxRect.x)),
		std::fmaxf(minRect.y, std::fminf(sphere.getPos().y, maxRect.y)),
		std::fmaxf(minRect.z, std::fminf(sphere.getPos().z, maxRect.z))
	);

	Vector3D delta(
		sphere.getPos().x - nearestPoint.x,
		sphere.getPos().y - nearestPoint.y,
		sphere.getPos().z - nearestPoint.z
	);

	float cornerDistanceSq = std::powf(delta.x, 2.f) + std::powf(delta.y, 2.f) + std::powf(delta.z, 2.f);


	if (cornerDistanceSq < std::powf(sphere.getRadius(), 2.f))
	{
		float dPene = std::sqrt(cornerDistanceSq);
		Vector3D n = nearestPoint - sphere.getPos();

		//restite?
		return Contact(dPene, n);
	}
	else {
		return Contact();
	}

}

Contact Contact::getContact(Rect3D rect, Sphere sphere)
{
	return getContact(sphere, rect);
}
