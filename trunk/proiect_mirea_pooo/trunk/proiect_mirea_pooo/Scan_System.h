
#pragma once 
#include<iostream>




class system
{
public:
	//Scan system

	virtual void scan( char* file1, char* file2)=0;// default valoarea e 40%>= 

	virtual void scan(char* file1, char* file2, float value)=0;


};




class subsystem_NS:public system
{


public:
	//Scan system

	virtual void scan( char* file1, char* file2);// default valoarea e 40%>= 

	virtual void scan(char* file1, char* file2, float value);

};


class subsystem_AS: public system
{

public:
	//Scan system

	virtual void scan( char* file1, char* file2);// default valoarea e 40%>= 

	virtual void scan(char* file1, char* file2, float value);
};