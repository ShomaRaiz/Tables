#ifndef TABLES_H
#define TABLES_H


#include "Paths.h"
#include "ui_Tables.h"

#include <QtWidgets/QMainWindow>


class Tables : public QMainWindow
{
    Q_OBJECT

public:
    Tables(QWidget* parent = Q_NULLPTR);
    ~Tables();
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
    void OnParameters();  // ��� ������ ���� "���������"
    void OnExit();
    void OnGraphs(); // �������
private:
    Ui::TablesClass ui;
    void init_paths();

};


#endif

