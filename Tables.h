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
    QString PRJpath; //путь к папке проекта
    Paths p; // необходимые пути
    bool openPRJ = false; // проект (.PRJ) открыт и сохранен
    bool calcDist = false; // распределение рассчитано
private slots:
	void OnMatFile(); // При нажатии на кнопку "Работа с мат-файлами"
	void OnOpenPRJ(); // При нажатии на кнопку "Открыть файл *.PRJ проекта РЭМП"
    void OnEditFile(); // При нажатии на кнопку "Редактировать файл оболочек"
    void OnCalcDist(); // При нажатии на кнопку "Рассчитать распределение"
    void OnGetDist();  // При нажатии на кнопку "Получить распределение для РЭМП"
private:
    Ui::TablesClass ui;

};
