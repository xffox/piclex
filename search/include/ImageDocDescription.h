#ifndef IMAGE_DOC_DESCRIPTION_H
#define IMAGE_DOC_DESCRIPTION_H

#include "DocDescription.h"

namespace search
{
class ImageDocDescription: public DocDescription
{
public:
    virtual ~ImageDocDescription();

    virtual void addObject(const DescriptionObject &object);
    virtual void addRelation(const DescriptionObject &firstObject,
            const DescriptionObject &secondObject,
            const DescriptionRelation &relation);

private:
    static const DescriptionRelation RELATION_LEFT;
    static const DescriptionRelation RELATION_RIGHT;
    static const DescriptionRelation RELATION_TOP;
    static const DescriptionRelation RELATION_DOWN;
    static const DescriptionRelation RELATION_IN;
};

}

#endif//IMAGE_DOC_DESCRIPTION_H
