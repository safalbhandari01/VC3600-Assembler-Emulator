//ssembler Class Implementation
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/*
Assembler::Assembler()

NAME
Assembler::Assembler(int argc, char* argv[]) - constructor for Assembler Class

SYNOPSIS
Assembler::Assembler(int argc, char * argv[])
argc --> the number of arguments received as command line arguments
argv --> the names of the arguments received

DESCRIPTION
This function acts as a starting point for our Assembler class. It will pass the no. of
arguments and the arguments as parameters for FileAccess class to instantiate the class

RETURNS
Exits from the program if the files could not be opened or if there were not enough
command line arguments
*/
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{

}

/*
Assembler::PassI()
NAME
Assembler::PassI() - Implements PassI method for the class
SYNOPSIS
Assembler::PassI()
->No parameters required
DESCRIPTION
This function establishes the location of the labels by parsing the source file.

RETURNS
The function will return if it there are no lines to read at the end of the file or
if it encounters a comment.


*/
void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

						// Successively process each line of source code.
	for (; ; )
	{

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff))
		{
			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}

		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel())
		{
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}


/*
Assembler::PassII()

NAME
Assembler::PassII() - Implements PassII method for the class

SYNOPSIS
Assembler::PassII()
->No parameters required

DESCRIPTION
This function will use the symbol table that we generated in PassI to translate the
numeric operands into numeric values.

The function will also print the translation of our assembly language to the console as it
parses our source file.

RETURNS
No return values


*/
void Assembler::PassII()
{
	// Prepare to reread the source file
	m_facc.rewind();

	int loc = 0;        // Tracks the location of the instructions.
	int contents;		// Contents of the translation

						// Output Formatting
	cout << "\nTranslation of Program:" << endl;
	cout << setw(9) << "\nLocation " << setw(9) << "Contents ";
	cout << left;
	cout << "\tOriginal Statement " << endl;


	for (; ; )
	{
		contents = 0;

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff))
		{

			// Report it as an error, if no lines
			Errors::RecordError("End Statement Missing!");
			break;
		}

		// Parses line and gets the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// Report error if illegal label format
		if (m_inst.GetLabel()[0] <= '9' && m_inst.GetLabel()[0] >= '0')
		{
			Errors::RecordError(m_inst.GetLabel() + " :Illegal. Label can only start with an alpha character.");
		}
		else if (m_inst.GetLabel().length() > 10)
		{
			Errors::RecordError(m_inst.GetLabel() + " :Illegal. Label can only be between 1-10 characters.");
			m_inst.SetLabel("?");
		}


		// Report error if illegal OpCode format
		if (st == Instruction::ST_Illegal)
		{
			Errors::RecordError(m_inst.GetOpCode() + " :Illegal opcode!");
		}

		// Report error if illegal operand
		if (m_inst.isNumericOperand())
		{
			if (m_inst.GetNumericOperand() > 999999)
			{
				Errors::RecordError("Illegal. The value of " + m_inst.GetOpCode() + " is too high");
			}
		}

		// Determine if the end is the last statement.
		if (st == Instruction::ST_End)
		{
			cout << "\t \t \t" << m_inst.GetInstruction() << endl;
			break;
		}

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			cout << "\t \t \t" << m_inst.GetInstruction() << endl;
			continue;
		}

		//get the content of machine level instruction
		contents = m_inst.GetNumericOpCode() * 10000;

		//compute the 4 digit equivalent of machine language instruction
		if (st == Instruction::ST_AssemblerInstr)
		{
			// Check and record any errors in the operand, opcode 
			if (m_inst.GetOpCode() != "end")
			{
				if (m_inst.GetOperand().empty())
				{
					Errors::RecordError("Empty Operand equivalent for the opcode.");
				}
				else if (!m_inst.isNumericOperand())
				{
					Errors::RecordError(m_inst.GetOperand() + " :Illegal. Operand needs to be numeric.");
				}

				if (m_inst.GetOpCode() != "org" && m_inst.GetLabel().empty())
				{
					Errors::RecordError("Invalid. Label for the opcode " + m_inst.GetOpCode() + " missing");
				}
			}

			//add the operand to the contents
			if (m_inst.GetOpCode() == "dc")
			{
				contents += m_inst.GetNumericOperand();
			}
		}

		// If the instruction is not Assembly Language, then compute the content
		// by looking up the symbol location in the symbol table 
		else
		{
			if (m_inst.GetOperand().empty() && m_inst.GetNumericOpCode() != 13)
			{
				Errors::RecordError(m_inst.GetOpCode() + " :Illegal. Operand missing in opcode!");
			}

			else if (!m_inst.isNumericOperand() && !m_inst.GetOperand().empty())
			{
				int locationOfSymbol = 0;

				// check if any operands corresponding to the location of the symbol exists
				if (!m_symtab.LookupSymbol(m_inst.GetOperand(), locationOfSymbol))
				{
					Errors::RecordError("Illegal. Symbol " + m_inst.GetOperand() + " not found");
					locationOfSymbol = 9999;
				}

				//	add the location to our contents
				contents += locationOfSymbol;
			}
		}

		// Start output of translation
		cout << setfill(' ') << setw(5) << loc << "\t";

		// Insert location and contents to the accumulator
		m_emul.insertMemory(loc, contents);

		string contentString = "";

		// Handle empty contents while printing
		if (contents == 0)
		{
			cout << "\t";
		}
		else
		{
			// Insert leading zeros in front of the contents 
			// ensure contents are of width 6
			contentString = string(6 - to_string(contents).length(), '0') + to_string(contents);

			cout << "  " << contentString;
		}
		cout << "\t" << m_inst.GetInstruction() << endl;

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}

	// display errors to the console once we read through the file
	Errors::DisplayErrors();
}


/*
Assembler::RunEmulator()

NAME
Assembler::RunEmulator() - Emulator for VC3600 compiler

SYNOPSIS
Assembler::RunEmulator()
->No parameters required

DESCRIPTION
This function will use the translation that we generated in Pass II to emulate the instructions
for our VC3600 compiler. The function will only run if there were no errors reported during Pass II.

RETURNS
The function will not return any values.


*/
void Assembler::RunEmulator()
{
	// check if Pass II reported any errors
	if (!Errors::CheckErrorMsgs())
	{
		cout << "Emulator cannot be run while there are errors. " << endl;
	}
	// proceed to emulating VC3600 compiler as there were no errors
	else
	{
		m_emul.runProgram();
	}
}