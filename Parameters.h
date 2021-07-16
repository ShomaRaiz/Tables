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
	QString fParameterIni; // Имя файла с параметрами (*.ini)
	xrbParam param;
	xrbParam param_init; // Исходные значения в файле  с параметрами (*.ini)
	QMap<int,int> enMap;
public:
	void InitData(); // загрузка исходных данных
	void readParametersIni();
	void UpdateData(bool a); // Обмен данными с интерфейсом (true - С интерфейса, false - НА интерфейс)
	bool EditedCheck(); // Редактировался файл или нет
	void closeEvent(QCloseEvent* event);
private slots:
	void OnSave(); // Сохраняем файл .ini
	void OnSaveAs(); 
	void OnOpen(); // Открываем файл с параметрами (*.ini)
	void OnExit(); // Выход
private:
	Ui::Parameters ui;
};

#endif