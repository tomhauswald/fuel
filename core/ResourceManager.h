/*****************************************************************
 * ResourceManager.h
 *****************************************************************
 * Created on: 23.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef CORE_RESOURCEMANAGER_H_
#define CORE_RESOURCEMANAGER_H_

#include "Util.h"
#include <map>

namespace fuel
{
	template<typename KEY, typename RESOURCE>
	class ResourceManager
	{
	protected:
		// Loaded resources
		std::map<KEY, std::shared_ptr<RESOURCE>> m_resources;

	public:
		/**
		 * Instantiates a new resource manager.
		 */
		ResourceManager(void) = default;

		/**
		 * Returns the requested resource.
		 *
		 * @param key
		 * 		Resource key.
		 *
		 * @return
		 * 		The resource.
		 */
		inline RESOURCE &get(const KEY &key){ return *m_resources[key]; }

		/**
		 * Adds a new resource.
		 */
		template<typename... ARGS>
		void add(const KEY &key, ...);

		/**
		 * Removes the specified resource.
		 *
		 * @param key
		 * 		Resource key.
		 */
		void remove(const KEY &key)
		{
			m_resources.erase(key);
		}
	};
}


#endif // CORE_RESOURCEMANAGER_H_
