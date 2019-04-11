//Implementation of the symbol table class.
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );
		a_symbol -> symbol
		a_loc -> corresponding location of the symbol 

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.

RETURNS
	The function will not return any value

*/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    
	if( st != m_symbolTable.end() ) 
	{
        st->second = multiplyDefinedSymbol;
        return;
    }

	// Record the location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}



 
 /*
 void SymbolTable::DisplaySymbolTable()

 NAME
	void SymbolTable::DisplaySymbolTable() -> display symbol table

 SYNOPSIS
	 void SymbolTable::DisplaySymbolTable()
		-> The function does not accept any parameters

 DESCRIPTION
	 The function will display the symbol table by reading off from our map
	 data type. It uses a map iterator to loop through the contents of the map.

 RETURNS
	 The function will not return anything

 */
void SymbolTable::DisplaySymbolTable()
{
	int count = 0;
	map<string, int>::iterator it;

	// Output Formatting
	cout << "Symbol Table:" << endl;
	cout << "\nSymbol#\tSymbol\tLocation" << endl;

	for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++)
	{
		cout << count << "\t" << it->first << "\t" << it->second << endl;
		count++;
	}
}



 /*
 bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)

 NAME
	 bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
		-> Look up symbols

 SYNOPSIS
	 bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
		a_symbol -> get the name of the symbol 
		a_loc -> the location of the symbol if it exists in our symbol table

 DESCRIPTION
	 The function will look up symbols in the symbol table to check if that symbol exists.
	 We can then determine if that symbol already exists and then use another function to 
	 report that it was multiply defined. If the symbol existed, then we pass by reference 
	 the corresponding location of the symbol

 RETURNS
	 The function will return false if the symbol did not exist in the symbol table. Else, if 
	 the symbol exists, then it will return its location as pass by reference and the function 
	 will return true.

 */

bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
{
	//check if the symbol exists in the symbol table
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end())
	{
		return false;
	}

	//get the location and status of the symbol
	a_loc = m_symbolTable[a_symbol];
	return true;
}