
#pragma once
#include<iostream>


class APP_Str//aplication string
{
	char* data;




public:
	APP_Str()
	{ data = NULL; }
	APP_Str(char* str)
	{ data = strdup(str); }
	~APP_Str()
	{
		delete data;
	}

	int operator==(char*str)
	{ 
		if (strcmp(this->data, str) == 0)
			return NULL;
		else 
			return 1;

	}
	void operator=(APP_Str&str)
	{
		this->data = strdup(str.get_Data());
	
	}
	void operator=(char* str)
	{
		this->data = strdup(str);
	
	}
	char* get_Data()
	{
		return this->data;
	}

	
};