#ifndef SQUIRRELENV_H
#define SQUIRRELENV_H

#include <squirrel.h>
#include <squirrel/sqvm.h>

template <typename T>
class Singleton {
public:
	static T& get() {
		static T instance{};
		return instance;
	}

protected:
	Singleton() = default;
	~Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

class SquirrelEnv : public Singleton<SquirrelEnv> {
public:
	SquirrelEnv();

private:
	SQVM m_vm;
};

#endif // SQUIRRELENV_H
