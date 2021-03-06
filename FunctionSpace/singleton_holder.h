#ifndef ARTPDE_SINGLETONHOLDER_HPP
#define ARTPDE_SINGLETONHOLDER_HPP


namespace art_pde {namespace function_space {

	template<class T>
	class SingletonHolder {
	public:
		static T& instance() {
			static T instance_;
			return instance_;
		}
	private:
		SingletonHolder() {}
		SingletonHolder(const SingletonHolder&) {}
		SingletonHolder& operator=(const SingletonHolder&) {}

	};

}}


# endif