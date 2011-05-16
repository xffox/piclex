#ifndef FS_DOC_PROVIDER_H
#define FS_DOC_PROVIDER_H

#include "DocProvider.h"

namespace search
{
class FsDocProvider: public DocProvider
{
public:
    virtual void listNames(std::vector<std::string> &names,
            const std::string &path) const;

    virtual void read(Document &document, const std::string &name) const;
};

}

#endif//FS_DOC_PROVIDER_H
