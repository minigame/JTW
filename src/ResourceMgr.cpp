#include "ResourceMgr.h"


ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
}

ResourceMgr* ResourceMgr::getInstance()
{
	return m_instance;
}
