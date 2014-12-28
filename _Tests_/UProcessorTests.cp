// ==============================
// Fichier:			UProcessorTests.cp
// Projet:			Einstein
// Ecrit par:		Paul Guyot (pguyot@kallisys.net)
// 
// Créé le:			27/7/2004
// Tabulation:		4 espaces
// 
// Copyright:		© 2004 by Paul Guyot.
// 					Tous droits réservés pour tous pays.
// ===========
// $Id: UProcessorTests.cp 151 2006-01-13 16:15:33Z paul $
// ===========

#include <K/Defines/KDefinitions.h>
#include "UProcessorTests.h"

// ANSI C & POSIX
#include <stdlib.h>

#if !TARGET_OS_WIN32
	#include <unistd.h>
#endif

// K
#include <K/Defines/UByteSex.h>

// Einstein
#include "Emulator/ROM/TFlatROMImageWithREX.h"
#include "Emulator/Log/TLog.h"
#include "Emulator/TMemory.h"
#include "Emulator/TEmulator.h"
#include "Emulator/TInterruptManager.h"
#include "Emulator/TARMProcessor.h"
#include "Emulator/JIT/JIT.h"
#include "Emulator/JIT/TJITPage.h"
#include "Emulator/Sound/TNullSoundManager.h"
#include "Emulator/Network/TUsermodeNetwork.h"
#include "Emulator/Screen/TNullScreenManager.h"

// -------------------------------------------------------------------------- //
// Constantes
// -------------------------------------------------------------------------- //
#if TARGET_OS_WIN32
	#define kTempFlashPath "c:/EinsteinTests.flash"
#else
	#define kTempFlashPath "/tmp/EinsteinTests.flash"
#endif

// -------------------------------------------------------------------------- //
//  * ExecuteInstruction( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::ExecuteInstruction( const char* inHexWord, TLog* inLog )
{
	KUInt32 theInstruction;
	if (inHexWord == nil)
	{
		(void) ::printf( "This test requires an instruction in hexa.\n" );
	} else if (::sscanf(
					inHexWord,
					"%X",
					(unsigned int*) &theInstruction ) != 1) {
		(void) ::printf( "Can't parse instruction (%s).\n", inHexWord );
	} else {
		KUInt8* rom = (KUInt8*) ::calloc( 8 * 1024 * 1024, 1 );
		((KUInt32*) rom)[0] = theInstruction;
		TMemory theMem( inLog, rom, kTempFlashPath );
		TARMProcessor theProcessor( inLog, &theMem );
		theMem.GetJITObject()->Step( &theProcessor, 1 );
		theProcessor.PrintRegisters();
		(void) ::unlink( kTempFlashPath );
		::free( rom );
	}
}

// -------------------------------------------------------------------------- //
//  * ExecuteInstructionState1( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::ExecuteInstructionState1( const char* inHexWord, TLog* inLog )
{
	KUInt32 theInstruction;
	if (inHexWord == nil)
	{
		(void) ::printf( "This test requires an instruction in hexa.\n" );
	} else if (::sscanf(
					inHexWord,
					"%X",
					(unsigned int*) &theInstruction ) != 1) {
		(void) ::printf( "Can't parse instruction (%s).\n", inHexWord );
	} else {
		KUInt8* rom = (KUInt8*) ::calloc( 8 * 1024 * 1024, 1 );
		((KUInt32*) rom)[0] = theInstruction;
		TMemory theMem( inLog, rom, kTempFlashPath );
		TARMProcessor theProcessor( inLog, &theMem );
		theProcessor.SetRegister( 0, 0x01020304 );
		theProcessor.SetRegister( 1, 0x05060708 );
		theProcessor.SetRegister( 2, 0x090A0B0C );
		theProcessor.SetRegister( 3, 0x0D0E0F10 );
		theProcessor.SetRegister( 4, 0x11121314 );
		theProcessor.SetRegister( 5, 0x15161718 );
		theProcessor.SetRegister( 6, 0x191A1B1C );
		theProcessor.SetRegister( 7, 0x1D1E1F20 );
		theProcessor.SetRegister( 8, 0x21222324 );
		theProcessor.SetRegister( 9, 0x25262728 );
		theProcessor.SetRegister( 10, 0x292A2B2C );
		theProcessor.SetRegister( 11, 0x2D2E2F30 );
		theProcessor.SetRegister( 12, 0x31323334 );
		theProcessor.SetRegister( 13, 0x35363738 );
		theProcessor.SetRegister( 14, 0x393A3B3C );
//		theProcessor.SetRegister( 15, 0x00000004 );
		theMem.GetJITObject()->Step( &theProcessor, 1 );
		theProcessor.PrintRegisters();
		(void) ::unlink( kTempFlashPath );
		::free( rom );
	}
}

// -------------------------------------------------------------------------- //
//  * ExecuteInstructionState2( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::ExecuteInstructionState2( const char* inHexWord, TLog* inLog )
{
	KUInt32 theInstruction;
	if (inHexWord == nil)
	{
		(void) ::printf( "This test requires an instruction in hexa.\n" );
	} else if (::sscanf(
					inHexWord,
					"%X",
					(unsigned int*) &theInstruction ) != 1) {
		(void) ::printf( "Can't parse instruction (%s).\n", inHexWord );
	} else {
		KUInt8* rom = (KUInt8*) ::calloc( 8 * 1024 * 1024, 1 );
		((KUInt32*) rom)[0] = theInstruction;
		TMemory theMem( inLog, rom, kTempFlashPath );
		TARMProcessor theProcessor( inLog, &theMem );
		theProcessor.SetRegister( 3, 0x00000020 );
		theProcessor.SetRegister( 12, 0xFFFFFFFF );
//		theProcessor.SetRegister( 15, 0x00000004 );
		theMem.GetJITObject()->Step( &theProcessor, 1 );
		theProcessor.PrintRegisters();
		(void) ::unlink( kTempFlashPath );
		::free( rom );
	}
}

// -------------------------------------------------------------------------- //
//  * ExecuteTwoInstructions( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::ExecuteTwoInstructions( const char* inHexWords, TLog* inLog )
{
	KUInt32 theInstructions[2];
	if (inHexWords == nil)
	{
		(void) ::printf( "This test requires two instructions in hexa.\n" );
	} else if (::sscanf(
					inHexWords,
					"%X-%X",
					(unsigned int*) &theInstructions[0],
					(unsigned int*) &theInstructions[1] ) != 2) {
		(void) ::printf( "Can't parse instructions (%s).\n", inHexWords );
	} else {
		KUInt8* rom = (KUInt8*) ::calloc( 8 * 1024 * 1024, 1 );
		((KUInt32*) rom)[0] = theInstructions[0];
		((KUInt32*) rom)[1] = theInstructions[1];
		TMemory theMem( inLog, rom, kTempFlashPath );
		TARMProcessor theProcessor( inLog, &theMem );
		theMem.GetJITObject()->Step( &theProcessor, 2 );
		theProcessor.PrintRegisters();
		(void) ::unlink( kTempFlashPath );
		::free( rom );
	}
}

// -------------------------------------------------------------------------- //
//  * RunCode( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::RunCode( const char* inHexWords, TLog* inLog ) {
	if (inHexWords == nil)
	{
		(void) ::printf( "This test requires code in hexa\n" );
	} else {
		KUInt8* rom = (KUInt8*) ::calloc( 8 * 1024 * 1024, 1 );
		KUInt32* theCodePtr = (KUInt32*) rom;
		int nbBytes;
		KUInt32 registers[16];
		::memset(registers, 0, sizeof(registers));
		registers[15] = 4;
		unsigned theRegister;
		KUInt32 theValue;
		while (::sscanf(inHexWords, "R%u=%X %n", &theRegister, &theValue, &nbBytes) == 2) {
			if (theRegister > 15) {
				(void) ::printf( "Invalid register ! R%u\n", theRegister );
				return;
			}
			registers[theRegister] = theValue;
			inHexWords += nbBytes;
		}
		while (::sscanf(inHexWords, "%X %n", theCodePtr, &nbBytes) == 1) {
			inHexWords += nbBytes;
			theCodePtr++;
		}
		if (inLog) {
			inLog->FLogLine("Parsed %d instruction(s).", (int) ((theCodePtr - (KUInt32*)rom)));
		}

		TEmulator theEmulator(inLog, rom, kTempFlashPath);
		TARMProcessor* theProcessor = theEmulator.GetProcessor();
		for (theRegister = 0; theRegister < 16; theRegister++) {
			theProcessor->SetRegister(theRegister, registers[theRegister]);
		}
		theEmulator.Run();
		theProcessor->PrintRegisters();
		(void) ::unlink( kTempFlashPath );
		::free( rom );
	}
}


// -------------------------------------------------------------------------- //
//  * Step( const char* )
// -------------------------------------------------------------------------- //
void
UProcessorTests::Step( const char* inCount, TLog* inLog )
{
	KUInt32 count;
	if (inCount == nil)
	{
		(void) ::printf( "This test requires a number of steps in decimal.\n" );
	} else if (::sscanf( inCount, "%d", (unsigned int*) &count ) != 1) {
		(void) ::printf( "Can't parse number of steps (%s).\n", inCount );
	} else {
		// Load the ROM.
		TFlatROMImageWithREX theROM(
			"../../_Data_/717006", "../../_Data_/Einstein.rex", "717006" );
		TNullSoundManager soundManager;
		TUsermodeNetwork networkManager(inLog);
		TNullScreenManager screenManager(inLog);
		TEmulator theEmulator(inLog, &theROM, kTempFlashPath, &soundManager, &screenManager, &networkManager);

		theEmulator.GetMemory()->GetJITObject()->Step( theEmulator.GetProcessor(), count );
		theEmulator.GetProcessor()->PrintRegisters();
		(void) ::unlink( kTempFlashPath );
	}
}

// ========================================================================== //
// APL is a mistake, carried through to perfection.  It is the language of    //
// the future for the programming techniques of the past: it creates a new    //
// generation of coding bums.                                                 //
//               -- Edsger W. Dijkstra, SIGPLAN Notices, Volume 17, Number 5  //
// ========================================================================== //
