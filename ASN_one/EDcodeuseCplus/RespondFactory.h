#pragma once
#include "FactoryCode.h"
class RespondFactory :
	public FactoryCode
{
public:
	RespondFactory();
	~RespondFactory();

	Codec * CreateCode(void * agv);
};

