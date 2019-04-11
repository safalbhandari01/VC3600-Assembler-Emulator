//		Assembler class.  This is a container for all the components
//		that make up the assembler.
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler
{

public:
	//	Constructor for the Assembler class
	Assembler(int argc, char *argv[]);

	// Pass I - establish the locations of the symbols
	void PassI();

	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

	// Run emulator on the translation.
	void RunEmulator();

private:

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab;	// Symbol table object
	Instruction m_inst;	    // Instruction object
	Emulator m_emul;        // Emulator object
};

