#include "stdafx.h"
#include "SPoint.h"

template<typename T>
SRange<T>::SRange()
	: start(T())
	, end(T())
{
}

template<>
SRange<size_t>::SRange<size_t>()
	: start(0)
	, end(0)
{
}


template<typename T>
SRange<T>::SRange(T start, T end)
	: start(start)
	, end(end)
{
}

template<typename T>
bool const operator ==(SRange<T> const & first, SRange<T> const & second)
{
	return ((first.start == second.start) && (first.end == second.end));
}

template<typename T>
bool const operator!=(SRange<T> const & first, SRange<T> const & second)
{
	return !(first == second);
}