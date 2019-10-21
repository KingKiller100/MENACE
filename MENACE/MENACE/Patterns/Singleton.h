#pragma once

#include <memory>

namespace Pattern
{
	template<typename T>
	class Singleton
	{
	public:
		virtual ~Singleton( void ) {}
		
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton) = delete;
		
		static T& Reference()
		{
			return *instance;
		}
				
	protected:
		Singleton()
		{
			instance = std::make_unique<T>(Token());
		}

		static std::unique_ptr<T>& Pointer()
		{
			return instance;
		}

	protected:
		struct Token {};

	private:
		static std::unique_ptr<T> instance;
	};
}

template<typename T>
std::unique_ptr<T> Pattern::Singleton<T>::instance;