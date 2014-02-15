// insert copyright

/**
Virtual class which defines the interface each data containers MUST implement.
**/

#ifndef _DATACONTAINER
#define _DATACONTAINER

#define ISMASTER (this->master == NULL)

namespace dc {

	struct DataContainerInfo {
		std::string name;
		std::string container_name;
		std::string location;
	};

	virtual class DataContainer 
	{
	public:
		DataContainer(std::string location);
		DataContainer(DataContainer * master, std:string location);
		
		std::string newKey() { return(itoa(currentKey++)); }
		
		int newContainer(DataContainerInfo * info);
		
		int newModel(std::string modelName, ModelSchema * modelSchema);
		int newLoader(DataLoaderInfo * info);
		
		ModelKey * getNewKey(std::string modelName);
		int updateKey(std::string modelName, ModelKey * key, std::string value);
		int updateKey(std::string modelName, ModelKey * key, int value);
		
	protected:
		int id;
		static int currentKey;
		DataContainer * master;
	};

}

#endif // _DATACONTAINER

