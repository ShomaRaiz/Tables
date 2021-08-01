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
    void OnParameters();  // При вызове окна "Параметры"
    void OnExit();
    void OnGraphs(); // Графики
private:
    Ui::TablesClass ui;
    void init_paths();

};


#endif

