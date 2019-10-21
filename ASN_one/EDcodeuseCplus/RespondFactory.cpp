#include "RespondFactory.h"

#include"RespondCodec.h"

RespondFactory::RespondFactory()
{
}


RespondFactory::~RespondFactory()
{
}

Codec * RespondFactory::CreateCode(void * agv)
{
	Codec* code = NULL;
	if (NULL == agv)
	{
		code = new RespondCodec;
	}
	else
	{

	}


	return NULL;
}
