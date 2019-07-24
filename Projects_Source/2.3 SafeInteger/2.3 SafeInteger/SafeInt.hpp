#pragma once
#include <exception>
#include <limits>
#include <ostream>

template<typename T> class SafeInt;
template<typename T> SafeInt<T> operator+(SafeInt<T> l, SafeInt<T> r);
template<typename T> SafeInt<T> operator-(SafeInt<T> l, SafeInt<T> r);
template<typename T> SafeInt<T> operator*(SafeInt<T> l, SafeInt<T> r);
template<typename T> SafeInt<T> operator/(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator==(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator!=(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator>(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator<(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator<=(SafeInt<T> l, SafeInt<T> r);
template<typename T> bool operator>=(SafeInt<T> l, SafeInt<T> r);
template<typename T> std::ostream& operator<<(std::ostream& stream, const SafeInt<T>& safeInt);

template<typename T>
class SafeInt {
	T value;

	friend SafeInt<T> operator+ <T>(SafeInt<T> l, SafeInt<T> r);
	friend SafeInt<T> operator- <T>(SafeInt<T> l, SafeInt<T> r);
	friend SafeInt<T> operator* <T>(SafeInt<T> l, SafeInt<T> r);
	friend SafeInt<T> operator/ <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator== <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator!= <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator> <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator< <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator<= <T>(SafeInt<T> l, SafeInt<T> r);
	friend bool operator>= <T>(SafeInt<T> l, SafeInt<T> r);
	friend std::ostream& operator<< <T>(std::ostream& stream, const SafeInt<T>&);

public:
	template<typename srcT>
	SafeInt(srcT _value) :value(_value) {
		if(_value < static_cast<srcT>(std::numeric_limits<T>::min()) || _value > static_cast<srcT>(std::numeric_limits<T>::max()))
			throw std::exception();
	}

	SafeInt(const SafeInt<T>& other) :value(other.value) {}

	SafeInt<T>& operator++() {
		*this = *this + SafeInt<T>(1);
		return *this;
	}

	SafeInt<T>& operator--() {
		*this = *this - SafeInt<T>(1);
		return *this;
	}

	T operator()() {
		return value;
	}
};

template<typename T> SafeInt<T> operator+(SafeInt<T> l, SafeInt<T> r) {
	/* Not available in MSVC++
	T result;
	if(__builtin_add_overflow(l.value, r.value, &result))
		throw std::exception();
	return result;*/
	/* Undefined behavior in C
	T result = l.value + r.value;
	if((r.value < 0) != (result < l.value))
		throw std::exception();
	return result;*/
	if(l.value > 0 && r.value > 0) {
		if(r.value > std::numeric_limits<T>::max() - l.value)
			throw std::exception();
	} else if(l.value < 0 && r.value < 0) {
		if (l.value < std::numeric_limits<T>::min() - r.value)
			throw std::exception();
	}
	return l.value + r.value;
}

template<typename T> SafeInt<T> operator-(SafeInt<T> l, SafeInt<T> r) {
	/* Not available in MSVC++
	T result;
	if(__builtin_sub_overflow(l.value, r.value, &result))
		throw std::exception();
	return result;*/
	/* Undefined behavior in C
	T result = l.value - r.value;
	if((r.value > 0) != (result < l.value))
		throw std::exception();
	return result;*/
	if(r.value < 0) {
		if(l.value > r.value + std::numeric_limits<T>::max())
			throw std::exception();
	} else {
		if(l.value <= r.value + std::numeric_limits<T>::min())
			throw std::exception();
	}
	return l.value - r.value;
}

#define lowerHalf(x) ((x) & halfMask)
#define upperHalf(x) (((x) >> halfBits) & halfMask)

template<typename T> SafeInt<T> operator*(SafeInt<T> l, SafeInt<T> r) {
	/* Not available in MSVC++
	T result;
	if (__builtin_mul_overflow(l.value, r.value, &result))
		throw std::exception();
	return result;*/
	/* Undefined behavior in C */
	T result = l.value * r.value;
	if(l.value != 0 && result / l.value != r.value)
		throw std::exception();
	return result;
	/* Long multiplication by splitting in half
	// TODO: Exception Only works for unsigned
	unsigned int halfBits = sizeof(T) * 4;
	const T halfMask = (static_cast<T>(1) << halfBits) - static_cast<T>(1);
	T aux, result[4],
	  lHalf[] = { lowerHalf(l.value), upperHalf(l.value) },
	  rHalf[] = { lowerHalf(r.value), upperHalf(r.value) };
	aux = lHalf[0] * rHalf[0];
	result[0] = lowerHalf(aux);
	aux = lHalf[1] * rHalf[0] + upperHalf(aux);
	result[1] = lowerHalf(aux);
	result[2] = upperHalf(aux);
	aux = lHalf[0] * rHalf[1] + result[1];
	result[1] = lowerHalf(aux);
	aux = lHalf[1] * rHalf[1] + upperHalf(aux) + result[2];
	result[2] = lowerHalf(aux);
	result[3] = upperHalf(aux);
	T carry = (result[3] << halfBits) | result[2];
	if(carry)
		throw std::exception();
	return (result[1] << halfBits) | result[0]; */
	// return l.value * r.value;
}

#undef lowerHalf
#undef upperHalf

template<typename T> SafeInt<T> operator/(SafeInt<T> l, SafeInt<T> r) {
	if(r.value == 0 || (l.value == std::numeric_limits<T>::min() && r.value == -1))
		throw std::exception();
	return l.value / r.value;
}

template<typename T> bool operator==(SafeInt<T> l, SafeInt<T> r) {
	return l.value == r.value;
}

template<typename T> bool operator!=(SafeInt<T> l, SafeInt<T> r) {
	return l.value != r.value;
}

template<typename T> bool operator>(SafeInt<T> l, SafeInt<T> r) {
	return l.value > r.value;
}

template<typename T> bool operator<(SafeInt<T> l, SafeInt<T> r) {
	return l.value < r.value;
}

template<typename T> bool operator<=(SafeInt<T> l, SafeInt<T> r) {
	return l.value <= r.value;
}

template<typename T> bool operator>=(SafeInt<T> l, SafeInt<T> r) {
	return l.value >= r.value;
}

template<typename T> std::ostream& operator<<(std::ostream & stream, const SafeInt<T> & safeInt) {
	stream << static_cast<long long>(safeInt.value);
	return stream;
}
