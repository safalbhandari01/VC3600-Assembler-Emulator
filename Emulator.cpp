//      Implementation of the Emulator class.
#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"



/*
Emulator::insertMemory()

NAME
	bool Emulator::insertMemory(int a_location, int a_contents) - get machine level
		language instructions to be inserted into memory

SYNOPSIS
	bool Emulator::insertMemory(int a_location, int a_contents)
		a_location -> get the location of the symbol so that we can translate 
		a_contents -> the contents of our translation

DESCRIPTION
	The function will emulate the machine level instructions passed in from Pass II 
	and then store the contents of the translation corresponding to the location of 
	the value that was passed in.

RETURNS
	The function will return true if it was able to store the contents in the location 
	specified. If the user passed in location that exceeded 10,000 words of memory, then the function will
	return false. 

*/
bool Emulator::insertMemory(int a_location, int a_contents)
{
	// Check if the location exceeds 10,000 words in memory
	// Also, record the error
	if (a_location >= MEMSZ)
	{
		Errors::RecordError("Cannot insert into the emulator as the location has exceeded memory size.");
		return false;
	}

	m_memory[a_location] = a_contents;
	return true;
}


 /*
 Emulator::runProgram()

 NAME
	 bool Emulator::runProgram() -> start emulating VC 3600 decimal computer

 SYNOPSIS
	bool Emulator::runProgram()
		-> Does not receive any parameters

 DESCRIPTION
	The function use the sequence of machine level instructions that were stored in memory 
	by the bool Emulator::insertMemory(int a_location, int a_contents) function. It will 
	execute by looking up commands that were stored in successive memory locations. If there
	are no contents in the memory location, then it will look for the next one. The first two
	digits stored in the location acts as an opcode while the last four digits will be used to 
	identify the address in the VC compiler.After, it uses the opcode value to perform 
	corresponding operation. 

 RETURNS
	 The function will return true if it was able to store the contents in the location
	 specified. If the user passed in location that exceeded 10,000 words of memory, then the function will
	 return false.

 */
bool Emulator::runProgram()
{
	int opCode = 0;
	int input = 0;
	int address = 0;

	for(int loc = 0; loc < MEMSZ; ++loc)
	{
		//emulate only if memory has contents
		if (m_memory[loc] != 0)
		{
			//get the first two digits for opcode
			opCode = m_memory[loc] / 10000;
			//get the last four digits for address
			address = m_memory[loc] % 10000;

			switch (opCode)
			{
			// ACC <-- content(ACC) + c(ADDR)
			case 1:
				m_accumulator += m_memory[address];
				break;
			
			// ACC <-- content(ACC) - c(ADDR)
			case 2:
				m_accumulator -= m_memory[address];
				break;

			// ACC <--content(ACC) * c(ADDR)
			case 3:
				m_accumulator *= m_memory[address];
				break;
			
			// ACC <--content(ACC) / c(ADDR)
			case 4:
				m_accumulator /= m_memory[address];
				break;
			
			// ACC <--c(ADDR)
			case 5:
				m_accumulator = m_memory[address];
				break;
			
			// ADDR<--c(ACC)
			case 6:
				m_memory[address] = m_accumulator;
				break;
			
			// A line is read and its first 6 digits are
			// placed in the specified address
			case 7:
				cout << "?";
				cin >> input;
				input %= 1000000;
				m_memory[address] = input;
				break;
			
			// c(ADDR) is displayed
			case 8:
				cout << m_memory[address] << endl;
				break;
			
			// Go to ADDR for next instruction
			case 9:
				loc = address;
				break;
			
			// Go to ADDR if c(ACC) < 0
			case 10:
				if (m_accumulator < 0)
				{
					loc = address - 1;
				}
				break;

			// Go to ADDR if c(ACC) = 0
			case 11:
				if (m_accumulator == 0)
				{
					loc = address - 1;
				}
				break;

			// Go to ADDR if c(ACC) > 0
			case 12:
				if (m_accumulator > 0)
				{
					loc = address - 1;
				}
				break;
			
			// Terminate execution
			case 13:
				loc = 10000;
				break;	
			}
		}
	}
	return false;
}