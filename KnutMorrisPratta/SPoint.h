#pragma once

template<typename T>
struct SRange
{
	SRange();
	SRange(T start, T end);
	T start;
	T end;
};

template<typename T>
bool const operator ==(SRange<T> const& first, SRange<T> const& second);

template<typename T>
bool const operator !=(SRange<T> const& first, SRange<T> const& second);
