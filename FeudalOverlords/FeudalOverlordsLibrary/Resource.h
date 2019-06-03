#pragma once
class Resource
{
public:
	Resource(int maxAmount, ResourceType type);
	~Resource();
	void setCurrentAmount(int amount);
	void resetAmount();
	ResourceType getType();
private:
	int maxAmount;
	int currentAmount;
	ResourceType type;
};

enum ResourceType
{
	money,
	military
};