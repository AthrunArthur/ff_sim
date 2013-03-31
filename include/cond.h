#ifndef FF_SIM_COND_H_
#define FF_SIM_COND_H_

#define cfalse false
#define ctrue true;
class cond {
protected:
	bool			bval;
public:
	cond( bool v) :bval(v){};
	cond(): bval(false){};
	
	bool &		val() {return bval;}
};
template<class L, class op, class R>
struct cond_expr_bin{
	cond_expr_bin(L & l, R & r): ML(l), MR(r){}
	
	cond	val(){return op::apply(ML, MR);}
	
protected:
	L & ML;
	R & MR;
};

template<class C, class op>
struct cond_expr_uni{
	cond_expr_uni(C & c): MC(c){}
	
	cond	val(){return op::apply(MC);}
protected:
	C & MC;
};

struct OpAnd{
	template <class L, class R>
	static cond apply(L & l, R & r)
	{
		return cond(l.val() && r.val());
	}
};

struct OpOr{
	template <class L, class R>
	static cond apply(L & l, R & r)
	{
		return cond(l.val() || r.val());
	}
};
struct OpAll{
	template <class C>
	static cond apply(C & c)
	{
		cond t = ctrue;
		for(typename C::iterator it = c.begin(); it != c.end(); it++)
			t = t.val() && (*it).val();
		return t;
	}
};
struct OpAny{
	template <class C>
	static cond apply(C & c)
	{
		cond t = ctrue;
		for(typename C::iterator it = c.begin(); it != c.end(); it++)
			t = t.val() || (*it).val();
		return t;
	}
};
struct OpSingle{
	template <class C>
	static cond apply(C & c)
	{
		return cond(c.val());
	}
};
template<class L, class R>
cond_expr_bin<L, OpAnd, R>		operator&& (L & l, R & r)
{
	return cond_expr_bin<L, OpAnd, R>(l, r);
}
template<class L, class R>
cond_expr_bin<L, OpOr, R>		operator|| (L & l, R & r)
{
	return cond_expr_bin<L, OpOr, R>(l, r);
}
template<class C>
cond_expr_uni<C, OpAny>		any(C & c)
{
	return cond_expr_uni<C, OpAny>(c);
}
template<class C>
cond_expr_uni<C, OpAll>		all(C & c)
{
	return cond_expr_uni<C, OpAll>(c);
}

#endif

