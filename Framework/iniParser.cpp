//Local includes
#include "IniParser.h"

//Library includes
#include <string>
#include <fstream>
#include <sstream>
#include <map>

//Static instances:
IniParser* IniParser::sm_pInstance = 0;
std::map<std::string, std::string>* m_pContent = 0;

IniParser&
IniParser::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new IniParser();
	}

	return (*sm_pInstance);
}

void
IniParser::DestroyInstance()
{
	if(sm_pInstance != 0) 
		delete sm_pInstance;
}

IniParser::IniParser()
	: m_pContent(0)
	, m_fileLastLoaded("")
{
	
}

IniParser::~IniParser()
{
	if (sm_pInstance->m_pContent != 0)
	{
		sm_pInstance->m_pContent->clear();
		delete m_pContent;
	}

	if (sm_pInstance->m_pSectionList != 0)
	{
		sm_pInstance->m_pSectionList->clear();
		delete m_pSectionList;
	}
}

bool 
IniParser::LoadIniFile(const std::string& filename)
{
	std::ifstream file; //File
	std::string line; //Line to be cut
	std::string section; //Section
	std::string key; //Key
	std::string value;

	if (m_fileLastLoaded == filename)
	{
		return true; //File alreadly loaded.
	}

	//Check if the parser has been loaded before.
	if (m_pContent == 0) 
	{
		m_pContent = new std::map<std::string, std::string>();
		m_pSectionList = new std::vector<std::string>();
	}
	else //clear old data.
	{
		m_pContent->clear();
		m_pSectionList->clear();
	}

	file.open(filename); //Open the file

	//Check if the file exists
	if (file.is_open()) 
	{
		while (std::getline(file, line))
		{
			if (line.empty()) //Ignore because it is empty.
			{
				
			}
			else if (line.at(0) == '[') //Start of a section identifier
			{
				section = line.substr(1, line.size() - 2);
				std::vector<std::string>::iterator iter = m_pSectionList->end();
				m_pSectionList->insert(iter, section);
			}
			else if (line.at(0) == ';') //Ignore because it is a comment.
			{
				
			}
			else //it is relevant informaton
			{
				int temp = line.find(" ");
				key = line.substr(0, temp);
				value = line.substr(temp + 3, line.size() - 1);
				m_pContent->insert(std::pair<std::string, std::string>(section + " | " + key, value));
			}
		}
		file.close(); //Close the file
		m_fileLastLoaded = filename;
		return true; //Successflly loaded
	}
	else //failed to open the file
	{
		return false; //Failed to load
	}
}

bool 
IniParser::DoesSectionExist(const std::string iniSection)
{
	std::vector<std::string>::iterator iter = std::find(m_pSectionList->begin(), m_pSectionList->end(), iniSection);
	
	return (iter != m_pSectionList->end());
}

bool 
IniParser::DoesKeyExist(const std::string& iniSection, const std::string& key)
{
	std::map<std::string, std::string>::iterator iter = m_pContent->find(iniSection + " | " + key);
	return (iter != m_pContent->end());
}

std::string
IniParser::GetValueAsString(const std::string& iniSection, const std::string& key)
{
	return m_pContent->at(iniSection + " | " + key);
}

int
IniParser::GetValueAsInt(const std::string& iniSection, const std::string& key)
{
	std::string temp = m_pContent->at(iniSection + " | " + key);
	std::stringstream geek(temp);
	int val = 0;
	geek >> val;
	return val;
}

float
IniParser::GetValueAsFloat(const std::string& iniSection, const std::string& key)
{
	std::string temp = m_pContent->at(iniSection + " | " + key);
	return strtof(temp.data(), NULL);
}

bool
IniParser::GetValueAsBoolean(const std::string& iniSection, const std::string& key)
{
	std::string temp = m_pContent->at(iniSection + " | " + key);
	if (temp == "true") 
	{
		return true;
	}
	else if(temp == "false")
	{
		return false;
	}
}
