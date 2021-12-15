#include "Collider.h"

Collider::Collider() {}


//bool Collider::Collide(Actor a, Actor b)
//{
//	Vec4 intersect = { 0, 0, 0, 0 };
//
//	intersect.x = std::max(a.getPos().x, b.getPos().x);
//	intersect.z = std::min(a.getPos().x + a.getCurrentFrame().w, b.getPos().x + b.getCurrentFrame().w);
//	intersect.y = std::max(a.getPos().y, b.getPos().y);
//	intersect.w = std::min(a.getPos().y + a.getCurrentFrame().h, b.getPos().y + b.getCurrentFrame()h);
//
//	if (intersect.x < intersect.z && intersect.y < intersect.w)
//	{
//		//intersect = { leftX, topY, rightX - leftX, bottomY - topY };
//		return true;
//	}
//
//	return false;
//}

bool Collider::Collide(Vec4 a, Vec4 b)
{
	Vec4 intersect = { 0, 0, 0, 0 };

	intersect.x = std::max(a.x, b.x);
	intersect.z = std::min(a.x + (a.x + a.z), b.x + (b.x + b.z));
	intersect.y = std::max(a.y, b.y);
	intersect.w = std::min(a.y + (a.y + a.w), b.y + (b.y + b.w));

	if (intersect.x < intersect.z && intersect.y < intersect.w)
	{
		//intersect = { leftX, topY, rightX - leftX, bottomY - topY };
		return true;
	}

	return false;
}