#ifndef FF_PARA_DATA_WRAPPER_H_
#define FF_PARA_DATA_WRAPPER_H_
#include "common/common.h"

namespace ff
{
	template<class T>
	class accumulator{
	public:
		accumulator(const accumulator<T> & ) = delete;
		accumulator<T> & operator = (const accumulator<T> &) = delete;
	public:
		typedef std::function<T (const T&, const T&)> Functor_t;
		template<class FT>
		accumulator(const T & value, const FT& functor)
		: m_oValue(value)
		, Functor(functor){}
		
		template<class FT>
		accumulator(const FT& functor)
		: m_oValue()
		, Functor(functor){}
		
		accumulator<T>& increase(const T & value){
		  m_oValue = Functor(m_oValue, value);
		  return *this;
		}
		
		T & get(){return m_oValue;}
	protected:
		T m_oValue;
		Functor_t	Functor;
	};//end class accumulator
	
	template< class T>
	class single_assign
	{
		single_assign(const single_assign<T> & ) = delete;
		single_assign<T> & operator =(const single_assign<T> &) = delete;
	public:
		single_assign()
		: m_oValue()
		, m_bIsAssigned(false){}
		single_assign(const T & v)
		: m_oValue(v)
		, m_bIsAssigned(true){}
		
		single_assign<T> & operator =(const T & v)
		{
			if(m_bIsAssigned)
				return *this;
			m_bIsAssigned = true;
			m_oValue = v;
			return *this;
		}
		
		T & get() {return m_oValue;}
	protected:
		T m_oValue;
		bool m_bIsAssigned;
	};//end class single_assign
}//end namespace ff;
#endif