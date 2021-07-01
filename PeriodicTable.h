#pragma once

#include <QWidget>
#include <QDialog.h>
#include "ui_PeriodicTable.h"
#include "QAbstractTableModel"

class PeriodicTableModel : public QAbstractTableModel // ������ ��� ������������� ������������� �������
{
	Q_OBJECT

public:
	PeriodicTableModel(QObject *parent = 0);

	void populateData(const QVector<QString> &Name, const QVector<int>  &Number);
	void addRow();
	void deleteRow();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
	QVector<QString> lm_Name;// ��� ��������
	QVector<int>  lm_Number;// ����� ��������


};

class PeriodicTable : public QDialog, public Ui::PeriodicTable
{
	Q_OBJECT

public:
	PeriodicTable(QWidget *parent = Q_NULLPTR);
	~PeriodicTable();
public:
	PeriodicTableModel *PeriodTableM; //������ ��� ����� ������ � ���. ��������� � �������� �� ������

	bool userChange = true; // ��������� �������� ������������� (true - ��, fasle - ���)
	QVector<int> number; // ������ ���. ���������
	QVector<QString> name; // ����� ���. ���������
	QString element; //�������� ������� �� �������
public:
	int readElements(); // ������ ����� � ��� � ���. ���������
private slots:
	void OnElementSelected();
private:
	Ui::PeriodicTable ui;
};
