#pragma once
#include "FactoryCode.h"
class RequestFactory :
	public FactoryCode
{
public:
	RequestFactory();
	~RequestFactory();
	Codec* CreateCode(void * agv = NULL);
};

