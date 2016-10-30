#ifndef _object_h_
#define _object_h_

namespace sirius{
class Object{

};
class NonCopyableObject:Object{
private:
    void operator=(Object){};
};
}

#endif //_object_h_