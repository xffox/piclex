#include "FsDocProvider.h"

#include <fstream>

#include "FsUtil.h"

namespace search
{
void FsDocProvider::listNames(std::vector<std::string> &names,
        const std::string &path) const
{
    try
    {
        base::FsUtil::listFiles(names, path);
    }
    catch(base::FsUtilError &exc)
    {
        throw DocProviderError();
    }

    std::vector<std::string>::iterator namesIter = names.begin();
    for(; namesIter != names.end(); ++namesIter)
    {
        namesIter->insert(0, "/");
        namesIter->insert(0, path);
    }
}

void FsDocProvider::read(Document &document, const std::string &name) const
{
    document.clear();

    std::ifstream infile(name.c_str());
    if(!infile.is_open())
        throw DocProviderError();

    const size_t bufSize = 4096;
    char buf[bufSize];

    do
    {
        infile.read(buf, bufSize);
        if(infile.bad())
            throw DocProviderError();
        document.append(buf, infile.gcount());
    }while(!infile.eof());
}

}
