#ifndef PARAMETRES
#define PARAMETRES

#include <QWidget.h>
#include <QDialog>
#include "ui_Parameters.h"


struct xrbParam
{
	int Emin = 0;
	int Emax = 0;
	int En = 0;
	int nG = 0;
	int nG_el = 0;
	int nG_ion = 0;
	int nG_br = 0;
	int nG_br_tet = 0;
	int nG_photo = 0;
	int nG_para = 0;
	int nG_annig = 0;

};
class Parameters : public QDialog, public Ui::Parameters
{
	Q_OBJECT

public:
	Parameters(QWidget *parent = Q_NULLPTR);
	~Parameters();
	QString fParameterIni; // ��� ����� � ����������� (*.ini)
	xrbParam param;
	xrbParam param_init; // �������� �������� � �����  � ����������� (*.ini)
	QMap<int,int> enMap;
public:
	void InitData(); // �������� �������� ������
	void readParametersIni();
	void UpdateData(bool a); // ����� ������� � ����������� (true - � ����������, false - �� ���������)
	bool EditedCheck(); // �������������� ���� ��� ���
	void closeEvent(QCloseEvent* event);
private slots:
	void OnSave(); // ��������� ���� .ini
	void OnSaveAs(); 
	void OnOpen(); // ��������� ���� � ����������� (*.ini)
	void OnExit(); // �����
private:
	Ui::Parameters ui;
};

#endif