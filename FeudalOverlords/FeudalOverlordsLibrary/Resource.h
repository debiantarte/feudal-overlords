#pragma once

enum ResourceType
{
	money,
	military
};

class Resource
{
public:
	Resource(int maxAmount, ResourceType type);
	~Resource();
	void setCurrentAmount(int amount);
	void resetAmount();
	ResourceType getType();
	void setAmount(int);
	int getAmount() const;
private:
	int maxAmount;
	int currentAmount;
	ResourceType type;
};