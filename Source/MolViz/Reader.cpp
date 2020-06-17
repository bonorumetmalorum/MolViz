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
			Outbuffer++;
			*Outbuffer = CurrentChar;
			Counter++;
		}
		if(Counter == MaxRead)
		{// we were able to read the full amount
			return true;
		}
	}
	return false;
}
