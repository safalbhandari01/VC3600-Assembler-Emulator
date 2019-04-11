
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
#pragma once
#include "stdafx.h"

// Instruction Class
class Instruction
{

public:

	Instruction();
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  
	enum InstructionType
	{
		ST_MachineLanguage, // machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,         // Comment or blank line
		ST_End,             // end instruction.
		ST_Illegal
	};

	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel()
	{
		return m_Label;
	}
	// To determine if a label is blank.
	inline bool isLabel()
	{
		return !m_Label.empty();
	}

	// To access the numeric equivalent of the op code
	inline int &GetNumericOpCode()
	{
		return m_NumOpCode;
	}

	// To access the opcode
	inline string &GetOpCode()
	{
		return m_OpCode;
	}

	// To access the numeric equivalent of the operand
	inline int &GetNumericOperand()
	{
		return m_OperandValue;
	}

	// To access the operand
	inline string &GetOperand()
	{
		return m_Operand;
	}

	// To access the instruction
	inline string &GetInstruction()
	{
		return m_instruction;
	}

	// To determine if the operand is numeric
	inline bool &isNumericOperand()
	{
		return m_IsNumericOperand;
	}

	// To set the value of op code
	inline void SetOpCode(string a_newOpCode)
	{
		m_OpCode = a_newOpCode;
	}

	// To set the label
	inline void SetLabel(string a_newLabel)
	{
		m_Label = a_newLabel;
	}

	// To set the operand
	inline void SetOperand(string a_newOperand)
	{
		m_Operand = a_newOperand;
	}

private:


	// The elements of a instruction
	string m_Label;			// The label.
	string m_OpCode;		// The symbolic op code.
	string m_Operand;		// The operand.


	string m_instruction;   // The original instruction.

							// Derived values.
	int m_NumOpCode;		// The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;		// The value of the operand if it is numeric.

							//store allowed opcode values in respective language
	vector <string> MACHINE_LANG_OPCODE;
	vector <string> ASSEMBLY_LANG_OPCODE;
};