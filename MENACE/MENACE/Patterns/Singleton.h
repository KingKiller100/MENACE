#pragma once

namespace Pattern
{
	template<class T>
	class Singleton
	{
	public:
		virtual ~Singleton( void ) {}
		
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton) = delete;

		static T& GetInstance()
		{
			static auto instance_ = std::make_unique<T>(Token());
			return *instance_;
		}

	protected:
		Singleton() {}

	protected:
		struct Token {};
	};
}
