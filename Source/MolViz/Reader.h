// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Base functionality that all readers must implement
 */
class MOLVIZ_API IReader
{
public:
	IReader();
	virtual ~IReader();
	virtual void readStructure(FString filepath, AActor * Structure) = 0;
protected:
	/*
	 * used to read a line from a given file
	 * @param Data file handle to the file we are reading from
	 * @param OutData the buffer to which we are reading file contents to
	 * @param maxRead the max amount of characters we can read
	 * @return true if successful false otherwise
	 */
	bool ReadLine(IFileHandle * Data, uint8* OutData, SIZE_T maxRead);
	/*
	 * used to read a line from a given file
	 * @param Data file handle to the file we are reading from
	 * @param OutData the buffer to which we are reading file contents to
	 * @param ReadFrom the location to start reading from
	 * @param maxRead the max amount of characters we can read
	 * @return true if successful false otherwise
	 */
	bool ReadLine(FString& Data, uint8* Outbuffer, SIZE_T & ReadFrom, SIZE_T MaxRead);
	/*
	 * helper function to convert a number of bytes into a FString
	 * @param bytes the byte array to read from
	 * @param count the number bytes to read
	 * @return the FString of bytes read
	 */
	FString BytesToString(const uint8* bytes, SIZE_T count);
};
