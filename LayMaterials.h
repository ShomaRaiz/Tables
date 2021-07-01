#pragma once

#include <QWidget>
#include <QDialog>

#include "ui_LayMaterials.h"
class Tables;
class LayMaterialsModel : public QAbstractTableModel // ������ ��� ������������� ���������� � ���������� � �������
{
	Q_OBJECT

public:
	LayMaterialsModel(QObject *parent = 0);

	void populateData(const QVector<QString> &name, const QVector<int> &layNumber, const QVector<double> &density, const QVector<bool> &exist);
	void addRow();
	void deleteRow();
	void refreshList();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole);
public:
	QVector<QString> lm_name;
	QVector<int> lm_layNumber;
	QVector<double> lm_density;
	QVector<bool> lm_exist;
};

struct Material  // ��������� ��������
{
	QString name; // ��� ��������� 
	double density; // ���������
	int layNum; // ����� ����
	int exist = 0; //������� ���-����� � ����� mat_files
};

class LayMaterials : public QDialog, Ui::LayMaterials
{
	Q_OBJECT

public:
	LayMaterials(Tables* table, QWidget *parent = Q_NULLPTR);
	LayMaterials(QString PRJfile, QWidget* parent = Q_NULLPTR);
	~LayMaterials();
public:
	bool r_or_p;  // ���� ��� ������� (true - REMP, false - �������)
	bool userChange = true; // ��������� �������� ������������� (true - ��, fasle - ���)
	bool saved = false; // ��������� ������ ��� ���
	bool edited = false; // �������� ������ ��� ���
	int nLayer;  // ����� �����
	Material *Layers; // ������ ����� �� ����� *.LAY
	QString path; // ���� � ����� �������
	QString materialsPath; // ���� � ����� materials
	QVector<QString> vNames; // ����� ����������
	QVector<int> vLayNumbers; // ������ ����� ����������
	QVector<double> vDensity; // ��������� ����������
	QVector<bool> vExist; // ������� ���-������ ��� ����������

	// �������� ������
	QVector<QString> fvNames;
	QVector<int> fvLayNumbers;
	QVector<double> fvDensity;
	QVector<bool> fvExist;
	
	QVector<Material> vMat; //  ������ ����������

	LayMaterialsModel *LayMatModel; // ������ ��� ����� ������ � ����� � ��������
public:
	int readLayers(QString path);  // ������ ���� layers (����� ����, �������� ���������, ���������)
	void checkMatFiles(); // ��������� ������� ����������� ���-������
	void UpdateData();  // ������ ���������� �� ������(�������)
	int WriteFile();  // ������ ���. � ���������� � ���� layers
	void ReadLay();  // ������ ����� � ���. � ����� *.LAY
	void ReadConfig(); // ������ ����� configuration

private slots:
	void OnMaterialSelected();
	void OnEditCell();
	void OnDelete();
	void OnSave();
	void OnExit();
	void OnAdd();
private:
	Ui::LayMaterials ui;
};
