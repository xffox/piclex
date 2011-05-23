#ifndef DOC_DESCRIPTION_H
#define DOC_DESCRIPTION_H

#include <vector>
#include <string>

#include "Matrix3d.h"
#include "BaseExceptions.h"

namespace search
{
typedef std::string DescriptionObject;
typedef std::string DescriptionRelation;

class DocDescriptionInternalError: public base::InternalError
{
};

//! Describe a document by objects and their relations
class DocDescription
{
    typedef std::vector<DescriptionObject> Objects;
    typedef std::vector<DescriptionRelation> Relations;

public:
    virtual ~DocDescription();

    void addObject(const DescriptionObject &object);
    void addRelation(const DescriptionObject &firstObject,
            const DescriptionObject &secondObject,
            const DescriptionRelation &relation);

    bool operator==(const DocDescription &that) const;
    bool isSubsetEq(const DocDescription &that) const;

    bool isObject(const DescriptionObject &object) const;
    bool isObjectsRelation(const DescriptionObject &firstObject,
            const DescriptionObject &secondObject,
            const DescriptionRelation &relation) const;

private:
    virtual void processAddObject(const DescriptionObject &object) const;
    virtual void processAddRelation(const DescriptionObject &firstObject,
            const DescriptionObject &secondObject,
            const DescriptionRelation &relation) const;

private:
    size_t getObjectIndex(const DescriptionObject &object) const;
    size_t getRelationIndex(const DescriptionRelation &relation) const;

    size_t getNewObjectIndex(const DescriptionObject &object);
    size_t getNewRelationIndex(const DescriptionRelation &relation);

private:
    Matrix3d<bool> mObjectsRelations;

    Objects mObjects;
    Relations mRelations;
};

}

#endif//DOC_DESCRIPTION_H
