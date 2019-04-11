//  Implementation of file access class.
#include "stdafx.h"
#include "FileAccess.h"



/*
FileAccess::FileAccess()

NAME
	FileAccess::FileAccess(int argc, char* argv[]) - constructor for FileAccess Class

SYNOPSIS
	FileAccess::FileAccess(int argc, char * argv[])
		argc --> the number of arguments received as command line arguments
		argv --> the names of the arguments received

DESCRIPTION
	This function will validate the number of arguments received by the program. 
	Then, proceeds towards opening the file for reading. It will report to the console and 
	exits if reading from the file was not possible.

RETURNS
	Exits from the program if the files could not be opened or if there were not enough
	command line arguments
*/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) 
	{
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) 
	{
        cerr << "Source file could not be opened, assembler terminated." << endl;
        exit( 1 ); 
    }
}




/*
FileAccess::~FileAccess()

NAME
	FileAccess::~FileAccess() - destructor for FileAccess Class

SYNOPSIS
	FileAccess::~FileAccess()

DESCRIPTION
	The function will close the file which we had opened for reading	

RETURNS
	The function will not return a value.
*/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates.
    m_sfile.close( );
}




 /*
 bool FileAccess::GetNextLine()

 NAME
	 bool FileAccess::GetNextLine( string &a_buff)
 
 SYNOPSIS
	 bool FileAccess::GetNextLine (string &a_buff)
		a_buff -> the next line in the buffer. The value is passed by reference

 DESCRIPTION
	 The function will read a line from our source file and try to read until there 
	 is no more data or if it reached the end of file.

 RETURNS
	 The function will return false if it has reached the end of file and there is no 
	 data to read. Else, it will get the next line in the source file and pass the string 
	 as referenced value. After, it will return true since it was able to read from the file.

 */
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) 
	{
        return false;
    }
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
}




 /*
 void FileAccess::rewind( )

 NAME
	 void FileAccess::rewind( ) - resetting file descriptors

 SYNOPSIS
	 void FileAccess::rewind( )
		-> the function will not receive any parameters	

 DESCRIPTION
	 The function will reset all the file descriptors associated with the read file
	 and then point the file descriptor to the beginning of the file
 
 RETURNS
	 The function will not return anything

 */
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}