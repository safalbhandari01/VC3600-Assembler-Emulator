//		Implementation of Errors class

#include "stdafx.h"
#include "Errors.h"

//included to disable link_external error
vector<string> Errors::m_ErrorMsgs;


/*
void Errors::InitErrorReporting()

NAME
	void Errors::InitErrorReporting() - initialize error reporting

SYNOPSIS
	void Errors::InitErrorReporting()
		-> Does not accept any parameters

DESCRIPTION
	The function will start error messaging procedure by emptying out 
	all the elements in the m_ErrorMsgs vector.

RETURNS
	The function will not return anything

*/
void Errors::InitErrorReporting()
{
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}



 /*
 void Errors::RecordError()

 NAME
 void Errors::RecordError(string a_emsg) - record errors from the source file

 SYNOPSIS
	void Errors::RecordError(string a_emsg)
		a_emsg -> error messages passed in as a string

 DESCRIPTION
	The function will record errors that were discovered while we performed PassII.
	The errors are appended to our error recording string vector.

 RETURNS
	 The function will not return anything

 */
void Errors::RecordError(string a_emsg)
{
	m_ErrorMsgs.push_back(a_emsg);
}




 /*
 void Errors::DisplayErrors()

 NAME
	 void Errors::DisplayErrors() - display errors

 SYNOPSIS
	 void Errors::DisplayErrors()
		-> The function does not receive any parameters

 DESCRIPTION
	The function will display errors that were recorded to the console.
	The errors are read from our error recording string vector.

 RETURNS
	 The function will not return anything

 */
void Errors::DisplayErrors()
{
	for (vector<string>::const_iterator i = m_ErrorMsgs.begin(); i != m_ErrorMsgs.end(); ++i)
	{
		cout << *i << endl;
	}
}



 
 /*
 void Errors::CheckErrorMsgs()

 NAME
	 void Errors::CheckErrorMsgs() - check if there were any errors reported

 SYNOPSIS
	 void Errors::CheckErrorMsgs()
		-> The function checks if there were any error messages reported by Pass II

 DESCRIPTION
	 The function will check if the m_ErrorMsgs vector has any elements or not.
	 If it does, then there are error messages in the program. Else, there are no error messages.

 RETURNS
	 The function will return true if m_ErrorMsgs vector is empty. It will return false if there
	 are elements in the vector. 

 */
bool Errors::CheckErrorMsgs()
{
	return m_ErrorMsgs.empty();
}