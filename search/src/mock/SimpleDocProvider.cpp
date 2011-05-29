#include "mock/SimpleDocProvider.h"

#include <fstream>

#include "Logger.h"
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
    ExtensionFilter filter("png");
    try
    {
        base::FsUtil::listFiles(names, path, &filter);
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
    const std::string ext = "descr";

    document.clear();

    size_t dotPos = name.find_last_of('.');
    if(dotPos != std::string::npos && dotPos != name.size()-1)
    {
        std::string descriptionName = name;
        descriptionName.replace(dotPos + 1, name.size() - (dotPos+1),
                ext);

        base::Log().debug("read image description from '%s'",
                descriptionName.c_str());

        try
        {
            base::FsUtil::read(document, descriptionName);
        }
        catch(base::FsUtilError &exc)
        {
            base::Log().warning("description read failed from '%s'",
                    descriptionName.c_str());
            return;
        }

        if(document.size() > 0)
        {
            if(document[document.size()-1] == '\n')
                document.erase(document.size()-1);
        }
    }
    else
    {
        base::Log().warning("invalid document name '%s'",
                name.c_str());
    }
}

}
