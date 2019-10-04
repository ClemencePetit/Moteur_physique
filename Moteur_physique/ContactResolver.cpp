#include "ContactResolver.h"

ContactResolver::ContactResolver()
{
}

ContactResolver::~ContactResolver()
{
	while (!contacts_.empty()) {
		deleteContact(contacts_.front());
	}
}

void ContactResolver::resolveContacts(float t) {
	while (!contacts_.empty()) {
		contacts_.front()->resolve(t);
		deleteContact(contacts_.front());
		iterUsed_ += 1;
	}
}

void ContactResolver::deleteContact(ParticleContact* paC) {
	contacts_.remove(paC);
	delete(paC);
}