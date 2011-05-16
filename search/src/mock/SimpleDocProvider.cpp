#include "mock/SimpleDocProvider.h"

#include <fstream>

#include "FsUtil.h"

namespace
{
class ExtensionFilter: public base::FsFilter
{
public:
    ExtensionFilter(const std::string &extension)
        :mDotExtension(extension)
    {
        if(extension.length() == 0)
            throw base::InvalidArgument();

        mDotExtension.insert(0, ".");
    }

    bool isValid(const std::string &str)
    {
        // dot at the beginning of the word is not the extension delimeter dot
        if(str.length() <= mDotExtension.length())
            return false;

        return !str.compare(str.length() - mDotExtension.length(),
                mDotExtension.length(), mDotExtension);
    }

private:
    std::string mDotExtension;
};
}

namespace search
{
void SimpleDocProvider::listNames(std::vector<std::string> &names,
        const std::string &path) const
{
    ExtensionFilter filter("jpg");
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

void SimpleDocProvider::read(Document &document, const std::string &name) const
{
    document = name;

    size_t pos = 0;
    while((pos = document.find('/', pos)) != std::string::npos)
    {
        document[pos] = ' ';
        ++pos;
    }
}

}
