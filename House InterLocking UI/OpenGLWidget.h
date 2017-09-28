#pragma once
#include <iostream>

#include <QtMath>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLWidget>

#define PI 3.14159265

using namespace std;

struct NormalParams
{
	//////////////////////////////////////////////////////////////////////////
	// 記住!! 是向外擴張!!
	//////////////////////////////////////////////////////////////////////////
	int XLength;													// X 長度
	int YLength;													// Y 長度
	int ZLength;													// Z 長度

	QVector3D TranslatePoint;
};
struct DoorParams
{
	float ratio;

	int DoorWidth;
	int DoorHeight;
};
struct SingleWindowParams
{
	float RatioWidth;
	float RatioHeight;

	int WindowWidth;
	int WindowHeight;
};
struct MultiWindowParams
{
	SingleWindowParams windowA;
	SingleWindowParams windowB;
};
struct TriangleParams
{
	float ratioX;

	bool IsXY;
};
/*struct CrossGableParams
{

};*/

struct NodeInfo
{
	QString name;													// 物體名稱

	// 參數類
	NormalParams			nParams;
	SingleWindowParams		singleWindowParams;
	DoorParams				doorParams;
	MultiWindowParams		multiWindowParams;
	TriangleParams			triangleParams;

	QVector<NodeInfo *> childNode;									// 小孩的 Node
};
struct HouseTree
{
	NodeInfo *Root;
};
class OpenGLWidget: public QOpenGLWidget
{
public:
	OpenGLWidget(QWidget *);
	~OpenGLWidget();

	void initializeGL();
	void paintGL();
	

	// 滑鼠事件
	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

private:
	//////////////////////////////////////////////////////////////////////////
	// 滑鼠相關
	//////////////////////////////////////////////////////////////////////////
	int AngleXZ = 0;
	int LastAngleXZ = 0;
	bool IsLeftButtonClick = false;
	QPoint lastMousePosition;


	HouseTree *info;
	
	QVector<QVector3D> TransformParamToModel(NodeInfo *);			// 將參數改成模型的點

	void InitModelParams();											// 初始化模型參數

	void SetPMVMatrix();											// 設定矩陣
	void DrawHouseView();											// 畫出整棟房子
	void DrawBorder();												// 劃出畫面的邊界
	void DrawModelByName(QString, QVector<QVector3D>);				// 根據物體的名稱，還有點，來畫面

	float GetNextValue(float, float);
};

