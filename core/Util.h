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
#include <vector>
#include <cmath>

// Macro shortcut to create a const-qualified by-const-reference getter.
#define CONSTREF_GETTER(TYPE, FIELD, NAME) inline const TYPE &NAME(void) const{ return FIELD; }

// Macro shortcut to create a by-reference getter.
#define REF_GETTER(TYPE, FIELD, NAME) inline TYPE &NAME(void) { return FIELD; }

// Macro shortcut to create a const-qualified by-value getter.
#define VALUE_GETTER(TYPE, FIELD, NAME) inline TYPE NAME(void) const { return FIELD; }

// Macro shortcut to create a by-const-reference setter.
#define SETTER(TYPE, FIELD, ARG, NAME) inline void NAME(const TYPE &ARG){ FIELD = ARG; }

// Print message to std::cout and append endl
#define COUTLN(STRING) std::cout << STRING << std::endl

// Print message to std::cerr and append endl
#define CERRLM(STRING) std::cerr << STRING << std::endl

// Clamp a value between minimum and maximum
#define CLAMP(VALUE, MIN, MAX) (std::min(MAX, std::max(MIN, VALUE)))

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

	// Cube vertices
	static const std::vector<float> CUBE_VERTICES =
	{
			// Front face
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,

			// Right face
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,

			// Back face
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,

			// Left face
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			// Top Face
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			// Bottom Face
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f
	};

	// Cube normals
	static const std::vector<float> CUBE_NORMALS =
	{
			// Front face
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			// Right face
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			// Back face
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,

			// Left face
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,

			// Top Face
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,

			// Bottom Face
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
	};

	// Cube texture coordinates
	static const std::vector<float> CUBE_TEXTURE_COORDS =
	{
			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1
	};

	// Cube indices
	static const std::vector<uint16_t> CUBE_INDICES =
	{
			// Front face
			0, 1, 2, 2, 3, 0,

			// Right face
			4, 5, 6, 6, 7, 4,

			// Back face
			8, 9, 10, 10, 11, 8,

			// Left face
			12, 13, 14, 14, 15, 12,

			// Top Face
			16, 17, 18, 18, 19, 16,

			// Bottom Face
			20, 21, 22, 22, 23, 20
	};
}


#endif // CORE_UTIL_H_
