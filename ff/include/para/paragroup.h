#ifndef FF_PARA_PARA_GROUND_H_
#define FF_PARA_PARA_GROUND_H_
#include "common/common.h"
#include "para/para.h"
#include "para/para_helper.h"

namespace ff {

enum group_optimizer
{
  auto_partition,
  max_partition, 
  //other may be here
};
  
template<class RT>
class paragroup {
public:
  typedef RT ret_type;
public:
    void		push(const para<RT> & p) {}
    
    template <class WT>
    internal::para_accepted_wait<paragroup<RT>,WT> operator[](const WT & cond)
    {
        return internal::para_accepted_wait<paragroup<RT>,WT>(*this, cond);
    }
    
    
    template<class Iterator_t, class Functor_t>
    auto for_each(Iterator_t begin, Iterator_t end, Functor_t f) 
    -> internal::para_accepted_call<paragroup<RT>, RT>
    {
        Iterator_t t = begin;
        while(t!= end)
        {
            f(*t);
	    t++;
        }
        return internal::para_accepted_call<paragroup<RT>, RT>(*this);
    }
};//end class paragroup
}//end namespace ff

#endif
