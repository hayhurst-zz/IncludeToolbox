#pragma once

#include <cinttypes>

#ifdef INCLUDEPARSER_EXPORTS
	#define INCLUDEPARSER_API __declspec(dllexport)
#else
	#define INCLUDEPARSER_API __declspec(dllimport)
#endif

// Error handling.
typedef int32_t Result;
enum ResultCodes
{
	RESULT_FAILURE,
	RESULT_SUCCESS,
};



// All incoming and outgoing strings are (expected to be) UTF8 encoded and null-terminated!
// String handles are used to pass strings from within the library to the outside:
// All strings generated by this library will be stored in a map instead of beeing passed directly which can be accessed using StringHandle.
typedef int32_t StringHandle;

extern "C"
{
	extern INCLUDEPARSER_API void __stdcall Init();
	extern INCLUDEPARSER_API void __stdcall Exit();

	// Writes string identified by handle into the given buffer and removes it from the internal map.
	extern INCLUDEPARSER_API Result __stdcall ResolveString(StringHandle handle, char* buffer, int32_t bufferSize);
	// Gets the needed buffer size of a string in bytes (include null termination).
	extern INCLUDEPARSER_API Result __stdcall GetStringLength(StringHandle handle, int32_t* outBufferSize);


	// includeDirectories: Directories to look for includes separated by ';', paths relative to the file itself will be resolved automatically.
	// preprocessorDefinitions: Global preprocessor definitions, separated by ';'
	// outIncludeTreeString: Every line contains an include (new line using '\n'). Number of tabs '\t' gives tree relation. Example:
	//	C:/blub/included0.h
	//		C:/blub/File0.h
	//			C:/blub/IncludedByFile0.h
	//		C:/blub/File1.h
	//		C:/blub/File2.h
	//	C:/blab/included1.h
	extern INCLUDEPARSER_API Result __stdcall ParseIncludes(const char* inputFilename, const char* includeDirectories, const char* preprocessorDefinitions, 
															StringHandle* outProcessedInputFile, StringHandle* outIncludeTree);
}