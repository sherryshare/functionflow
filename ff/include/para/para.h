#ifndef FF_PARA_PAEA_H_
#define FF_PARA_PAEA_H_
#include "common/common.h"
#include "common/function_traits.h"
#include "para/para_helper.h"
#include "para/exception.h"
#include "para/para_impl.h"
#include "runtime/rtcmn.h"

namespace ff {
using namespace ff::utils;
template<typename RT = void>
class para {
public:
    typedef RT  ret_type;
public:
    
    para()
     : m_pImpl(nullptr){};
    template<class WT>
    internal::para_accepted_wait<para<RT>, WT> operator[](const WT & cond)
    {
        return internal::para_accepted_wait<para<RT>, WT>(*this,cond);
    }
    template<class F>
    auto		exe(const F & f) -> internal::para_accepted_call<para<RT>, RT>
    {
        if(m_pImpl)
            throw used_para_exception();
		m_pImpl = std::make_shared<internal::para_impl<RT>>([f](){return f();});
		internal::schedule(m_pImpl);
        return internal::para_accepted_call<para<RT>, RT>(*this);
    }
    template<class F>
    auto		operator ()(const F & f) -> internal::para_accepted_call<para<RT>, RT>
    {
        return exe(f);
    }

    RT & get() {
        return m_pImpl->get();
    }
    
    exe_state	get_state()
	{
		if(m_pImpl)
			return m_pImpl->get_state();
		return exe_state::exe_unknown;
	}
	bool	check_if_over()
	{
		if(m_pImpl)
			return m_pImpl->check_if_over();
		return false;
	}

	internal::para_impl_ptr<RT> get_internal_impl(){return m_pImpl;}
	
protected:
    internal::para_impl_ptr<RT> m_pImpl; 
};//end class para;


template<>
class para<void> {
public:
    typedef void ret_type;
public:
    para()
        : m_pImpl() {};

    template <class WT>
    internal::para_accepted_wait<para<void>, WT> operator[](const WT & cond)
    {
        return internal::para_accepted_wait<para<void>, WT>(*this, cond);
    }
    template<class F>
    auto		exe(F && f) -> internal::para_accepted_call<para<void>, void>
    {
		if(m_pImpl)
            throw used_para_exception();
		m_pImpl = std::make_shared<internal::para_impl<void> >([&f](){f();});
		internal::schedule(m_pImpl);
        return internal::para_accepted_call<para<void>, void>(*this);
    }
    template<class F>
    auto		operator ()(F && f) -> internal::para_accepted_call<para<void>, void>
    {
        return exe(f);
    }
    
    exe_state	get_state()
	{
		if(m_pImpl)
			return m_pImpl->get_state();
		return exe_state::exe_unknown;
	}
	bool	check_if_over()
	{
		if(m_pImpl)
			return m_pImpl->check_if_over();
		return false;
	}

	internal::para_impl_ptr<void> get_internal_impl(){return m_pImpl;}
	
protected:
    internal::para_impl_ptr<void> m_pImpl; 
};//end class para<void>

}//end namespace ff
#endif
