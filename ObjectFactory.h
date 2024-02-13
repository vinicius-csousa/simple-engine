#pragma once

#include <map>
#include <memory>
#include <string>
#include <functional>
#include "GameObject.h"

class ObjectFactory
{
public:
	static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }
	GameObject* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function<GameObject* (Properties* props)> type);

private:
	static ObjectFactory* s_Instance;
	ObjectFactory(){}
	std::map<std::string, std::function<GameObject* (Properties* props)>> m_TypeRegistry;
};

template<class Type>
class Registr {
public:
	Registr(std::string className) {
		ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* { return new Type(props); });
	}
};