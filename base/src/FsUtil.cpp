#include "FsUtil.h"

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <fstream>

namespace
{
int isType(const std::string &path, mode_t typeMask)
{
    if(path.size() == 0)
        return 0;

    struct stat inf;
    if(lstat(path.c_str(), &inf) != 0)
        return 0;

    return (inf.st_mode & S_IFMT & typeMask) != 0;
}

void listType(std::vector<std::string> &names,
        const std::string &path, mode_t typeMask,
        base::FsFilter *filter = NULL)
{
    names.clear();

    DIR *dir = opendir(path.c_str());
    if(!dir)
    {
        if(errno == EACCES || errno == ENOENT || errno == ENOTDIR)
            throw base::PathError(path);
        throw base::FsUtilError();
    }

    size_t len = offsetof(struct dirent, d_name) +
        pathconf(path.c_str(), _PC_NAME_MAX) + 1;
    char *buf = NULL;
    try
    {
        buf = new char[len];
    }
    catch(std::bad_alloc &exc)
    {
        closedir(dir);

        throw base::FsUtilError();
    }
    struct dirent *entry = reinterpret_cast<struct dirent*>(buf);

    struct dirent *result = NULL;
    std::string filePath;
    while(true)
    {
        if(readdir_r(dir, entry, &result))
        {
            delete[] buf;
            closedir(dir);

            throw base::FsUtilError();
        }
        if(!result)
            break;

        filePath = path;
        filePath += '/';
        filePath += result->d_name;
        if( isType(filePath, typeMask) &&
                (!filter || filter->isValid(result->d_name)) )
            names.push_back(result->d_name);
    }

    delete[] buf;
    closedir(dir);
}

}

namespace base
{
void FsUtil::list(std::vector<std::string> &names,
        const std::string &path, FsFilter *filter)
{
    listType(names, path, S_IFMT, filter);
}

void FsUtil::listFiles(std::vector<std::string> &names,
            const std::string &path, FsFilter *filter)
{
    listType(names, path, S_IFREG, filter);
}

void FsUtil::listDirs(std::vector<std::string> &names,
        const std::string &path, FsFilter *filter)
{
    listType(names, path, S_IFDIR, filter);
}

void FsUtil::read(std::string &data, const std::string &name)
{
    std::ifstream infile(name.c_str());
    if(!infile.is_open())
        throw base::FsUtilError();

    const size_t bufSize = 4096;
    char buf[bufSize];

    do
    {
        infile.read(buf, bufSize);
        if(infile.bad())
            throw base::FsUtilError();
        data.append(buf, infile.gcount());
    }while(!infile.eof());
}

PathError::PathError(const std::string &path)
    :mPath(path)
{
}

const std::string &PathError::getPath() const
{
    return mPath;
}
}
