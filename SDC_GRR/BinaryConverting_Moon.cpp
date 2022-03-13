/****************************************************************************
*
* Title   : Binary Converting Function
* File    : BinaryConverting_Moon.cpp
* Author  : James Moon (gyeongub.moon@samsung.com)
* Version : v1.0.0
* Date    : 2019.04.18
* Brief   : Binary Converting Code file
*
* Copyright (C) 2019 Samsung Display Company (Korea) Co., Ltd.
*
***************************************************************************/

/****************************************************************************
* v1.0.0(2019/04/18) : Initial Release (Binary Encoding/Decoding Function)
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "BinaryConverting_Moon.h"

/* Functions -----------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------
//		Binary Encode/Decode (Based on BASE64 / https://en.wikipedia.org/wiki/Base64)
//----------------------------------------------------------------------------------------------

int BinaryEncoding(char * input, char * output)
{

	int i;
	UINT8 checksum = 0;
	char checksum_char[3];

	FILE *fp_CSV;
	fopen_s(&fp_CSV, input, "rb");

	FILE *fp_BIN;
	fopen_s(&fp_BIN, output, "wb");

	if ((fp_CSV == NULL) && (fp_BIN == NULL)) {
		return 0;
	}

	if ((fp_CSV == NULL) && (fp_BIN != NULL)) {
		fclose(fp_BIN);
		return 1;
	}

	if ((fp_CSV != NULL) && (fp_BIN == NULL)) {
		fclose(fp_CSV);
		return 1;
	}

	int ch;
	int ch_cnt = 2;
	char strASCII[3];
	char strBASE64[4];
	char strResent[5];

	strASCII[2] = 0x00;
	strASCII[1] = 0x00;
	strASCII[0] = 0x00;

	while ((ch = fgetc(fp_CSV)) != EOF) {
		strASCII[ch_cnt--] = (UINT8)ch;
		strResent[0] = strResent[1];
		strResent[1] = strResent[2];
		strResent[2] = strResent[3];
		strResent[3] = strResent[4];
		strResent[4] = (UINT8)ch;

		if (ch_cnt < 0)
		{
			ch_cnt = 2;
			strBASE64[3] = ((strASCII[2] & 0XFC) >> 2);
			strBASE64[2] = ((strASCII[2] & 0X03) << 4) + ((strASCII[1] & 0XF0) >> 4);
			strBASE64[1] = ((strASCII[1] & 0X0F) << 2) + ((strASCII[0] & 0XC0) >> 6);
			strBASE64[0] = (strASCII[0] & 0X3F);

			fprintf_s(fp_BIN, "%c", strBASE64[3]);
			fprintf_s(fp_BIN, "%c", strBASE64[2]);
			fprintf_s(fp_BIN, "%c", strBASE64[1]);
			fprintf_s(fp_BIN, "%c", strBASE64[0]);

			strBASE64[3] = 0x00;
			strBASE64[2] = 0x00;
			strBASE64[1] = 0x00;
			strBASE64[0] = 0x00;
			strASCII[2] = 0x00;
			strASCII[1] = 0x00;
			strASCII[0] = 0x00;
		}
		else
		{

		}
		checksum += (UINT8)ch;


		if (strncmp(strResent, "//CS:", 5) == 0)
		{
			_itoa_s((int)checksum, checksum_char, 16);

			strASCII[ch_cnt--] = checksum_char[0];
			if (ch_cnt < 0)
			{
				ch_cnt = 2;
				strBASE64[3] = ((strASCII[2] & 0XFC) >> 2);
				strBASE64[2] = ((strASCII[2] & 0X03) << 4) + ((strASCII[1] & 0XF0) >> 4);
				strBASE64[1] = ((strASCII[1] & 0X0F) << 2) + ((strASCII[0] & 0XC0) >> 6);
				strBASE64[0] = (strASCII[0] & 0X3F);

				fprintf_s(fp_BIN, "%c", strBASE64[3]);
				fprintf_s(fp_BIN, "%c", strBASE64[2]);
				fprintf_s(fp_BIN, "%c", strBASE64[1]);
				fprintf_s(fp_BIN, "%c", strBASE64[0]);

				strBASE64[3] = 0x00;
				strBASE64[2] = 0x00;
				strBASE64[1] = 0x00;
				strBASE64[0] = 0x00;
				strASCII[2] = 0x00;
				strASCII[1] = 0x00;
				strASCII[0] = 0x00;
			}

			strASCII[ch_cnt--] = checksum_char[1];
			if (ch_cnt < 0)
			{
				ch_cnt = 2;
				strBASE64[3] = ((strASCII[2] & 0XFC) >> 2);
				strBASE64[2] = ((strASCII[2] & 0X03) << 4) + ((strASCII[1] & 0XF0) >> 4);
				strBASE64[1] = ((strASCII[1] & 0X0F) << 2) + ((strASCII[0] & 0XC0) >> 6);
				strBASE64[0] = (strASCII[0] & 0X3F);

				fprintf_s(fp_BIN, "%c", strBASE64[3]);
				fprintf_s(fp_BIN, "%c", strBASE64[2]);
				fprintf_s(fp_BIN, "%c", strBASE64[1]);
				fprintf_s(fp_BIN, "%c", strBASE64[0]);

				strBASE64[3] = 0x00;
				strBASE64[2] = 0x00;
				strBASE64[1] = 0x00;
				strBASE64[0] = 0x00;
				strASCII[2] = 0x00;
				strASCII[1] = 0x00;
				strASCII[0] = 0x00;
			}

			break;
		}

	}

	if (ch_cnt != 2)
	{
		strBASE64[3] = ((strASCII[2] & 0XFC) >> 2);
		strBASE64[2] = ((strASCII[2] & 0X03) << 4) + ((strASCII[1] & 0XF0) >> 4);
		strBASE64[1] = ((strASCII[1] & 0X0F) << 2) + ((strASCII[0] & 0XC0) >> 6);
		strBASE64[0] = (strASCII[0] & 0X3F);

		fprintf_s(fp_BIN, "%c", strBASE64[3]);
		fprintf_s(fp_BIN, "%c", strBASE64[2]);
		fprintf_s(fp_BIN, "%c", strBASE64[1]);
		fprintf_s(fp_BIN, "%c", strBASE64[0]);
	}


	fclose(fp_BIN);
	fclose(fp_CSV);

	return 0;
}


int BinaryDecoding(char * input, char * output)
{
	int i;
	UINT8 addr;
	UINT8 checksum = 0;
	char checksum_char[3];
	char checksum_Resent[3];

	FILE *fp_BIN;
	fopen_s(&fp_BIN, input, "rb");

	FILE *fp_CSV;
	fopen_s(&fp_CSV, output, "wb");

	if ((fp_CSV == NULL) && (fp_BIN == NULL)) {
		return 0;
	}

	if ((fp_CSV == NULL) && (fp_BIN != NULL)) {
		fclose(fp_BIN);
		return 1;
	}

	if ((fp_CSV != NULL) && (fp_BIN == NULL)) {
		fclose(fp_CSV);
		return 1;
	}

	int ch;
	int ch_cnt = 3;
	char strASCII[3];
	char strBASE64[4];

	strBASE64[3] = 0x00;
	strBASE64[2] = 0x00;
	strBASE64[1] = 0x00;
	strBASE64[0] = 0x00;

	while ((ch = fgetc(fp_BIN)) != EOF) {
		strBASE64[ch_cnt--] = (UINT8)ch;

		if (ch_cnt < 0)
		{
			ch_cnt = 3;
			strASCII[2] = ((strBASE64[3] & 0x3F) << 2) + ((strBASE64[2] & 0X30) >> 4);
			strASCII[1] = ((strBASE64[2] & 0X0F) << 4) + ((strBASE64[1] & 0X3C) >> 2);
			strASCII[0] = ((strBASE64[1] & 0X03) << 6) + (strBASE64[0] & 0x3F);

			checksum += strASCII[2] + strASCII[1] + strASCII[0];

			checksum_Resent[1] = strASCII[1];
			checksum_Resent[0] = strASCII[0];

			if (strASCII[2] != 0x00) fprintf_s(fp_CSV, "%c", strASCII[2]);
			if (strASCII[1] != 0x00) fprintf_s(fp_CSV, "%c", strASCII[1]);
			if (strASCII[0] != 0x00) fprintf_s(fp_CSV, "%c", strASCII[0]);

			strBASE64[3] = 0x00;
			strBASE64[2] = 0x00;
			strBASE64[1] = 0x00;
			strBASE64[0] = 0x00;
			strASCII[2] = 0x00;
			strASCII[1] = 0x00;
			strASCII[0] = 0x00;
		}
		else
		{

		}
	}

	if (ch_cnt != 3)
	{
		ch_cnt = 3;
		strASCII[2] = ((strBASE64[3] & 0x3F) << 2) + ((strBASE64[2] & 0X30) >> 4);
		strASCII[1] = ((strBASE64[2] & 0X0F) << 4) + ((strBASE64[1] & 0X3C) >> 2);
		strASCII[0] = ((strBASE64[1] & 0X03) << 6) + (strBASE64[0] & 0x3F);

		if (strASCII[2] != 0x00)
		{
			checksum_Resent[0] = checksum_Resent[1];
			checksum_Resent[1] = strASCII[2];
			checksum += (UINT8)strASCII[2];
			fprintf_s(fp_CSV, "%c", strASCII[2]);
		}
		if (strASCII[1] != 0x00)
		{
			checksum_Resent[0] = checksum_Resent[1];
			checksum_Resent[1] = strASCII[1];
			checksum += (UINT8)strASCII[1];
			fprintf_s(fp_CSV, "%c", strASCII[1]);
		}
		if (strASCII[0] != 0x00)
		{
			checksum_Resent[0] = checksum_Resent[1];
			checksum_Resent[1] = strASCII[0];
			checksum += (UINT8)strASCII[0];
			fprintf_s(fp_CSV, "%c", strASCII[0]);
		}
	}

	fclose(fp_BIN);
	fclose(fp_CSV);

	checksum = checksum - (UINT8)checksum_Resent[0] - (UINT8)checksum_Resent[1];
	_itoa_s(checksum, checksum_char, 16);

	if (strncmp(checksum_Resent, checksum_char, 2) == 0)
	{
		return 1;
	}

	return 0;
}