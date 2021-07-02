#ifndef NEW_COMPOSITE_H
#define NEW_COMPOSITE_H

#include <QWidget>
#include <QDialog.h>
#include "ui_NewComposite.h"

class NewComposite : public QDialog, public Ui::NewComposite
{
	Q_OBJECT

public:
	NewComposite(QWidget *parent = Q_NULLPTR);
	~NewComposite();

	QString compositeName; // ��� ���������
	QVector<QString> elementName; // ����� ��������� �� ������� �������� ��������
	QVector<double> elementPortion; // ���������� ���������� �������� � ���������
	double compositeDensity; // ��������� ���������

	QPushButton *elementPB[14]; // ��������� �� PushButton ���������
	QLineEdit *elementLE[14]; // ��������� �� LineEdit ���������
	QComboBox *elementCB[14]; // ��������� �� ComboBox ��������� (����������������)

public:
	int readMRAT(QString filename); // ������ ����� � ���. � ��������� ������� *.mrat
private slots:
	void OnElement(); //��� ������� �� ������ ������ �������� �� �������
	void OnOpen(); // ��� ������� �� ������ "�������"
	void OnIon(); // ��� ������� �� ������ "��������������"
	void OnCheck(); // ��� ������� ������ "���������" (���������� ���� ��� ���������)
	void OnCreate(); // ��� ������� ������ "�������"
	void OnSave(); // ��� ������� ������ "���������" 
private:
	Ui::NewComposite ui;
};

#endif
