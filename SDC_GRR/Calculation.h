#pragma once

#define MAXITEMSIZE 7000
#define MAXITEMLENGTH 100
#define MAXSAMPLESIZE 100
#define MAXDATAQUANTITY 500
#define ITEMSTART 0 //아이템 인덱스로 나중에 돌릴것
#define ERRORSCALE 0.3 //에러스케일, 나중에는 스펙에서 받을것

/*PercentGRR 계산 Switch Define*/
#define MODERANGEAVERAGE	1
#define MODEXDIFF			2
#define MODERPART			3
#define MODEK1				4
#define MODEK2				5
#define MODEK3				6
#define MODEEV				7
#define MODEAV				8
#define MODEGRR				9
#define MODEPV				10
#define MODETV				11
#define MODEPERCENTEV		12
#define MODEPERCENTAV		13
#define MODEPERCENTGRR		14
#define MODEPERCENTPT		15
#define MODEPERCENTPV		16
#define MODENDC				17
#define MODESCORE2			18
#define MODESCORE3_MAX		19
#define MODESCORE3_MIN		20
/*******************************/

/*로그 출력 Mode*/
#define MODEINFORM		1
#define MODEWARNING		2
#define MODERESULT		3
/*******************************/
#define SCORE1 Spec[0].Score[Itemindex] == "1"
#define SCORE2 Spec[0].Score[Itemindex] == "2"
#define SCORE3 Spec[0].Score[Itemindex] == "3"
//#define NOSPEC Spec[0].Score[Itemindex] != "1" || Spec[0].Score[Itemindex] != "2" 
typedef struct _BasicInformation
{
	CString serialnumber;
	CString tester;
	CString time;
	CString errorcode;
	CString proj_name;
	int trial;
}BasicInformation;

typedef struct _itemvalue
{
	CString serialnumber;
	CString tester;
	CString time;
	int trial;
	CString fom;
	CString version;
	CString value[MAXITEMSIZE];
}ItemValue;

typedef struct _Specvalue
{
	CString itemname[MAXITEMSIZE];
	CString fom;
	CString version;
	CString USL[MAXITEMSIZE];
	CString LSL[MAXITEMSIZE];
	int totalitemnumber;
	CString Score[MAXITEMSIZE];
	CString ErrorScale[MAXITEMSIZE];
	CString TolScale[MAXITEMSIZE];
	int commanumber[MAXITEMSIZE];
}SpecValue;


CString MinMaxRangeValue(CString a[], int b, double *result);
CString MedianValue(CString a[], int b, double *result);
int compare(const void *a, const void *b);
CString CalculateUnpivotAverageStd(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_average[], ItemValue unpivot_std[]);
CString CalculateUnpivotMedian(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_median[]);
CString CalculateGoldenMedian(ItemValue unpivot_median[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, CString goldentester, ItemValue unpivot_median_golden[]);
CString CalculateUnpivotMin(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin,  ItemValue unpivot_min[]);
CString CalculateUnpivotMax(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, int trialmin, ItemValue unpivot_max[]);
CString SettingGoldenTester(ItemValue unpivot_average[], ItemValue unpivot_std[], ItemValue unpivot_median[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int Datanumber, CString *Goldentester);
CString CalculateGoldenGRR(ItemValue unpivot_average[], ItemValue unpivot_std[], ItemValue unpivot_median_golden[], SpecValue Spec[], CString Serialnumber[], CString Tester[], CString goldentester, int *serialtesterindex, ItemValue unpivot_min_grr_negative[], ItemValue unpivot_max_grr_positive[]);
CString GoldenGRRComparing(ItemValue unpivot_max_grr_positive[], ItemValue unpivot_min_grr_negative[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString *TotalFailItem);
CString S2GoldenGRRComparing(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString *TotalFailItem);
CString S3GoldenGRRComparing(ItemValue unpivot[], SpecValue Spec[], CString Serialnumber[], CString Tester[], int serialtesternumber, CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE], CString * TotalFailItem);
CString CalculatingPercentGRR(int Mode, ItemValue unpivot[], double input1, double input2, double input3, int Itemindex, int Datanumber, CString Serialnumber[], CString Tester[], int trialmin, double *result);
CString GetValuefromCSV(CString Itemname, CString Path, CString Serialnumber);


