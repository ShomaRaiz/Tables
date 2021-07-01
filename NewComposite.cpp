#include "NewComposite.h"
#include "PeriodicTable.h"
#include "QFile.h"
#include "QMessageBox.h"
#include "QTextStream.h"
#include "QFileDialog.h"

NewComposite::NewComposite(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	 


	// Связываем однотипные элементы интерфейса в массивы
	elementPB[0] = ui.el1_pb;		elementLE[0] = ui.el1_le;
	elementPB[1] = ui.el2_pb;		elementLE[1] = ui.el2_le;
	elementPB[2] = ui.el3_pb;		elementLE[2] = ui.el3_le;
	elementPB[3] = ui.el4_pb;		elementLE[3] = ui.el4_le;
	elementPB[4] = ui.el5_pb;		elementLE[4] = ui.el5_le;
	elementPB[5] = ui.el6_pb;		elementLE[5] = ui.el6_le;
	elementPB[6] = ui.el7_pb;		elementLE[6] = ui.el7_le;
	elementPB[7] = ui.el8_pb;		elementLE[7] = ui.el8_le;
	elementPB[8] = ui.el9_pb;		elementLE[8] = ui.el9_le;
	elementPB[9] = ui.el10_pb;		elementLE[9] = ui.el10_le;
	elementPB[10] = ui.el11_pb;		elementLE[10] = ui.el11_le;
	elementPB[11] = ui.el12_pb;		elementLE[11] = ui.el12_le;
	elementPB[12] = ui.el13_pb;		elementLE[12] = ui.el13_le;
	elementPB[13] = ui.el14_pb;		elementLE[13] = ui.el14_le;

	elementCB[0] = ui.el1_cb;
	elementCB[1] = ui.el2_cb;
	elementCB[2] = ui.el3_cb;
	elementCB[3] = ui.el4_cb;
	elementCB[4] = ui.el5_cb;
	elementCB[5] = ui.el6_cb;
	elementCB[6] = ui.el7_cb;
	elementCB[7] = ui.el8_cb;
	elementCB[8] = ui.el9_cb;
	elementCB[9] = ui.el10_cb;
	elementCB[10] = ui.el11_cb;
	elementCB[11] = ui.el12_cb;
	elementCB[12] = ui.el13_cb;
	elementCB[13] = ui.el14_cb;


	// Задаем постоянный размер элементов интерфейса при их скрытии
	for (int i = 0; i < 14; i++)
	{
		QSizePolicy p = elementCB[i]->sizePolicy();
		p.setRetainSizeWhenHidden(true);
		elementCB[i]->setSizePolicy(p);
		elementCB[i]->addItem("0");
		elementCB[i]->addItem("1");
		elementCB[i]->addItem("2");
	}
	QSizePolicy p = ui.ionCharg_lb->sizePolicy();
	p.setRetainSizeWhenHidden(true);
	ui.ionCharg_lb->setSizePolicy(p);

	// Скрываем ионизированность элементов
	for (int i = 0; i < 14; i++)
	{
		elementCB[i]->hide();
	}
	ui.ionCharg_lb->hide();

	// Связываем сигналы от эелементов интерфейса с функциями 
	connect(ui.el1_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el2_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el3_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el4_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el5_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el6_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el7_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el8_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el9_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el10_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el11_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el12_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el13_pb, SIGNAL(clicked()), this, SLOT(OnElement()));
	connect(ui.el14_pb, SIGNAL(clicked()), this, SLOT(OnElement()));

	connect(ui.open_pb, SIGNAL(clicked()), this, SLOT(OnOpen()));
	connect(ui.ioniz_pb, SIGNAL(clicked()), this, SLOT(OnIon()));
	connect(ui.check_pb, SIGNAL(clicked()), this, SLOT(OnCheck()));
	connect(ui.create_pb, SIGNAL(clicked()), this, SLOT(OnCreate()));
	connect(ui.save_pb, SIGNAL(clicked()), this, SLOT(OnSave()));

}

NewComposite::~NewComposite()
{
}

/////////////////////////////////////////////////////////////////////////////
// Чтение файла с инф. о композите формата *.mrat
//
int NewComposite::readMRAT(QString filename)
{
	QString tmp,key, value;
	int k;
	double buf;

	

	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Manager"),
			QString::fromUtf8("Не удается прочитать файл %1:\n%2.")
			.arg(filename)
			.arg(file.errorString()));
		return -1;
	}
	QTextStream in(&file);

	elementName.clear();
	elementPortion.clear();

	while (!in.atEnd())
	{
		in >> tmp;
		if (tmp == "[Composite]")
		{ 
			in >> compositeName;
		}
		if (tmp == "[Element]")
		{
			in >> tmp >> buf;
			elementName.append(tmp);
			elementPortion.append(buf);
		}
		if (tmp == "[Density]")
		{
			in >> compositeDensity;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// При нажатии на кнопку выбора элемента из таблицы
//
void NewComposite::OnElement()
{
	PeriodicTable dlg; 
	dlg.exec(); //Открытие таблицы с хим. элементами
	if (this->sender() == ui.el1_pb)
		ui.el1_pb->setText(dlg.element);
	if (this->sender() == ui.el2_pb)
		ui.el2_pb->setText(dlg.element);
	if (this->sender() == ui.el3_pb)
		ui.el3_pb->setText(dlg.element);
	if (this->sender() == ui.el4_pb)
		ui.el4_pb->setText(dlg.element);
	if (this->sender() == ui.el5_pb)
		ui.el5_pb->setText(dlg.element);
	if (this->sender() == ui.el6_pb)
		ui.el6_pb->setText(dlg.element);
	if (this->sender() == ui.el7_pb)
		ui.el7_pb->setText(dlg.element);
	if (this->sender() == ui.el8_pb)
		ui.el8_pb->setText(dlg.element);
	if (this->sender() == ui.el9_pb)
		ui.el9_pb->setText(dlg.element);
	if (this->sender() == ui.el10_pb)
		ui.el10_pb->setText(dlg.element);
	if (this->sender() == ui.el11_pb)
		ui.el11_pb->setText(dlg.element);
	if (this->sender() == ui.el12_pb)
		ui.el12_pb->setText(dlg.element);
	if (this->sender() == ui.el13_pb)
		ui.el13_pb->setText(dlg.element);
	if (this->sender() == ui.el14_pb)
		ui.el14_pb->setText(dlg.element);
}

/////////////////////////////////////////////////////////////////////////////
// Открываем файл с композитом
//
void NewComposite::OnOpen() 
{
	// Диалог для выбора файла *.mrat
	QFileDialog  dialog;
	QString FileName;
	QString Path;
	dialog.setDirectory("C:\Program Files\REMP\share\scripts\mat_files");
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Layers files (*.mrat)"));
	dialog.setViewMode(QFileDialog::Detail);
	if (dialog.exec() == QDialog::Accepted)
	{
		FileName = QFileInfo(dialog.selectedFiles()[0]).fileName();
		Path = QFileInfo(dialog.selectedFiles()[0]).path();
	}
	else
	{
		return;
	}
	
	QDir::setCurrent(Path);
	if (readMRAT(Path + '/' + FileName) == -1)
		return;
	for (int i = 0; i < elementName.size(); i++)
	{
		elementPB[i]->setText(elementName[i]); // имя хим. элемента
		elementLE[i]->setText(QString("%1").arg(elementPortion[i])); // доля хим. элемента
	}

	ui.name_le->setText(compositeName); // Имя композита
	ui.density_le->setText(QString("%1").arg(compositeDensity)); // Плотность композита
}

/////////////////////////////////////////////////////////////////////////////
// Настраиваем ионизированность
//
void NewComposite::OnIon()
{
	if (ui.ionCharg_lb->isVisible())
	{
		for (int i = 0; i < 14; i++)
		{
			elementCB[i]->hide();
		}
		ui.ionCharg_lb->hide();
	}
	else
	{
		for (int i = 0; i < 14; i++)
		{
			elementCB[i]->show();
		}
		ui.ionCharg_lb->show();
	}
}

/////////////////////////////////////////////////////////////////////////////
//  При нажатии кнопки "Проверить" (складывает доли хим элементов)
//
void  NewComposite::OnCheck()
{
	double sum = 0;
	for (int i = 0; i < 14; i++)
	{
		if (elementLE[i]->text() != "")
		{
			sum += elementLE[i]->text().toDouble();
		}
	}

	QMessageBox::information(this, QString::fromLocal8Bit("Композиты"), QString::fromLocal8Bit("Сумма массовых долей хим. елементов равна %1").arg(sum), QMessageBox::Ok); return;
}

/////////////////////////////////////////////////////////////////////////////
//  Создание нового композита
//
void  NewComposite::OnCreate()
{
	//
	for (int i = 0; i < 14; i++)
	{
		elementPB[i]->setText("");
		elementLE[i]->setText("");
		elementCB[i]->setCurrentIndex(0);
	}
	ui.density_le->setText("");
	ui.name_le->setText("MATERIAL");
}

/////////////////////////////////////////////////////////////////////////////
//  Сохранение композита
//
void  NewComposite::OnSave()
{
	//Проверка вводимых данных 
	if (ui.density_le->text() == "" || ui.density_le->text().toDouble() <= 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Композиты"), QString::fromLocal8Bit("Неправильно задана плотность композита!"), QMessageBox::Ok); return;
	}

	for (int  i = 0; i < 14; i++)
	{
		if (elementPB[i]->text() != "")
		{
			if (elementLE[i]->text().toDouble() <= 0)
			{
				QMessageBox::information(this, QString::fromLocal8Bit("Композиты"), QString::fromLocal8Bit("Неправильно задана доля хим. элемента %1").arg(elementPB[i]->text()), QMessageBox::Ok); return;
			}
		}
	}

	double sum = 0;
	for (int i = 0; i < 14; i++)
	{
		if (elementLE[i]->text() != "")
		{
			sum += elementLE[i]->text().toDouble();
		}
	}
	if (  abs(1 - sum) > 0.00000001)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Композиты"), QString::fromLocal8Bit("Сумма массовых долей хим. элементов в композите не равна 1!"), QMessageBox::Ok); return;
	}



	compositeName = ui.name_le->text();
	QString FileName = compositeName;
	QString FullName = QFileDialog::getSaveFileName(this, tr("Save File"), FileName, tr("mrat (*.mrat)")); // Выбор места сохранения и имени файла

	if ( FullName.isEmpty() || FullName.isNull()) { // при отмене диалога сохранения
		return;
	}

	QFile file(FullName);
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);

	// Запись в файл .mrat
	out << "[Composite] " << compositeName << endl;
	for (int i = 0; i < 14; i++)
	{
		if (elementPB[i]->text() != "")
		{
			out << "[Element] " << elementPB[i]->text() << " " << elementLE[i]->text() << endl;
		}
	}
	out << "[Density] " << ui.density_le->text() << endl;

	file.close();
}