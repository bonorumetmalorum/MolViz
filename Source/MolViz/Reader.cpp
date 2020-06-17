// Fill out your copyright notice in the Description page of Project Settings.


#include "Reader.h"

IReader::IReader()
{
}

IReader::~IReader()
{
}

bool IReader::ReadLine(IFileHandle * Data, uint8* Outbuffer, SIZE_T MaxRead)
{
	if(Data && Outbuffer)
	{ //if we have a valid pointer to a file data and storage buffer
		int Counter = 0;
		uint8 CurrentChar;
		while(Data->Read(&CurrentChar, 1) && Counter < MaxRead)
		{
			if(CurrentChar == '\n')
			{ //if we found the end of the line
				return true;	
			}
			*Outbuffer = CurrentChar;
			Outbuffer++;
			Counter++;
		}
		if(Counter == MaxRead)
		{// we were able to read the full amount
			return true;
		}
	}
	return false;
}

FString IReader::BytesToString(const uint8* Bytes, SIZE_T Count)
{
	FString Result;
	Result.Empty(Count);

	while (Count)
	{
		// Put the byte into an int16 and add 1 to it, this keeps anything from being put into the string as a null terminator
		Result += TCHAR(*Bytes);

		++Bytes;
		Count--;
	}
	return Result;
}
