#ifndef MAPPER_CALLBACK_H
#define MAPPER_CALLBACK_H

namespace gui
{
template<class In, class Out>
class MapperCallback
{
public:
    virtual ~MapperCallback(){};

    virtual void call(const In &in, const Out &out) = 0;

private:
};

}

#endif//MAPPER_CALLBACK_H
