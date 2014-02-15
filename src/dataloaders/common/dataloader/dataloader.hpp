// insert copyright

/**
Virtual class which defines the interface each data loaders MUST implement.
**/

#ifndef _DATALOADER
#define _DATALOADER

namespace dl{
    struct DataLoaderInfo
    {
        DataContainer *dc;
        std::string source;
        std::string name;
        std::string loader_name;
    };

    virtual class DataLoader
    {
    public:
        virtual DataLoader();
        ~DataLoader() { delete defaultSchema; }
        virtual int update(DataLoaderInfo * info);
        virtual int update(DataLoaderInfo * info, std::string user, std::string pwd);
        virtual DataLoaderInfo * init(DataContainer * dc, std::string source);
        virtual DataLoaderInfo * init(DataContainer * dc, std::string source, std::string user, std::string pwd);
        ModelSchema *defaultSchema;
    }

}
#endif // _DATALOADER
