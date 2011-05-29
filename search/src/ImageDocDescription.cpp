#include "ImageDocDescription.h"

namespace search
{
ImageDocDescription::~ImageDocDescription()
{
}

void ImageDocDescription::addObject(const DescriptionObject &object)
{
    DocDescription::addObject(object);
}

void ImageDocDescription::addRelation(const DescriptionObject &firstObject,
        const DescriptionObject &secondObject,
        const DescriptionRelation &relation)
{
    DocDescription::addRelation(firstObject, secondObject, relation);

    if(relation == RELATION_LEFT)
    {
        DocDescription::addRelation(secondObject, firstObject, RELATION_RIGHT);
    }
    else if(relation == RELATION_RIGHT)
    {
        DocDescription::addRelation(secondObject, firstObject, RELATION_LEFT);
    }
    else if(relation == RELATION_TOP)
    {
        DocDescription::addRelation(secondObject, firstObject, RELATION_DOWN);
    }
    else if(relation == RELATION_DOWN)
    {
        DocDescription::addRelation(secondObject, firstObject, RELATION_TOP);
    }
}

const DescriptionRelation ImageDocDescription::RELATION_LEFT = "left";
const DescriptionRelation ImageDocDescription::RELATION_RIGHT = "right";
const DescriptionRelation ImageDocDescription::RELATION_TOP = "top";
const DescriptionRelation ImageDocDescription::RELATION_DOWN = "down";
const DescriptionRelation ImageDocDescription::RELATION_IN = "in";

}
