
// Implementation of Instruction class
#include "stdafx.h"
#include "Instruction.h"


/*
Instruction::Instruction()

NAME
Instruction::Instruction() - constructor for Instruction class
SYNOPSIS
Instruction::Instruction()
-> Does not accept any parameters
DESCRIPTION
The function acts as a contructor to store all the applicable machine level opcodes and
assembly language opcode into separate string vectors.
RETURNS
The function will not return a value

*/
Instruction::Instruction()
{
	MACHINE_LANG_OPCODE = { "add", "sub", "mult", "div", "load", "store", "read", "write", "b", "bm", "bz", "bp", "halt" };
	ASSEMBLY_LANG_OPCODE = { "dc", "ds", "org", "end" };
	m_IsNumericOperand = true;
}

/*
Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)

NAME
Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)
- parse the instructions from pass I and pass II

SYNOPSIS
Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)
a_buff -> word passed in as string to determine its instruction type

DESCRIPTION
The function will parse the string passed in as instruction and decide the instruction
type of the string.

RETURNS
The function will return the instruction type for the particular word in the line.

*/
Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)
{
	//clear all necessary variables
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = "";
	m_NumOpCode = 0;
	m_OperandValue = 999999;
	m_IsNumericOperand = true;
	bool containsComment = false;
	//store the original instruction
	m_instruction = a_buff;

	//create an istringstream object and initialize
	//it to the passed string 
	istringstream readLine(a_buff);

	string word;
	int countWordsInLine = 0;

	//extract words from the buffer
	readLine >> word;

	//check if the entire line is a comment
	if (word.at(0) == ';')
	{
		return ST_Comment;
	}

	//check if the line is empty
	if (word.empty())
	{
		return ST_Comment;
	}

	while (word.size() != 0)
	{
		int indexOfComment = word.find(';');

		//if the first element has ';', then the entire line is a comment
		//break from the loop
		if (indexOfComment >= 0) {

			//extract the substring without comment
			containsComment = true;

			if (indexOfComment == 0) { break; }

			word = word.substr(0, indexOfComment);
		}

		if (countWordsInLine == 0)
		{
			m_Label = word;
		}
		else if (countWordsInLine == 1)
		{
			m_OpCode = word;
		}
		else if (countWordsInLine == 2)
		{
			m_Operand = word;
		}
		//clear the buffer and read the next word in the line
		word = "";
		readLine >> word;
		countWordsInLine++;

		if (containsComment)
		{
			break;
		}
	}

	//if the line only has two words, then it does not have a label
	//fix the correct values for opcode and operand
	if (countWordsInLine == 2)
	{
		if (find(MACHINE_LANG_OPCODE.begin(), MACHINE_LANG_OPCODE.end(), m_OpCode) == MACHINE_LANG_OPCODE.end())
		{
			if (find(ASSEMBLY_LANG_OPCODE.begin(), ASSEMBLY_LANG_OPCODE.end(), m_OpCode) == ASSEMBLY_LANG_OPCODE.end())
			{
				m_Operand = m_OpCode;
				m_OpCode = m_Label;
				m_Label = "";
			}
		}
	}

	//if the line only has one word, then the word is an opcode and there are no labels
	if (countWordsInLine == 1)
	{
		m_OpCode = m_Label;
		m_Label = "";
	}

	//transform all machine Opcode into lowercase letters
	transform(m_OpCode.begin(), m_OpCode.end(), m_OpCode.begin(), tolower);

	//check the instruction type of the opcode
	if (find(MACHINE_LANG_OPCODE.begin(), MACHINE_LANG_OPCODE.end(), m_OpCode) != MACHINE_LANG_OPCODE.end())
	{
		m_type = ST_MachineLanguage;

		//evaluate the numerical equivalent of the op code
		m_NumOpCode = distance(MACHINE_LANG_OPCODE.begin(), find(MACHINE_LANG_OPCODE.begin(), MACHINE_LANG_OPCODE.end(), m_OpCode)) + 1;
	}
	else if (m_OpCode == "end")
	{
		m_type = ST_End;
	}
	// check if the word is an assembly language instruction
	else if (find(ASSEMBLY_LANG_OPCODE.begin(), ASSEMBLY_LANG_OPCODE.end(), m_OpCode) != ASSEMBLY_LANG_OPCODE.end())
	{
		m_type = ST_AssemblerInstr;
	}
	else
	{
		m_type = ST_Illegal;
	}

	//try to convert the operand to numerical value
	try
	{
		m_OperandValue = stoi(m_Operand);
	}
	catch (invalid_argument&)
	{
		m_IsNumericOperand = false;
	}

	return m_type;

}


/*
int Instruction::LocationNextInstruction()

NAME
int Instruction::LocationNextInstruction(int a_loc) -> locate the next instruction

SYNOPSIS
int Instruction::LocationNextInstruction(int a_loc)
a_loc -> get the location for the next instruction

DESCRIPTION
The function will evaluate the next location of the instruction by identifying the opcode name.
if the opcode was "ds" (define storage) or "org" (the origin of the program), then their corresponding
operand value will be added to the location, else the location will be incremented by one.

RETURNS
The function will return the next location of the instruction

*/
int Instruction::LocationNextInstruction(int a_loc)
{
	if (m_OpCode == "ds" || m_OpCode == "org")
	{
		return a_loc + m_OperandValue;
	}
	return ++a_loc;
}