#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "calculation.h"
#include <string.h>


double d1[21] = { 1, 1, 1.12838, 1.69257, 2.05875, 2.32593, 2.53441, 2.70436, 2.8472, 2.97003, 3.07751, 3.17287, 3.25846, 3.33598, 3.40676, 3.47193, 3.53198, 3.58788, 3.64006, 3.68896, 3.735 };
double d2[21][21] = {
	{ 1, 1, 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1      , 1 },
	{ 1, 1, 1.41421, 1.91155, 2.23887, 2.48124, 2.7253 , 2.82981, 2.96288, 3.07794, 3.17905, 3.26909, 3.35016, 3.42378, 3.49116, 3.55333, 3.61071, 3.66422, 3.71424, 3.76118, 3.80537 },
	{ 1, 1, 1.27931,	1.80538, 2.15069, 2.40484, 2.60438, 2.76779, 2.90562, 3.02446, 3.12869, 3.22134, 3.30463, 3.38017, 3.44922, 3.51287, 3.57156, 3.62625, 3.67734, 3.72524, 3.77032 },
	{ 1, 1, 1.23105, 1.76858, 2.12049, 2.37883, 2.58127, 2.74681, 2.88628, 3.00643, 3.11173, 3.20526, 3.28931, 3.3655 , 3.43512, 3.49927, 3.55842, 3.61351, 3.66495, 3.71319, 3.75857 },
	{ 1, 1, 1.20621, 1.74989, 2.10522, 2.36571, 2.56964, 2.73626, 2.87656, 2.99737, 3.10321, 3.1972 , 3.28163, 3.35815, 3.42805, 3.49246, 3.55183, 3.60712, 3.65875, 3.70715, 3.75268 },
	{ 1, 1, 1.19105, 1.73857, 2.09601, 2.35781, 2.56263, 2.72991, 2.87071, 2.99192, 3.09808, 3.19235, 3.27701, 3.35372, 3.42381, 3.48836, 3.54787, 3.60328, 3.65502, 3.70352, 3.74914 },
	{ 1, 1, 1.18083, 1.73099, 2.08985, 2.35253, 2.55795, 2.72567, 2.8668 , 2.98829, 3.09467, 3.18911, 3.27392, 3.35077, 3.42097, 3.48563, 3.54522, 3.60072, 3.65253, 3.70109, 3.74678 },
	{ 1, 1, 1.17348, 1.72555, 2.08543, 2.34875, 2.5546 , 2.72263, 2.86401, 2.98568, 3.09222, 3.18679, 3.27172, 3.34866, 3.41894, 3.4368 , 3.54333, 3.59888, 3.65075, 3.69936, 3.74509 },
	{ 1, 1, 1.16794, 1.72147, 2.08212, 2.34591, 2.55208, 2.72036, 2.86192, 2.98373, 3.09039, 3.18506, 3.27006, 3.34708, 3.41742, 3.48221, 3.54192, 3.59751, 3.64941, 3.69806, 3.74382 },
	{ 1, 1, 1.16361, 1.71828, 2.0795 , 2.3437 , 2.55013, 2.71858, 2.86028, 2.98221, 3.08896, 3.1837 , 3.26878, 3.34585, 3.41624, 3.48107, 3.54081, 3.59644, 3.64838, 3.69705, 3.74284 },
	{ 1, 1, 1.16014, 1.71573, 2.07746, 2.34192, 2.54856, 2.71717, 2.85898, 2.981  , 3.08781, 3.18262, 3.26775, 3.34486, 3.41529, 3.48016, 3.53993, 3.59559, 3.64775, 3.69625, 3.74205 },
	{ 1, 1, 1.15729, 1.71363, 2.07577, 2.34048, 2.54728, 2.716  , 2.85791, 2.98   , 3.08688, 3.18174, 3.2669 , 3.34406, 3.41452, 3.47941, 3.53921, 3.59489, 3.64687, 3.69558, 3.74141 },
	{ 1, 1, 1.1549 , 1.71189, 2.07436, 2.33927, 2.54621, 2.71504, 2.85702, 2.97917, 3.0861 , 3.181  , 3.2662 , 3.34339, 3.41387, 3.47879, 3.53861, 3.5943 , 3.6463 , 3.69503, 3.74087 },
	{ 1, 1, 1.15289, 1.71041, 2.07316, 2.33824, 2.5453 , 2.71422, 2.85627, 2.97847, 3.08544, 3.18037, 3.26561, 3.34282, 3.41333, 3.47826, 3.5381 , 3.59381, 3.64582, 3.69457, 3.74041 },
	{ 1, 1, 1.15115, 1.70914, 2.07213, 2.33737, 2.54452, 2.71351, 2.85562, 2.97787, 3.08487, 3.17984, 3.2651 , 3.34233, 3.41286, 3.47781, 3.53766, 3.59339, 3.64541, 3.69417, 3.74002 },
	{ 1, 1, 1.14965, 1.70804, 2.07125, 2.33661, 2.54385, 2.7129 , 2.85506, 2.97735, 3.08438, 3.17938, 3.26465, 3.34191, 3.41245, 3.47742, 3.53728, 3.59302, 3.4505 , 3.69382, 3.73969 },
	{ 1, 1, 1.14833, 1.70708, 2.07047, 2.33594, 2.54326, 2.71237, 2.85457, 2.97689, 3.08395, 3.17897, 3.26427, 3.34154, 3.4121 , 3.47707, 3.53695, 3.5927 , 3.64474, 3.69351, 3.73939 },
	{ 1, 1, 1.14717, 1.70623, 2.06978, 2.33535, 2.54274, 2.7119 , 2.85413, 2.9749 , 3.08358, 3.17681, 3.26393, 3.34121, 3.41178, 3.47677, 3.53666, 3.59242, 3.64447, 3.69325, 3.73913 },
	{ 1, 1, 1.14613, 1.75047, 2.06917, 2.33483, 2.54228, 2.71148, 2.85375, 2.97613, 3.08324, 3.17829, 3.26362, 3.34092, 3.4115 , 3.4765 , 3.5364 , 3.59216, 3.64422, 3.69301, 3.7389 } ,
	{ 1, 1, 1.1452 , 1.7048 , 2.06862, 2.33436, 2.54187, 2.71111, 2.85341, 2.97581, 3.08294, 3.17801, 3.26335, 3.34066, 3.41125, 3.47626, 3.53617, 3.59194, 3.644  , 3.6928 , 3.73869 } ,
	{ 1, 1, 1.14437, 1.70419, 2.06813, 2.33394, 2.54149, 2.71077, 2.8531 , 2.97552, 3.08267, 3.17775, 3.26311, 3.34042, 3.41106, 3.47605, 3.53596, 3.59174, 3.6438 , 3.6926 , 3.7385 } };


CString MinMaxRangeValue(CString a[], int b, double *result)
{
	double max = atof(a[0]);
	double min = atof(a[0]);

	for (int i = 0; i < b; i++)
	{
		if (atof(a[i]) > max)
		{
			max = atof(a[i]);
		}
	}
	for (int i = 0; i < b; i++)
	{
		if (atof(a[i]) < min)
		{
			min = atof(a[i]);
		}
	}
	*result = max - min;
	return "";
}


CString MedianValue(CString a[], int b, double *result)
{
	double d[100] = { 0 };
	for (int i = 0; i < b; i++)
	{
		d[i] = atof(a[i]);
	}
	qsort(d, b, sizeof(double), compare);
	if ((b % 2) == 0)
		*result = (d[b / 2] + d[b / 2 - 1]) / 2;
	else
		*result = d[b / 2];

	return "";
}

int compare(const void *a, const void *b)
{
	double num1 = *(double *)a;
	double num2 = *(double *)b;

	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;
}


//각 모든 Tester별, Sample 별 평균, std 구하기
CString CalculateUnpivotAverageStd(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_average[], ItemValue unpivot_std[])
{
	CString log = "";
	int serialnumber = 0;
	int testernumber = 0;
	int serialtesterindex = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}
	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		if (SCORE2||SCORE3)
			continue;

		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		double value = 0;
		double sum = 0;
		double powsum = 0;
		double stdvalue = 0;
		CString average = "";
		CString std = "";

		for (int i = 0; i < serialnumber; i++)
		{
			for (int j = 0; j < testernumber; j++)
			{
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						unpivot_average[serialtesterindex].serialnumber = unpivot[k].serialnumber;
						unpivot_average[serialtesterindex].tester = unpivot[k].tester;
						unpivot_std[serialtesterindex].serialnumber = unpivot[k].serialnumber;
						unpivot_std[serialtesterindex].tester = unpivot[k].tester;
						value = atof(unpivot[k].value[Itemindex]);
						sum += value;
						powsum += pow(value, 2);
					}
				}
				average.Format("%f", sum / trialmin);
				stdvalue = powsum / trialmin - pow(sum / trialmin, 2);
				if (stdvalue > 0)
					stdvalue = sqrt(stdvalue);
				else
					stdvalue = 0;
				std.Format("%f", stdvalue);
				unpivot_average[serialtesterindex].value[Itemindex] = average;
				unpivot_std[serialtesterindex].value[Itemindex] = std;
				tmp.Format("Serial Number:%s \t Tester:%s \t Average:%s \t Std:%s \n", Serialnumber[i],Tester[j], average, std);
				log += tmp;
				value = 0;
				sum = 0;
				powsum = 0;
				stdvalue = 0;
				average = "";
				std = "";
				serialtesterindex++;
			}
		}
		serialtesterindex = 0;
	}
	return log;
}

//각 모든 Tester별, Sample 별 Median 값 구하기
CString CalculateUnpivotMedian(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_median[])
{
	CString log;
	int serialtesterindex = 0;
	int serialnumber = 0;
	int testernumber = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		if (SCORE2|| SCORE3)
			continue;
		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		CString Medianloader[100] = { "" };
		int trialindex = 0;

		for (int i = 0; i < serialnumber; i++)
		{
			for (int j = 0; j < testernumber; j++)
			{
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						unpivot_median[serialtesterindex].serialnumber = unpivot[k].serialnumber;
						unpivot_median[serialtesterindex].tester = unpivot[k].tester;
						Medianloader[trialindex] = unpivot[k].value[Itemindex];
						trialindex++;
					}
				}
				if (trialindex > 0)
				{
					double result = 0;
					MedianValue(Medianloader, trialindex, &result);
					unpivot_median[serialtesterindex].value[Itemindex].Format("%f", result);
					tmp.Format("Serial Number:%s \t Tester:%s \t Median:%f \n", Serialnumber[i], Tester[j], result);
					log += tmp;
					trialindex = 0;
					serialtesterindex++;
				}
			}
		}
		serialtesterindex = 0;
	}
	return log;
}


//GoldenTester 선정하기
CString SettingGoldenTester(ItemValue unpivot_average[], ItemValue unpivot_std[], ItemValue unpivot_median[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, CString *Goldentester)
{
	CString log = "";
	CString tmp = "";
	CString Item1[MAXSAMPLESIZE] = { "" };
	CString Item2[MAXSAMPLESIZE] = { "" };
	int testernumber = 0;
	int serialnumber = 0;
	int Totalgrade[MAXSAMPLESIZE] = {};
	double Tester_Min_grr_negative[MAXSAMPLESIZE] = { 0 };
	double Tester_Max_grr_positive[MAXSAMPLESIZE] = { 0 };
	int minimum = 0;
	int maximum = 0;

	while (Tester[testernumber] != "")
		testernumber++;
	while (Serialnumber[serialnumber] != "")
		serialnumber++;

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		if (SCORE2||SCORE3)
			continue;
		for (int j = 0; j < testernumber; j++)
		{
			for (int i = 0; i < serialnumber; i++)
			{
				double temp_Min_grr_negative = 0;
				double temp_Max_grr_positive = 0;
				for (int k = 0; k < Datanumber; k++)
				{
					if (Tester[j] == unpivot_average[k].tester && Serialnumber[i] == unpivot_average[k].serialnumber)
					{
						temp_Min_grr_negative += atof(unpivot_average[k].value[Itemindex]);
						temp_Max_grr_positive += atof(unpivot_average[k].value[Itemindex]);
					}
					if (Tester[j] == unpivot_std[k].tester && Serialnumber[i] == unpivot_std[k].serialnumber)
					{
						temp_Min_grr_negative -= 3 * atof(unpivot_std[k].value[Itemindex]);
						temp_Max_grr_positive += 3 * atof(unpivot_std[k].value[Itemindex]);
					}
					if (Tester[j] == unpivot_median[k].tester && Serialnumber[i] == unpivot_median[k].serialnumber)
					{
						temp_Min_grr_negative -= atof(unpivot_median[k].value[Itemindex]);
						temp_Max_grr_positive -= atof(unpivot_median[k].value[Itemindex]);
					}
				}
				double MIN = ((atof(Spec[0].LSL[Itemindex]) - atof(Spec[0].USL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]));
				double MAX = ((atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]));
				temp_Min_grr_negative -= MIN;
				temp_Max_grr_positive -= MAX;
				if (Tester_Min_grr_negative[j] == 0 && Tester_Max_grr_positive[j] == 0)
				{
					Tester_Min_grr_negative[j] = temp_Min_grr_negative;
					Tester_Max_grr_positive[j] = temp_Max_grr_positive;
				}
				if (temp_Min_grr_negative < Tester_Min_grr_negative[j])
				{
					Tester_Min_grr_negative[j] = temp_Min_grr_negative;
					Item1[j] = Spec[0].itemname[Itemindex];
				}
				if (temp_Max_grr_positive > Tester_Max_grr_positive[j])
				{
					Tester_Max_grr_positive[j] = temp_Max_grr_positive;
					Item2[j] = Spec[0].itemname[Itemindex];
				}
			}
		}
	}

	tmp = "";
	tmp.Format("[Golden Tester Total Score] \n");
	log += tmp;
	for (int j = 0; j < testernumber; j++)
	{
		tmp = "";
		tmp.Format("[Tester:%s] \nSelf_Min_grr_negative:%f (%s) \nSelf_Max_grr_positive:%f (%s) \n", Tester[j], Tester_Min_grr_negative[j], Item1[j], Tester_Max_grr_positive[j], Item2[j]);
		log += tmp;
	}

	for (int j = 0; j < testernumber; j++)
	{
		int k = j + 1;
		while (k < testernumber)
		{
			if (Tester_Min_grr_negative[j] < Tester_Min_grr_negative[k])
				Totalgrade[j] += 1;
			else if (Tester_Min_grr_negative[j] > Tester_Min_grr_negative[k])
				Totalgrade[k] += 1;
			if (Tester_Max_grr_positive[j] > Tester_Max_grr_positive[k])
				Totalgrade[j] += 1;
			else if (Tester_Max_grr_positive[j] < Tester_Max_grr_positive[k])
				Totalgrade[k] += 1;
			k++;
		}
	}

	minimum = Totalgrade[0];

	CString goldentester = "";
	for (int j = 0; j < testernumber; j++)
	{
		if (Totalgrade[j] <= minimum)
		{
			minimum = Totalgrade[j];
			goldentester = Tester[j];
		}
	}
	*Goldentester = goldentester;
	return log;
}

//Golden Tester Median 값 구하기
CString CalculateGoldenMedian(ItemValue unpivot_median[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, CString goldentester, ItemValue unpivot_median_golden[])
{
	CString log;
	int serialtesterindex = 0;
	int serialnumber = 0;
	int testernumber = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	int serialtesternumber = serialnumber * testernumber;

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		if (SCORE2||SCORE3)
			continue;
		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		for (int k = 0; k < Datanumber; k++)
		{
			if (unpivot_median[k].tester == goldentester)
			{
				unpivot_median_golden[serialtesterindex].serialnumber = unpivot_median[k].serialnumber;
				unpivot_median_golden[serialtesterindex].tester = unpivot_median[k].tester;
				unpivot_median_golden[serialtesterindex].value[Itemindex] = unpivot_median[k].value[Itemindex];
				tmp.Format("Serial Number:%s \t Tester:%s \t Golden Median:%s \n", unpivot_median_golden[serialtesterindex].serialnumber, unpivot_median_golden[serialtesterindex].tester, unpivot_median_golden[serialtesterindex].value[Itemindex]);
				log += tmp;
				serialtesterindex++;
			}
		}
		serialtesterindex = 0;
	}
	return log;
}

// Min 값 구하기
CString CalculateUnpivotMin(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin,  ItemValue unpivot_min[])
{
	CString log;
	int serialtesterindex = 0;
	int serialnumber = 0;
	int testernumber = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		int trialindex = 0;

		for (int i = 0; i < serialnumber; i++)
		{
			for (int j = 0; j < testernumber; j++)
			{
				BOOL First = TRUE;
				double minimum = 0;
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						if (First == TRUE)
						{
							minimum = atof(unpivot[k].value[Itemindex]);
							First = FALSE;
						}
						else if(minimum > atof(unpivot[k].value[Itemindex]))
							minimum = atof(unpivot[k].value[Itemindex]);
						trialindex++;
					}
				}
				if (trialindex > 0)
				{
					unpivot_min[serialtesterindex].serialnumber = Serialnumber[i];
					unpivot_min[serialtesterindex].tester = Tester[j];
					unpivot_min[serialtesterindex].value[Itemindex].Format("%f", minimum);
					tmp.Format("Serial Number:%s \t Tester:%s \t Min:%f \n", Serialnumber[i], Tester[j], minimum);
					log += tmp;
					trialindex = 0;
					serialtesterindex++;
				}
			}
		}
		serialtesterindex = 0;
	}
	return log;
}

//Max 값 구하기
CString CalculateUnpivotMax(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_max[])
{
	CString log;
	int serialtesterindex = 0;
	int serialnumber = 0;
	int testernumber = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		int trialindex = 0;

		for (int i = 0; i < serialnumber; i++)
		{
			for (int j = 0; j < testernumber; j++)
			{
				BOOL First = TRUE;
				double maximum = 0;
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						if (First == TRUE)
						{
							maximum = atof(unpivot[k].value[Itemindex]);
							First = FALSE;
						}
						else if (maximum < atof(unpivot[k].value[Itemindex]))
							maximum = atof(unpivot[k].value[Itemindex]);
						trialindex++;
					}
				}
				if (trialindex > 0)
				{
					unpivot_max[serialtesterindex].serialnumber = Serialnumber[i];
					unpivot_max[serialtesterindex].tester = Tester[j];
					unpivot_max[serialtesterindex].value[Itemindex].Format("%f", maximum);
					tmp.Format("Serial Number:%s \t Tester:%s \t Min:%f \n", Serialnumber[i], Tester[j], maximum);
					log += tmp;
					trialindex = 0;
					serialtesterindex++;
				}
			}
		}
		serialtesterindex = 0;
	}
	return log;
}


//min_grr_negatve, max_grr_positive 계산하기
CString CalculateGoldenGRR(ItemValue unpivot_average[], ItemValue unpivot_std[], ItemValue unpivot_median_golden[], SpecValue Spec[], CString Serialnumber[], CString Tester[], CString goldentester, int *serialtesterindex, ItemValue unpivot_min_grr_negative[], ItemValue unpivot_max_grr_positive[])
{
	CString log = "";
	int serialnumber = 0;
	int testernumber = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	int serialtesternumber = serialnumber * testernumber;

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		if (SCORE2||SCORE3)
			continue;
		CString tmp = "";
		tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
		log += tmp;
		*serialtesterindex = 0;
		double min_grr_negative = 0;
		double max_grr_positive = 0;
		for(int i=0; i<serialnumber; i++)
		{
			for (int k = 0; k < serialtesternumber; k++)
			{
				if (unpivot_average[k].serialnumber == unpivot_median_golden[i].serialnumber)
				{
					unpivot_min_grr_negative[*serialtesterindex].serialnumber = unpivot_average[k].serialnumber;
					unpivot_min_grr_negative[*serialtesterindex].tester = unpivot_average[k].tester;
					unpivot_max_grr_positive[*serialtesterindex].serialnumber = unpivot_average[k].serialnumber;
					unpivot_max_grr_positive[*serialtesterindex].tester = unpivot_average[k].tester;
					min_grr_negative = atof(unpivot_average[k].value[Itemindex]) - 3 * atof(unpivot_std[k].value[Itemindex]) - atof(unpivot_median_golden[i].value[Itemindex]);
					max_grr_positive = atof(unpivot_average[k].value[Itemindex]) + 3 * atof(unpivot_std[k].value[Itemindex]) - atof(unpivot_median_golden[i].value[Itemindex]);
					unpivot_min_grr_negative[*serialtesterindex].value[Itemindex].Format("%f", min_grr_negative);
					unpivot_max_grr_positive[*serialtesterindex].value[Itemindex].Format("%f", max_grr_positive);
					tmp.Format("Serial Number:%s \t Tester:%s \t Min_GRR_Neagative:%s \n", unpivot_min_grr_negative[*serialtesterindex].serialnumber, unpivot_min_grr_negative[*serialtesterindex].tester, unpivot_min_grr_negative[*serialtesterindex].value[Itemindex]);
					log += tmp;
					tmp.Format("Serial Number:%s \t Tester:%s \t Max_GRR_Positive:%s \n", unpivot_max_grr_positive[*serialtesterindex].serialnumber, unpivot_max_grr_positive[*serialtesterindex].tester, unpivot_max_grr_positive[*serialtesterindex].value[Itemindex]);
					log += tmp;
					*serialtesterindex = *serialtesterindex + 1;
				}
			}
		}
	}
	return log;
}

CString GoldenGRRComparing( ItemValue unpivot_max_grr_positive[], ItemValue unpivot_min_grr_negative[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString *TotalFailItem)
{
	CString log = "";
	int serialnumber = 0;
	int testernumber = 0;
	double Max_LIMIT[MAXITEMSIZE] = {};
	double Min_LIMIT[MAXITEMSIZE] = {};

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	for (int i = 0; i < serialnumber; i++)
	{
		for (int j = 0; j < testernumber; j++)
		{
			CString TRUEFALSE = "";
			CString  PASS= "NA";
			CString FailItem = "";

			for (int k = 0; k < serialtesternumber; k++)
			{
				for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
				{
					CString tmp = "";
					if (SCORE2|| SCORE3)
						continue;

					if (unpivot_min_grr_negative[k].serialnumber == Serialnumber[i] && unpivot_min_grr_negative[k].tester == Tester[j])
					{
						GRRpassfail[i + 1][0] = Serialnumber[i];
						GRRpassfail[0][j + 1] = Tester[j];
						Min_LIMIT[Itemindex] = (atof(Spec[0].LSL[Itemindex]) - atof(Spec[0].USL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]);
						if (atof(unpivot_min_grr_negative[k].value[Itemindex]) > Min_LIMIT[Itemindex])
						{
							if (PASS == "FAIL")
								PASS = "FAIL";
							else
								PASS = "PASS";
							TRUEFALSE = "TRUE";
						}
						else{
							PASS = "FAIL";
							TRUEFALSE = "FALSE";
							FailItem = Spec[0].itemname[Itemindex] + ", ";
						}
						tmp.Format("Serial Number:%s \t Tester:%s \t Item Name:%s \t Min_GRR_Negative:%s\t>\tMin_LIMIT:%f \t %s \n", Serialnumber[i], Tester[j], Spec[0].itemname[Itemindex], unpivot_min_grr_negative[k].value[Itemindex], Min_LIMIT[Itemindex], TRUEFALSE);
						log += tmp;
					}
					if (unpivot_max_grr_positive[k].serialnumber == Serialnumber[i] && unpivot_max_grr_positive[k].tester == Tester[j])
					{
						GRRpassfail[i + 1][0] = Serialnumber[i];
						GRRpassfail[0][j + 1] = Tester[j];
						Max_LIMIT[Itemindex] = (atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]);
						if (atof(unpivot_max_grr_positive[k].value[Itemindex]) < Max_LIMIT[Itemindex])
						{
							if (PASS == "FAIL")
								PASS = "FAIL";
							else
								PASS = "PASS";
							TRUEFALSE = "TRUE";
						}
						else
						{
							PASS = "FAIL";
							TRUEFALSE = "FALSE";
							FailItem = Tester[j] + Spec[0].itemname[Itemindex] + ", ";
						}
						tmp.Format("Serial Number:%s \t Tester:%s \t Item Name:%s \t Max_GRR_Positive:%s\t<\tMax_LIMIT:%f \t %s \n", Serialnumber[i], Tester[j], Spec[0].itemname[Itemindex], unpivot_max_grr_positive[k].value[Itemindex], Max_LIMIT[Itemindex], TRUEFALSE);
						log += tmp;
					}
					
					*TotalFailItem += FailItem;
				}
			}
			if (PASS == "PASS")
				GRRpassfail[i + 1][j + 1] = "PASS";
			else if(PASS=="FAIL")
				GRRpassfail[i + 1][j + 1] = "FAIL";
			else
				GRRpassfail[i + 1][j + 1] = "NA";
		}
	}
	GRRpassfail[0][0] = "Reproducibility";
	return log;
}

CString S2GoldenGRRComparing(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString *TotalFailItem)
{
	CString log = "";
	int serialnumber = 0;
	int testernumber = 0;
	log += "Score 2 Comparing \n";
	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	for (int i = 0; i < serialnumber; i++)
	{
		for (int j = 0; j < testernumber; j++)
		{
			CString TRUEFALSE = "";
			CString  PASS = "NA";
			CString FailItem = "";

			for (int k = 0; k < serialtesternumber; k++)
			{
				for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
				{
					CString tmp = "";
					if (SCORE2)
					{
						if (unpivot[k].serialnumber == Serialnumber[i] && unpivot[k].tester == Tester[j])
						{
							GRRpassfail[i + 1][0] = Serialnumber[i];
							GRRpassfail[0][j + 1] = Tester[j];

							//PASS일 경우
							if (atof(unpivot[k].value[Itemindex]) >= atof(Spec[0].LSL[Itemindex]) && atof(unpivot[k].value[Itemindex]) <= atof(Spec[0].USL[Itemindex]))
							{
								//이미 FAIL이면
								if (PASS == "FAIL")
									PASS = "FAIL";
								else
									PASS = "PASS";
								TRUEFALSE = "TRUE";
							}
							//FAIL일 경우
							else
							{
								PASS = "FAIL";
								TRUEFALSE = "FALSE";
								FailItem = Tester[j] + Spec[0].itemname[Itemindex] + ", ";
							}
							tmp.Format("Serial Number:%s \t Tester:%s \t Item Name:%s \t Value:%s \t USL: %s \t LSL: %s \t %s \n", Serialnumber[i], Tester[j], Spec[0].itemname[Itemindex], unpivot[k].value[Itemindex], Spec[0].USL[Itemindex], Spec[0].LSL[Itemindex], TRUEFALSE);
							log += tmp;
						}
					}
					else
						continue;
					
					*TotalFailItem += FailItem;
				}
			}
			if (PASS == "PASS")
				GRRpassfail[i + 1][j + 1] = "PASS";
			else if(PASS == "FAIL")
				GRRpassfail[i + 1][j + 1] = "FAIL";
			else
				GRRpassfail[i + 1][j + 1] = "NA";
		}
	}
	return log;
}

CString S3GoldenGRRComparing(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString *TotalFailItem)
{
	CString log = "";
	int serialnumber = 0;
	int testernumber = 0;
	log += "Score 3 Comparing \n";
	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}
	while (Tester[testernumber] != "")
	{
		testernumber++;
	}
	for (int j = 0; j < testernumber; j++)
	{
		CString tmp = "";
		CString  PASS = "NA";
		CString TRUEFALSE = "";
		CString FailItem = "";
		
		for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
		{
			if (SCORE3)
			{	
				BOOL First = true;
				double min = 0;
				double max = 0;
				CString strmin = "";
				CString strmax = "";
					for (int k = 0; k < serialtesternumber; k++)
					{
						if (unpivot[k].tester == Tester[j])
						{
							if (First == true)
							{
								min = atof(unpivot[k].value[Itemindex]);
								max = atof(unpivot[k].value[Itemindex]);
								First = false;
							}
							else
							{
								if(min > atof(unpivot[k].value[Itemindex]))
									min = atof(unpivot[k].value[Itemindex]);
								if(max < atof(unpivot[k].value[Itemindex]))
									max = atof(unpivot[k].value[Itemindex]);
							}
						}
					}
					min = floor(min * 100) / 100;
					max = floor(max * 100) / 100;
					if (min < atof(Spec[0].LSL[Itemindex]) && max < atof(Spec[0].USL[Itemindex]))
					{
						if (PASS == "FAIL")
							PASS = "FAIL";
						else
							PASS = "PASS";
						TRUEFALSE = "TRUE";
					}
					else
					{
						PASS = "FAIL";
						TRUEFALSE = "FALSE";
						FailItem += Tester[j] + Spec[0].itemname[Itemindex] + ", ";
					}
					strmin.Format("%.2f", min);
					strmax.Format("%.2f", max);
					tmp.Format("Tester:%s \t Item Name:%s \t Max:%s <= USL:%s \t Min:%s <= LSL:%s \t %s \n", Tester[j], Spec[0].itemname[Itemindex], strmax, Spec[0].USL[Itemindex], strmin, Spec[0].LSL[Itemindex], TRUEFALSE);
					log += tmp;
			}
			else
				continue;
		}
		if (PASS == "PASS")
		{
			for (int i = 0; i < serialnumber; i++)
				GRRpassfail[i + 1][j + 1] = "PASS";
		}
		else if(PASS == "FAIL")
		{
			for (int i = 0; i < serialnumber; i++)
				GRRpassfail[i + 1][j + 1] = "FAIL";
		}
		else
		{
			for (int i = 0; i < serialnumber; i++)
				GRRpassfail[i + 1][j + 1] = "NA";
		}
		
		*TotalFailItem += FailItem;
	}
	return log;
}

CString CalculatingPercentGRR(int Mode, ItemValue unpivot[], double input1, double input2, double input3, int Itemindex, int Datanumber, CString Serialnumber[], CString Tester[], int trialmin, double *outputValue)
{
	CString log = "";
	CString tmp = "";
	CString RangeMinMaxloader[100] = {};
	CString MinMaxloader[100] = {};
	int serialnumber = 0;
	int testernumber = 0;
	int trialindex = 0;
	double result = 0;

	while (Serialnumber[serialnumber] != "")
	{
		serialnumber++;
	}

	while (Tester[testernumber] != "")
	{
		testernumber++;
	}

	switch(Mode)
	{
	case MODERANGEAVERAGE:
		*outputValue = 0;
		for (int i = 0; i < serialnumber; i++)
		{
			for (int j = 0; j < testernumber; j++)
			{
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						RangeMinMaxloader[trialindex] = unpivot[k].value[Itemindex];
						trialindex++;
					}
				}
				if (trialindex > 0)
				{
					MinMaxRangeValue(RangeMinMaxloader, trialindex, &result);
					tmp.Format("Serial Number:%s \t Tester:%s \t Range:%f  \n", Serialnumber[i], Tester[j], result);
					log += tmp;
					*outputValue += result;
					trialindex = 0;
				}
			}
		}
		*outputValue= *outputValue / (testernumber*serialnumber);
		tmp.Format("Range Average:%f \n", *outputValue);
		log += tmp;
		break;

	case MODEXDIFF:
		for (int j = 0; j < testernumber; j++)
		{
			*outputValue = 0;
			for (int i = 0; i < serialnumber; i++)
			{
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
					{
						*outputValue += atof(unpivot[k].value[Itemindex]);
					}
				}
			}
			*outputValue = *outputValue / (serialnumber * trialmin);
			tmp.Format("Tester:%s \t X_Average:%f \n", Tester[j], *outputValue);
			log += tmp;
			MinMaxloader[j].Format("%f", *outputValue);
		}
		MinMaxRangeValue(MinMaxloader, testernumber, &result);
		tmp.Format("X_Diff:%f \n",  result);
		log += tmp;
		*outputValue = result;
		break;

	case MODERPART:
		for (int i = 0; i < serialnumber; i++)
		{
			*outputValue = 0;
			for (int j = 0; j < testernumber; j++)
			{
				for (int k = 0; k < Datanumber; k++)
				{
					if (Serialnumber[i] == unpivot[k].serialnumber && Tester[j] == unpivot[k].tester && unpivot[k].trial <= trialmin)
						*outputValue += atof(unpivot[k].value[Itemindex]);
				}
			}
			*outputValue = *outputValue / (testernumber * trialmin);
			tmp.Format("Serial Number:%s \t R_Average:%f \n", Serialnumber[i], *outputValue);
			log += tmp;
			MinMaxloader[i].Format("%f", *outputValue);
		}
		MinMaxRangeValue(MinMaxloader, serialnumber, &result);
		tmp.Format("R_Part:%f \n", result);
		log += tmp;
		*outputValue = result;
		break;
	case MODEK1:
		*outputValue = 1 / d1[trialmin];
		tmp.Format("K1:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEK2:
		*outputValue = 1 / d2[1][testernumber];
		tmp.Format("K2:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEK3:
		*outputValue = 1 / d2[1][serialnumber];
		tmp.Format("K3:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEEV:
		*outputValue = input1 * (input2);
		tmp.Format("EV:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEAV:
		*outputValue = pow(input1 * (input2), 2) - (pow(input3, 2) / (serialnumber*trialmin));
		if (*outputValue < 0)
			*outputValue = 0;
		else
			*outputValue = sqrt(*outputValue);
		tmp.Format("AV:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEGRR:
		*outputValue = sqrt(pow(input1, 2) + pow(input2, 2));
		tmp.Format("GRR:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEPV:
		*outputValue = input1 * (input2);
		tmp.Format("PV:%f \n", *outputValue);
		log += tmp;
		break;
	case MODETV:
		*outputValue = sqrt(pow(input1, 2) + pow(input2, 2));
		tmp.Format("TV:%f \n", *outputValue);
		log += tmp;
		break;
	case MODEPERCENTEV:
		*outputValue = input1 * 100 / input2;
		tmp.Format("%%EV:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODEPERCENTAV:
		*outputValue = input1 * 100 / input2;
		tmp.Format("%%AV:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODEPERCENTGRR:
		*outputValue = input1 * 100 / input2;
		tmp.Format("%%GRR:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODEPERCENTPT:
		*outputValue = input1 * 100 / input2;
		tmp.Format("%%P/T:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODEPERCENTPV:
		*outputValue = input1 * 100 / input2;
		tmp.Format("%%PV:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODENDC:
		*outputValue = input1 * 1.41 / input2;
		tmp.Format("NDC:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODESCORE2:
		for (int j = 0; j < testernumber; j++)
		{
			for (int k = 0; k < Datanumber; k++)
			{
				if((unpivot[k].tester == Tester[j]))
				{
					if ((atof(unpivot[k].value[Itemindex]) >= input2) && (atof(unpivot[k].value[Itemindex]) <= input1))
						*outputValue = *outputValue + 0;
					else
						*outputValue = *outputValue + 1;
				}
			}
		}
		tmp.Format("Score2Value:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODESCORE3_MIN:
		for (int j = 0; j < testernumber; j++)
		{
			BOOL First = true;
			for (int k = 0; k < Datanumber; k++)
			{
				if ((unpivot[k].tester == Tester[j]))
				{
					if (First == true)
					{
						*outputValue = atof(unpivot[k].value[Itemindex]);
						First = false;
					}
					else if (*outputValue > atof(unpivot[k].value[Itemindex]))
						*outputValue = atof(unpivot[k].value[Itemindex]);
				}
			}
		}
		*outputValue = floor(*outputValue * 100) / 100;
		tmp.Format("Score3_Min:%.2f \n", *outputValue);
		log += tmp;
		break;
	case MODESCORE3_MAX:
		for (int j = 0; j < testernumber; j++)
		{
			BOOL First = true;
			for (int k = 0; k < Datanumber; k++)
			{
				if ((unpivot[k].tester == Tester[j]))
				{
					if (First == true)
					{
						*outputValue = atof(unpivot[k].value[Itemindex]);
						First = false;
					}
					else if (*outputValue < atof(unpivot[k].value[Itemindex]))
						*outputValue = atof(unpivot[k].value[Itemindex]);
				}
			}
		}
		*outputValue = floor(*outputValue * 100) / 100;
		tmp.Format("Score3_Max:%.2f \n", *outputValue);
		log += tmp;
		break;

	}
	return log;
}

CString GetValuefromCSV(CString Itemname, CString Path, CString Serialnumber)
{
	CStdioFile FileRead;
	CString ReadSpecPath = Path;
	CString tmp;
	CString str;
	CString result;
	int commanumber = 0;

	if (!FileRead.Open(ReadSpecPath, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox(ReadSpecPath + "\nFile is damaged");
	}
	else
	{
		while (FileRead.ReadString(tmp))
		{
			if (tmp.Find(Itemname) != -1)
			{
				str = tmp.Left(tmp.Find(Itemname));
				commanumber = str.Remove(',');
			}
			else if (tmp.Left(tmp.Find(",")) == Serialnumber)
			{
				str = tmp;
				for (int j = 0; j < commanumber; j++)
					str = str.Mid(str.Find(",") + 1);
				if(str.Find(",") != -1)
					result = str.Left(str.Find(","));
				else
					result = str;
			}
			else
				continue;

		}
		FileRead.Close();
	}
	return result;
}

