#ifndef CALLBACK_EQUALS_HPP
#define	CALLBACK_EQUALS_HPP

namespace event
{
	
	/**
	 * Compares the callback (attribute) against given callbacks.
	 */
	template<class C>
	class callback_equals
	{
	private:
		/**
		 * The callback to compare to.
		 */
		const C * const callback;
		
	public:
		callback_equals(const C * const cb);
		
		bool operator()(const C * const rhs) const;
	};
	
	
	template<class C>
	callback_equals<C>::callback_equals(const C* const cb)
		: callback(cb)
	{
		
	}
		
	/**
	 * Compares the callback with the given callback.
	 * 
         * @param rhs Callback to compare to.
         * @return When they are equal true, otherwise false.
         */
	template<class C>
	bool callback_equals<C>::operator()(const C* const rhs) const
	{
		return *(this->callback) == *rhs;
	}
}

#endif	/* CALLBACK_EQUALS_HPP */

