//Emulator class - supports the emulation of VC3600 programs
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class Emulator 
{
public:

    const static int MEMSZ = 10000;	// The size of the memory of the VC3600.
    Emulator() 
	{
        memset( m_memory, 0, MEMSZ * sizeof(int) );
    }
    // Records instructions and data into VC3600 memory.
    bool insertMemory( int a_location, int a_contents );
    
    // Runs the VC3600 program recorded in memory.
    bool runProgram( );

private:

    int m_memory[MEMSZ];       // The memory of the VC3600.
    int m_accumulator;			// The accumulator for the VC3600
};

#endif