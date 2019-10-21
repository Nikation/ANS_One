#pragma once
#include"Codec.h"
class FactoryCode
{
public:
	FactoryCode();
	~FactoryCode();

public:
	virtual Codec * CreateCode(void * agv);
};

