/**
 *  @file
 *  @author     2012-2013 Stefan Radomski (stefan.radomski@cs.tu-darmstadt.de)
 *  @copyright  Simplified BSD
 *
 *  @cond
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the FreeBSD license as published by the FreeBSD
 *  project.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the FreeBSD license along with this
 *  program. If not, see <http://www.opensource.org/licenses/bsd-license>.
 *  @endcond
 */

#ifndef CONVENIENCE_H_LU7GZ6CB
#define CONVENIENCE_H_LU7GZ6CB

#include "uscxml/Common.h"
#include <inttypes.h>
#include <stdlib.h>
#include <boost/detail/endian.hpp>
#include <boost/lexical_cast.hpp>

namespace uscxml {
inline bool isnan(double x);

// see http://stackoverflow.com/questions/228005/alternative-to-itoa-for-converting-integer-to-string-c
template <typename T> std::string toStr(T tmp) {
	std::ostringstream out;
	out.precision(std::numeric_limits<double>::digits10 + 1);
	out << tmp;
	return out.str();
}

template <typename T> T strTo(std::string tmp) {
	T output;
	std::istringstream in(tmp);
	in >> output;
	return output;
}

class USCXML_API NumAttr {
public:
	NumAttr(const std::string& str) {
		size_t valueStart = str.find_first_of("0123456789.");
		if (valueStart != std::string::npos) {
			size_t valueEnd = str.find_last_of("0123456789.");
			if (valueEnd != std::string::npos) {
				value = str.substr(valueStart, (valueEnd - valueStart) + 1);
				size_t unitStart = str.find_first_not_of(" \t", valueEnd + 1);
				if (unitStart != std::string::npos) {
					size_t unitEnd = str.find_last_of(" \t");
					if (unitEnd != std::string::npos && unitEnd > unitStart) {
						unit = str.substr(unitStart, unitEnd - unitStart);
					} else {
						unit = str.substr(unitStart, str.length() - unitStart);
					}
				}
			}
		}
	}

	std::string value;
	std::string unit;
};

bool isNumeric(const char* pszInput, int nNumberBase);
bool isInteger( const char* pszInput, int nNumberBase);
bool iequals(const std::string& a, const std::string& b);
bool equals(const std::string& a, const std::string& b);
bool stringIsTrue(const std::string& value);
bool envVarIsTrue(const char* name);
bool envVarIEquals(const char* name, const char* value);

std::string escape(const std::string& a);
std::string unescape(const std::string& a);

// see http://www.cplusplus.com/forum/general/27544/

// Little-endian operating systems:
//---------------------------------
// Linux on x86, x64, Alpha and Itanium
// Mac OS on x86, x64
// Solaris on x86, x64, PowerPC
// Tru64 on Alpha
// Windows on x86, x64 and Itanium

// Big-endian operating systems:
//------------------------------
// AIX on POWER
// AmigaOS on PowerPC and 680x0
// HP-UX on Itanium and PA-RISC
// Linux on MIPS, SPARC, PA-RISC, POWER, PowerPC, and 680x0
// Mac OS on PowerPC and 680x0
// Solaris on SPARC

/**
Detect endianness, see http://stackoverflow.com/questions/809902/64-bit-ntohl-in-c
union {
    unsigned long long ull;
    char c[8];
} x;
x.ull = 0x0123456789abcdef; // may need special suffix for ULL.
*/

enum endianness {
	little_endian,
	big_endian,
	network_endian = big_endian,

#if defined(BOOST_LITTLE_ENDIAN)
	host_endian = little_endian
#elif defined(BOOST_BIG_ENDIAN)
	host_endian = big_endian
#else
#error "unable to determine system endianness"
#endif
};

namespace detail {

template<typename T, size_t sz>
struct swap_bytes {
	inline T operator()(T val) {
		throw std::out_of_range("data size");
	}
};

template<typename T>
struct swap_bytes<T, 1> {
	inline T operator()(T val) {
		return val;
	}
};

template<typename T>
struct swap_bytes<T, 2> { // for 16 bit
	inline T operator()(T val) {
		return ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));
	}
};

template<typename T>
struct swap_bytes<T, 4> { // for 32 bit
	inline T operator()(T val) {
#if defined(_USE_BUILTIN_BSWAPS) && defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4)
		return __builtin_bswap32(val);
#else
		return ((((val) & 0xff000000) >> 24) |
		        (((val) & 0x00ff0000) >>  8) |
		        (((val) & 0x0000ff00) <<  8) |
		        (((val) & 0x000000ff) << 24));
#endif
	}
};

template<>
struct swap_bytes<float, 4> {
	inline float operator()(float val) {
		uint32_t mem = swap_bytes<uint32_t, sizeof(uint32_t)>()(*(uint32_t*)&val);
		return *(float*)&mem;
	}
};

template<typename T>
struct swap_bytes<T, 8> { // for 64 bit
	inline T operator()(T val) {
#if defined(_USE_BUILTIN_BSWAPS) && defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4)
		return __builtin_bswap64(val);
#else
		return ((((val) & 0xff00000000000000ull) >> 56) |
		        (((val) & 0x00ff000000000000ull) >> 40) |
		        (((val) & 0x0000ff0000000000ull) >> 24) |
		        (((val) & 0x000000ff00000000ull) >> 8 ) |
		        (((val) & 0x00000000ff000000ull) << 8 ) |
		        (((val) & 0x0000000000ff0000ull) << 24) |
		        (((val) & 0x000000000000ff00ull) << 40) |
		        (((val) & 0x00000000000000ffull) << 56));
#endif
	}
};

template<>
struct swap_bytes<double, 8> {
	inline double operator()(double val) {
		uint64_t mem = swap_bytes<uint64_t, sizeof(uint64_t)>()(*(uint64_t*)&val);
		return *(double*)&mem;
	}
};

template<endianness from, endianness to, class T>
struct do_byte_swap {
	inline T operator()(T value) {
		return swap_bytes<T, sizeof(T)>()(value);
	}
};
// specialisations when attempting to swap to the same endianess
template<class T> struct do_byte_swap<little_endian, little_endian, T> {
	inline T operator()(T value) {
		return value;
	}
};
template<class T> struct do_byte_swap<big_endian,    big_endian,    T> {
	inline T operator()(T value) {
		return value;
	}
};

} // namespace detail

template<endianness from, endianness to, class T>
inline T byte_swap(T value) {
	// ensure the data is only 1, 2, 4 or 8 bytes
	BOOST_STATIC_ASSERT(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);
	// ensure we're only swapping arithmetic types
	BOOST_STATIC_ASSERT(boost::is_arithmetic<T>::value);

	return detail::do_byte_swap<from, to, T>()(value);
}


}


#endif /* end of include guard: CONVENIENCE_H_LU7GZ6CB */
