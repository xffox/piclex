#ifndef SEARCH_DEFINES_H
#define SEARCH_DEFINES_H

#include <cstddef>
#include <string>

#include "IdStorage.h"

namespace search
{
typedef StorageId DocId;
typedef IdStorage<std::string> DocIdStorage;
typedef std::string Term;
typedef std::string Document;
}

#endif//SEARCH_DEFINES_H
