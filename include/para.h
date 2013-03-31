#ifndef FF_SIM_PARA_H_
#define FF_SIM_PARA_H_
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "cond.h"
template<class T>
class defer_value
{
public :
	explicit defer_value(T & t): m_Val(t){};
	
protected:
	T &			m_Val;
};//end class defer_value;
class para
{
public:
	template <class Func_t>
	defer_value<typename Func_t::result_type>		operator ()(Func_t f)
	{
		typename Func_t::result_type t;
		funcWrapper(f, t);
		//do something
		return defer_value<typename Func_t::result_type>(t);
	}
	
	template <class T>
	para &	operator [] (T c)
	{
		cond_expr_uni<T, OpSingle> t(c);
		m_oEvalFunc = boost::bind(&cond_expr_uni<T, OpSingle>::val, &t);
		return *this;
	}
	
	cond			val(){return cond(true);}
protected:
	template <class Func_t>
	static		void funcWrapper(Func_t f, typename Func_t::result_type & t)
	{
		t = f();
	}
protected:
	boost::function<cond () > m_oEvalFunc;
	boost::function<void ( )> m_oFunc;
};
#endif