/****************************************************************************
*
* Title   : Binary Converting Function
* File    : BinaryConverting_Moon.h
* Author  : James Moon (gyeongub.moon@samsung.com)
* Version : v1.0.0
* Date    : 2019.04.18
* Brief   : Binary Converting Header file
*
* Copyright (C) 2019 Samsung Display Company (Korea) Co., Ltd.
*
***************************************************************************/

/****************************************************************************
* v1.0.0(2019/04/18) : Initial Release (Binary Encoding/Decoding Function)
****************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/


/* Macros --------------------------------------------------------------------*/


/* Settings ------------------------------------------------------------------*/


/* Types definition ----------------------------------------------------------*/
/*
typedef enum
{
	BINARY_ENCODE_OK = 0x00,
	BINARY_ENCODE_NULL_POINTER = 0x01,
	BINARY_ENCODE_OUT_BUFFER_OVERFLOW = 0x02
} binary_encode_status;

typedef struct
{
	size_t              out_len;
	binary_encode_status  status;
} binary_encode_result;


typedef enum
{
	BINARY_DECODE_OK = 0x00,
	BINARY_DECODE_NULL_POINTER = 0x01,
	BINARY_DECODE_OUT_BUFFER_OVERFLOW = 0x02,
	BINARY_DECODE_ZERO_BYTE_IN_INPUT = 0x04,
	BINARY_DECODE_INPUT_TOO_SHORT = 0x08,
	//////////////////////////////////////////////
	// add CRC Error Code (19/02/19 James Moon) //
	BINARY_DECODE_CRC_ERROR = 0x80,
	FILE_NOT_FOUND = 0x40
	//////////////////////////////////////////////
} binary_decode_status;

typedef struct
{
	size_t              out_len;
	binary_decode_status  status;
} binary_decode_result;
*/


/* Function prototypes -------------------------------------------------------*/

int BinaryEncoding(char * input, char * output);
int BinaryDecoding(char * input, char * output);