#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tables.h"

struct Paths
{
    QString mat;
    QString par;
    QString home;
    QString proj;
    QString rmp;
    QString tab;
    QString lay;
    bool electron = true;
    bool photon = true;
};

class Tables : public QMainWindow
{
    Q_OBJECT

public:
    Tables(QWidget *parent = Q_NULLPTR);
public:
    QString PRJpath; //���� � ����� �������
    Paths p; // ����������� ����
    bool openPRJ = false; // ������ (.PRJ) ������ � ��������
    bool calcDist = false; // ������������� ����������
private slots:
	void OnMatFile(); // ��� ������� �� ������ "������ � ���-�������"
	void OnOpenPRJ(); // ��� ������� �� ������ "������� ���� *.PRJ ������� ����"
    void OnEditFile(); // ��� ������� �� ������ "������������� ���� ��������"
    void OnCalcDist(); // ��� ������� �� ������ "���������� �������������"
    void OnGetDist();  // ��� ������� �� ������ "�������� ������������� ��� ����"
private:
    Ui::TablesClass ui;

};
