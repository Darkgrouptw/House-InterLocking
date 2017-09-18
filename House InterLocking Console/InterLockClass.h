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
/*enum LockType
{
	Concave	= 1,				// �W
	Convex	= 0					// �Y
};*/
struct CountInfo																		// ���e�����
{
	uint XCount = 0;
	uint YCount = 0;
	uint ZCount = 0;

	int XDir;
	int YDir;
	int ZDir;

	int offset;																			// ���] LockDataInfo �̭����ܦh�Ӫ���A���@��
};
struct ModelInfo																		// �ҫ����������
{
	int PartNumber;																		// Part Number
	QString PartName;																	// Part ���W�� (Ex: roof, base)
};
struct SplitModelInfo
{

	int OrgModelIndex;																	// �����쥻 Model �� index		(roof1, roof2, roof3, base1, base2, base3, base4)
	int StartModelIndex;																// ������ Split Model �� Index	(roof(0) ,base(3))
	int SplitCount;																		// ���X��						(roof(3) ,base(4))

	int PartNumber;																		// Part Number
	QString PartName;																	// Part ���W��

	QVector<CountInfo> LockDataInfo;													// �s�᭱�����ݭn����T
};

typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;
using namespace std;

class InterLockClass
{
public:
	InterLockClass(char *);
	~InterLockClass();

	void								SplitInSmallSize();								// �N�F������p����
	void								GenerateLock();									// ���ͥd�g
	void								SaveAllModel();									// �x�s Model
private:
	float								GetNextValue(float, float, float);				// �|�^�ǵ��A�U�@���n������
	uint								CountSize(float, float);						// �� End & Start ��X�`�@���X�ӷ|���X��
	MyMesh::Point						CountCenterPos(MyMesh *);						// �⤤���I�y��
	MyMesh::FaceHandle					FindFaceByDir(MyMesh *, MyMesh::Point, char, int,
												QVector<MyMesh::Point> &,
												MyMesh::Point &);						// �����骺�����I & ��V�A��X���@�ӭ� & �����������I
	float								CountDistance(MyMesh::Point, MyMesh::Point);	// ��X���I�������Z��
	float								CountArea(QVector<MyMesh::Point>);				// ���|���I�i�h�A�⭱�n

	QVector<MyMesh *>					ModelsArray;									// �s Model �� Array
	QVector<ModelInfo *>				InfoArray;										// �s Info �� Array

	QVector<MyMesh *>					SplitModelsArray;								// ���}�� Model �� Array
	QVector<MyMesh::Point>				SplitModelCenterPosArray;						// ���}�� Model �� Array �������I
	QVector<SplitModelInfo *>			SplitInfoArray;									// ���}�� Info �� Array 

	QString								FilePathLocation;								// �n�O�� info ���ؿ���m�A�o�ˮ���L Model ���ɭԭn�[�W�o�Ӧ�m

	const QString						outputFileEnd = ".obj";							// ��X����
	const int							SplitSize = 4;									// �C�@�� Unit ���j�p
	const int							LockHeight = 1;									// �d�g����
	const float							RoofLockYOffset = 0.5;							// Roof �� Y �첾�q
	const float							offset = 0.2;									// �d�g�첾�q
	const int							MinSize = 1;									// �}�̤p�����e�A�ܤ֭n1�ӳ��
};
