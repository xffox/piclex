#ifndef SIMPLE_DOC_PROVIDER_H
#define SIMPLE_DOC_PROVIDER_H

#include "DocProvider.h"

namespace search
{
class SimpleDocProvider: public DocProvider
{
public:
    virtual void listNames(std::vector<std::string> &names,
            const std::string &path) const;

    virtual void read(Document &document, const std::string &name) const;
};

}

#endif//SIMPLE_DOC_PROVIDER_H
