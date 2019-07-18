#pragma once

//Library includes:
#include <string>
#include <map>
#include <vector>

class IniParser
{
	//Member methods:
public:
	static IniParser& GetInstance();
	static void DestroyInstance();
	~IniParser();

	bool LoadIniFile(const std::string& filename);
	bool DoesSectionExist(const std::string iniSection);
	bool DoesKeyExist(const std::string& iniSection, const std::string& key);

	std::string GetValueAsString(const std::string& iniSection, const std::string& key);
	int GetValueAsInt(const std::string& iniSection, const std::string& key);
	float GetValueAsFloat(const std::string& iniSection, const std::string& key);
	bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);
protected:

private:
	IniParser();
	IniParser(const IniParser& logManager);
	IniParser& operator=(const IniParser& logManager);

	//Member data:
public:

protected:
	static IniParser* sm_pInstance;
	std::map<std::string, std::string>* m_pContent;
	std::vector<std::string>* m_pSectionList;

private:

};