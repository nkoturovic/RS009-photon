#include <iostream>
#include "transform_manager.hpp"


template <typename Rsrc>
class Transform {
public:

    friend Rsrc& operator<<=(Rsrc &resource, const Transform& tr) { 
        return tr.apply(resource); 
    }

    friend Rsrc operator<<(const Rsrc &resource, const Transform& tr) { 
        Rsrc copy(resource);
        return copy <<= tr;
    }

    Rsrc& operator()(Rsrc &resource) {
        this->apply(resource);
    }

private:
    virtual Rsrc& apply(Rsrc &) const = 0;
};

int main()
{

    TransformManager<int, Transform<int>> tformManager(1);
    tformManager.transform(

    return 0;
}
