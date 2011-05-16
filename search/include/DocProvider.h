#ifndef DOC_PROVIDER_H
#define DOC_PROVIDER_H

#include <string>
#include <vector>

#include "BaseExceptions.h"
#include "SearchDefines.h"

namespace search
{
class DocProviderError: public base::BaseException
{
};

class DocProvider
{
public:
    virtual void listNames(std::vector<std::string> &names,
            const std::string &path) const = 0;

    virtual void read(Document &document, const std::string &name) const = 0;
};

}

#endif//DOC_PROVIDER_H
