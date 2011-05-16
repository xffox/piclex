#ifndef FS_UTIL_H
#define FS_UTIL_H

#include <vector>
#include <string>

#include "BaseExceptions.h"

namespace base
{
class FsUtilError: public BaseException
{
};

class PathError: public FsUtilError
{
public:
    PathError(const std::string &path);

    const std::string &getPath() const;

private:
    std::string mPath;
};

class FsFilter
{
public:
    virtual ~FsFilter(){}

    virtual bool isValid(const std::string &str) = 0;
};

class FsUtil
{
public:
    static void list(std::vector<std::string> &names,
            const std::string &path, FsFilter *filter = NULL);

    static void listFiles(std::vector<std::string> &names,
            const std::string &path, FsFilter *filter = NULL);

    static void listDirs(std::vector<std::string> &names,
            const std::string &path, FsFilter *filter = NULL);
};

}

#endif//FS_UTIL_H
