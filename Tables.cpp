#include "Tables.h"
#include "PeriodicTable.h"
#include "NewComposite.h"
#include "LayMaterials.h"
Tables::Tables(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.matFile_pb, SIGNAL(clicked()), this, SLOT(OnMatFile()));
	connect(ui.openPRJ_pb, SIGNAL(clicked()), this, SLOT(OnOpenPRJ()));
	connect(ui.editFile_pb, SIGNAL(clicked()), this, SLOT(OnEditFile()));
	connect(ui.calcDist_pb, SIGNAL(clicked()), this, SLOT(OnCalcDist()));

}

/////////////////////////////////////////////////////////////////////////////
// �������� � �������������� ���������
//
void Tables::OnMatFile()
{
	//PeriodicTable dlg;
	//dlg.exec();
	NewComposite dlg;
	dlg.exec();
}

/////////////////////////////////////////////////////////////////////////////
// ������ � �������� ����
//
void Tables::OnOpenPRJ() 
{
	LayMaterials dlg(this);
	dlg.exec();
	openPRJ = dlg.saved;
	if (openPRJ)
	{
		ui.editFile_pb->setEnabled(true);
		ui.calcDist_pb->setEnabled(true);
	}
} 

/////////////////////////////////////////////////////////////////////////////
// ������������� ���� ��������
//
void Tables::OnEditFile()
{
	LayMaterials dlg(p.proj);
	dlg.exec();
}

/////////////////////////////////////////////////////////////////////////////
// ���������� �������������
//
void Tables::OnCalcDist()
{
	calcDist = true; // ������� ������������� ���������� �������
	if (calcDist)
		ui.getDist_pb->setEnabled(true);
}

/////////////////////////////////////////////////////////////////////////////
// �������� ������������� ��� ����
//
void Tables::OnGetDist()
{
	//
}