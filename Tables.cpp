#include <pybind11/pybind11.h>  // ��������� ������, ����� ������ ������� ����!

#include "QDir.h"

#include "Tables.h"
#include "Python_bindings.h"
#include "PeriodicTable.h"
#include "NewComposite.h"
#include "LayMaterials.h"
#include "Parameters.h"



Tables::Tables(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.matFile_pb, SIGNAL(clicked()), this, SLOT(OnMatFile()));
	connect(ui.openPRJ_pb, SIGNAL(clicked()), this, SLOT(OnOpenPRJ()));
	connect(ui.editFile_pb, SIGNAL(clicked()), this, SLOT(OnEditFile()));
	connect(ui.calcDist_pb, SIGNAL(clicked()), this, SLOT(OnCalcDist()));
	connect(ui.action_6, SIGNAL(triggered()), this, SLOT(OnParameters()));
	connect(ui.action_4, SIGNAL(triggered()), this, SLOT(OnExit()));
	connect(ui.action_5, SIGNAL(triggered()), this, SLOT(OnGraphs()));


	init_paths();
}


void Tables::init_paths() {
	QString appPath = qApp->applicationDirPath();
	QDir appDir(appPath);
	appDir.cdUp();
	appPath = appDir.path();
	p.execDir = appPath;
	p.mat = appPath + "/.." + "/share/scripts/mat_files";
	p.par = appPath + +"/.." "//share/scripts/xrb_parameters.ini";
	p.home = appPath + +"/.." "/share/scripts";

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
	Python python = Python();
	python.calcDistributions(p);
	calcDist = true; // ������� ������������� ���������� �������
	if (calcDist)
		ui.getDist_pb->setEnabled(true);
}

/////////////////////////////////////////////////////////////////////////////
// �������� ������������� ��� ����
//
void Tables::OnGetDist()
{
	Python python = Python();
	python.getDistributions(p);

}

/////////////////////////////////////////////////////////////////////////////
// ����� ���� "���������"
//
void Tables::OnParameters()
{
	Parameters dlg(this);
	dlg.exec();
}

/////////////////////////////////////////////////////////////////////////////
// �����
//
void Tables::OnExit()
{
	this->close();
}

/////////////////////////////////////////////////////////////////////////////
// �������
//
void Tables::OnGraphs()
{
	
}