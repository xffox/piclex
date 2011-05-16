#ifndef INDEX_MAKER_FACTORY_H
#define INDEX_MAKER_FACTORY_H

namespace search
{
class IndexMaker;
class DocIdReader;
class DocProcessor;

IndexMaker *createIndexMaker(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor);
}

#endif//INDEX_MAKER_FACTORY_H
