
/**
Data loader for nntp protocol
**/
#include "dataloader.hpp"
#include "nntp.h"


#ifndef _NNTP
#define _NNTP

namespace dl
{
    class NNTP : DataLoader
    {
    	NNTP();
    	int update(DataLoaderInfo * info);
    	int update(DataLoaderInfo * info, std::string user, std::string pwd);
    	DataLoaderInfo * init(DataContainer * dc, std::string source);
    	DataLoaderInfo * init(DataContainer * dc, std::string source, std::string user, std::string pwd);
    };
}

#endif // _NNTP
