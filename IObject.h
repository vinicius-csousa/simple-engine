#pragma once
class IObject
{
public:
	virtual void Draw() = 0;
	virtual void Update(float dt = 0) = 0;
	virtual void Clear() = 0;

};

