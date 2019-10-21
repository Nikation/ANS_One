#include "RequestFactory.h"
#include"RequestCodec.h"


RequestFactory::RequestFactory()
{
}


RequestFactory::~RequestFactory()
{
}

Codec* RequestFactory::CreateCode(void * agv) {
	Codec *code = NULL;
	if (NULL == agv)
	{
		code = new RequestCodec;
	}
	else
	{
		code = new RequestCodec((RequestMsg*)agv);
	}

	return code;
}