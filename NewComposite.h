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

	QString compositeName; // Имя композита
	QVector<QString> elementName; // Имена элементов из которых сосотоит композит
	QVector<double> elementPortion; // Процентное содержание элемента в композите
	double compositeDensity; // Плотность композита

	QPushButton *elementPB[14]; // Указатели на PushButton элементов
	QLineEdit *elementLE[14]; // Указатели на LineEdit элементов
	QComboBox *elementCB[14]; // Указатель на ComboBox элементов (ионизированность)

public:
	int readMRAT(QString filename); // Чтение файла с инф. о композите формата *.mrat
private slots:
	void OnElement(); //При нажатии на кнопку выбора элемента из таблицы
	void OnOpen(); // При нажатии на кнопку "Открыть"
	void OnIon(); // При нажатии на кнопку "Ионизированный"
	void OnCheck(); // При нажатии кнопки "Проверить" (складывает доли хим элементов)
	void OnCreate(); // При нажатии кнопки "Создать"
	void OnSave(); // При нажатии кнопки "Сохранить" 
private:
	Ui::NewComposite ui;
};

#endif
