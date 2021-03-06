#pragma once
#include <iostream>
#include <cmath>

#include <QDir>
#include <QFile>
#include <QVector>
#include <QIODevice>
#include <QTextStream>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
struct CountInfo																		// 長寬的資料
{
	uint XCount = 0;
	uint YCount = 0;
	uint ZCount = 0;

	int XDir;
	int YDir;
	int ZDir;

	int offset;																			// 假設 LockDataInfo 裡面有很多個物件，有一個
};
struct ModelInfo																		// 模型相關的資料
{
	int PartNumber;																		// Part Number
	QString PartName;																	// Part 的名稱 (Ex: roof, base)
};
struct SplitModelInfo
{
	int OrgModelIndex;																	// 對應原本 Model 的 index		(roof1, roof2, roof3, base1, base2, base3, base4)
	int StartModelIndex;																// 對應到 Split Model 的 Index	(roof(0) ,base(3))
	int SplitCount;																		// 有幾個						(roof(3) ,base(4))

	int PartNumber;																		// Part Number
	QString PartName;																	// Part 的名稱

	QVector<CountInfo> LockDataInfo;													// 存後面切曾需要的資訊
};

typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;
using namespace std;

class InterLockClass
{
public:
	InterLockClass(char *);
	~InterLockClass();

	void								SplitInSmallSize();								// 將東西切成小塊的
	void								GenerateLock();									// 產生卡榫
	void								SaveAllModel();									// 儲存 Model
private:
	MyMesh *							CombineTwoMeshToOne(MyMesh *, MyMesh *);		// 將兩個模型合成一個

	float								GetNextValue(float, float, float);				// 會回傳給你下一次要做的值
	uint								CountSize(float, float);						// 給 End & Start 算出總共有幾個會有幾個
	MyMesh::Point						CountCenterPos(MyMesh *);						// 算中心點座標
	MyMesh::FaceHandle					FindFaceByDir(MyMesh *, MyMesh::Point, char, int,
												QVector<MyMesh::Point> &,
												MyMesh::Point &);						// 給物體的中心點 & 方向，找出哪一個面 & 那面的中心點
	float								CountDistance(MyMesh::Point, MyMesh::Point);	// 算出兩點之間的距離
	float								CountArea(QVector<MyMesh::Point>);				// 給四個點進去，算面積

	bool								CheckIsTheSamePoint(MyMesh::Point, MyMesh::Point);
	bool								CheckIsCombined(int);							// 判斷是不是已經 Combine 過後的結果，如果是的話，就不用儲存

	QVector<int>						CombineIndex;									// 要略過的 Index
	QVector<MyMesh *>					ModelsArray;									// 存 Model 的 Array
	QVector<ModelInfo *>				InfoArray;										// 存 Info 的 Array

	QVector<MyMesh *>					SplitModelsArray;								// 分開的 Model 的 Array
	QVector<MyMesh::Point>				SplitModelCenterPosArray;						// 分開的 Model 的 Array 的中心點
	QVector<SplitModelInfo *>			SplitInfoArray;									// 分開的 Info 的 Array 

	QString								FilePathLocation;								// 要記錄 info 的目錄位置，這樣拿其他 Model 的時候要加上這個位置

	const QString						outputFileEnd = ".obj";							// 輸出種類
	const int							SplitSize = 4;									// 每一個 Unit 的大小
	const int							LockHeight = 1;									// 卡榫高度
	const float							RoofLockYOffset = 0.5;							// Roof 的 Y 位移量
	const float							offset = 0.2;									// 卡榫位移量
	const int							MinSize = 1;									// 洞最小的長寬，至少要1個單位
};

