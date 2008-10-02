#ifndef __MODEL_H__
#define __MODEL_H__

#include "integer.h"

class SymbolHistoryParameterType
{
public:
	enum {TypeCode = 0x1000};
};

template <typename T> class IModelT
{
public:
	typedef T Value;
	typedef IModelT<Value> IModel;

	virtual void AddRef() = 0;
	virtual void DecRef() = 0;

	virtual u32 GetSpaceSize() = 0;
	virtual u32 GetRangeLow(Value value) = 0;
	virtual u32 GetRangeSize(Value value) = 0;
	virtual Value FindValue(u32 position) = 0;

	virtual int GetParameterCount() const = 0;
	virtual int GetParameterType(int paramIndex) const = 0;
	virtual const char* GetParameterName(int paramIndex) const = 0;
};

template <typename T, typename P> class PrimitiveModelT : public P, public IModelT<T>
{
public:
	typedef T Value;
	typedef P Primitive;

	virtual void AddRef();
	virtual void DecRef();

	virtual u32 GetSpaceSize();
	virtual u32 GetRangeLow(Value value);
	virtual u32 GetRangeSize(Value value);
	virtual Value FindValue(u32 position);

	virtual int GetParameterCount() const;
	virtual int GetParameterType(int paramIndex) const;
	virtual const char* GetParameterName(int paramIndex) const;

private:
	int refCount;
};

template <typename T, typename P> PrimitiveModelT<T, P>::PrimitiveModelT()
: refCount(0)
{
}

template <typename T, typename P> void PrimitiveModelT<T, P>::AddRef()
{
	++this->refCount;
}

template <typename T, typename P> void PrimitiveModelT<T, P>::DecRef()
{
	if (--this->refCount <= 0)
		delete this;
}

template <typename T, typename P> u32 PrimitiveModelT<T, P>::GetSpaceSize()
{
	return static_cast<Primitive*>(this)->GetSpaceSize();
}

template <typename T, typename P> u32 PrimitiveModelT<T, P>::GetRangeLow(Value value)
{
	return static_cast<Primitive*>(this)->GetRangeLow(value);
}

template <typename T, typename P> u32 PrimitiveModelT<T, P>::GetRangeSize(Value value)
{
	return static_cast<Primitive*>(this)->GetRangeSize(value);
}

template <typename T, typename P> PrimitiveModelT<T, P>::Value PrimitiveModelT<T, P>::FindValue(u32 position)
{
	return static_cast<Primitive*>(this)->FindValue(position);
}

template <typename T, typename P> int PrimitiveModelT<T, P>::GetParameterCount() const
{
	return sizeof(Primitive::parameters) / sizeof(Primitive::parameters[0]);
}

template <typename T, typename P> int PrimitiveModelT<T, P>::GetParameterType(int paramIndex) const
{
	return Primitive::parameters[paramIndex].type;
}

template <typename T, typename P> const char* PrimitiveModelT<T, P>::GetParameterName(int paramIndex) const
{
	return Primitive::parameters[paramIndex].name;
}

#endif //__MODEL_H__
