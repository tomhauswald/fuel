/*****************************************************************
 **' Util.h
 *****************************************************************
 **' Created on: 12.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef CORE_UTIL_H_
#define CORE_UTIL_H_

#include <memory>
#include <type_traits>
#include <utility>
#include <cstdio>

namespace fuel
{
	/**
	 * Make unique helper. (array type version)
	 */
	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args)
	{
	  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	/**
	 * Make unique helper. (non-array type version)
	 */
	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args)
	{
	   static_assert(std::extent<T>::value == 0,
		   "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

	   typedef typename std::remove_extent<T>::type U;
	   return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
	}

	/**
	 * Make unique implementation.
	 */
	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args)
	{
	   return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
	}

	/**
	 * Returns whether the given file exists.
	 *
	 * @param filename
	 * 		Name of the file.
	 *
	 * @return Whether the file exists.
	 */
	inline bool fileExists (const std::string &filename)
	{
		if(FILE *file = fopen(filename.c_str(), "r")) { fclose(file); return true; }
		return false;
	}
}


#endif // CORE_UTIL_H_
