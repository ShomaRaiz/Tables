#include "Parameters.h"
#include "QMainWindow.h"
#include "QBoxLayout.h"
#include "QMenuBar.h"
#include "QDir.h"
#include "QMessageBox.h"
#include "qtextstream.h"
#include "QFileDialog.h"
#include "QCloseEvent"

Parameters::Parameters(QWidget *parent)
	: QDialog(parent)
{
	QMenuBar* menuBar = new QMenuBar(this);
	menuBar->setMinimumWidth(1000);
	QMenu *File = new QMenu(QString::fromLocal8Bit("Файл"), menuBar);
	QAction* Help = new QAction(QString::fromLocal8Bit("Помощь"), menuBar);
	QAction* action1 = new QAction(QString::fromLocal8Bit("Открыть"));
	QAction* action2 = new QAction(QString::fromLocal8Bit("Сохранить"));
	QAction* action3 = new QAction(QString::fromLocal8Bit("Сохранить как"));
	QAction* action4 = new QAction(QString::fromLocal8Bit("Выйти"));
	File->addAction(action1);
	File->addAction(action2);
	File->addAction(action3);
	File->addAction(action4);
	menuBar->addMenu(File);
	menuBar->addAction(Help);

	ui.setupUi(this);

	
	InitData();
	readParametersIni();
	UpdateData(false);

	connect(action2, SIGNAL(triggered()), this, SLOT(OnSave()));
	connect(action3, SIGNAL(triggered()), this, SLOT(OnSaveAs()));
	connect(action1, SIGNAL(triggered()), this, SLOT(OnOpen()));
	connect(action4, SIGNAL(triggered()), this, SLOT(OnExit()));
}

Parameters::~Parameters()
{
}

/////////////////////////////////////////////////////////////////////////////
// Загрузка исходных данных
//
void Parameters::InitData()
{
	int en[15] = {1,2,3,4,5,6,7,8,9,10,15,20,25,50,100};
	enMap[1] = 0;
	enMap[2] = 1;
	enMap[3] = 2;
	enMap[4] = 3;
	enMap[5] = 4;
	enMap[6] = 5;
	enMap[7] = 6;
	enMap[8] = 7;
	enMap[9] = 8;
	enMap[10] = 9;
	enMap[15] = 10;
	enMap[20] = 11;
	enMap[25] = 12;
	enMap[50] = 13;
	enMap[100] = 14;

	for (int i = 0; i < 15; i++)
	{
		ui.Emax_cb->addItem(QString("%1").arg(en[i]));
		ui.Emin_cb->addItem(QString("%1").arg(en[i]));
		ui.En_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_annig_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_br_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_br_tet_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_el_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_ion_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_para_cb->addItem(QString("%1").arg(en[i]));
		ui.nG_photo_cb->addItem(QString("%1").arg(en[i]));
	}

	QString appPath = qApp->applicationDirPath();
	QDir dir(appPath);
	dir.cdUp();
	fParameterIni = dir.path() + "/share/scripts/xrb_parameters.ini";
	
}

/////////////////////////////////////////////////////////////////////////////
// Чтение файла с параметрами
//
void Parameters::readParametersIni()
{
	
	QFile file(fParameterIni);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Manager"),
			QString::fromLocal8Bit("Не удалось открыть файл %1.")
			.arg(fParameterIni));
		return;
	}

	QTextStream in(&file);

	QString buff;
	int b;
	while (!in.atEnd())
	{
		in >> buff >> b;
		if (buff == "[Emin]")
		{
			param.Emin = b;
			param_init.Emin = b;
		}
		else if (buff == "[Emax]")
		{ 
			param.Emax = b;
			param_init.Emax = b;
		}
		else if (buff == "[En]")
		{
			param.En = b;
			param_init.En = b;
		}
		else if (buff == "[nG]")
		{
			param.nG = b;
			param_init.nG = b;
		}
		else if (buff == "[nG_el]")
		{
			param.nG_el = b;
			param_init.nG_el = b;
		}
		else if (buff == "[nG_ion]")
		{
			param.nG_ion = b;
			param_init.nG_ion = b;
		}
		else if (buff == "[nG_br_tet]")
		{
			param.nG_br_tet = b;
			param_init.nG_br_tet = b;
		}
		else if (buff == "[nG_photo]")
		{
			param.nG_photo = b;
			param_init.nG_photo = b;
		}
		else if (buff == "[nG_br]")
		{
			param.nG_br = b;
			param_init.nG_br = b;
		}
		else if (buff == "[nG_para]")
		{
			param.nG_para = b;
			param_init.nG_para = b;
		}
		else if (buff == "[nG_annig]")
		{
			param.nG_annig = b;
			param_init.nG_annig = b;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// Обмен данными с экраном (true - считываем с экрана, false - запись на экран)
//
void Parameters::UpdateData(bool a)
{
	if (a)
	{
		param.Emin = ui.Emin_cb->currentText().toInt();
		param.Emax = ui.Emax_cb->currentText().toInt();
		param.En = ui.En_cb->currentText().toInt();
		param.nG = ui.nG_cb->currentText().toInt();
		param.nG_annig = ui.nG_annig_cb->currentText().toInt();
		param.nG_br = ui.nG_br_cb->currentText().toInt();
		param.nG_br_tet = ui.nG_br_tet_cb->currentText().toInt();
		param.nG_el = ui.nG_el_cb->currentText().toInt();
		param.nG_ion = ui.nG_ion_cb->currentText().toInt();
		param.nG_para = ui.nG_para_cb->currentText().toInt();
		param.nG_photo = ui.nG_photo_cb->currentText().toInt();
	}
	else
	{
		ui.Emax_cb->setCurrentIndex(enMap[param.Emax]);
		ui.Emin_cb->setCurrentIndex(enMap[param.Emin]);
		ui.En_cb->setCurrentIndex(enMap[param.En]);
		ui.nG_annig_cb->setCurrentIndex(enMap[param.nG_annig]);
		ui.nG_br_cb->setCurrentIndex(enMap[param.nG_br]);
		ui.nG_br_tet_cb->setCurrentIndex(enMap[param.nG_br_tet]);
		ui.nG_cb->setCurrentIndex(enMap[param.nG]);
		ui.nG_el_cb->setCurrentIndex(enMap[param.nG_el]);
		ui.nG_ion_cb->setCurrentIndex(enMap[param.nG_ion]);
		ui.nG_para_cb->setCurrentIndex(enMap[param.nG_para]);
		ui.nG_photo_cb->setCurrentIndex(enMap[param.nG_photo]);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Редактировался файл или нет
//
bool Parameters::EditedCheck()
{
	UpdateData(true);
	if (param.Emax != param_init.Emax)
		return false;
	if (param.Emin != param_init.Emin)
		return false;
	if (param.En != param_init.En)
		return false;
	if (param.nG != param_init.nG)
		return false;
	if (param.nG_ion != param_init.nG_ion)
		return false;
	if (param.nG_br_tet != param_init.nG_br_tet)
		return false;
	if (param.nG_photo != param_init.nG_photo)
		return false;
	if (param.nG_br != param_init.nG_br)
		return false;
	if (param.nG_para != param_init.nG_para)
		return false;
	if (param.nG_annig != param_init.nG_annig)
		return false;
	if (param.nG_br_tet != param_init.nG_br_tet)
		return false;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Сохраняем файл .ini
//
void Parameters::OnSave()
{
	UpdateData(true);
	QFile file(fParameterIni);
	QTextStream out(&file);
	if (file.open(QFile::WriteOnly | QFile::Text))
	{
		out << "[Emin] " << param.Emin << endl;
		out << "[Emax] " << param.Emax << endl;
		out << "[En] " << param.En << endl;
		out << "[nG] " << param.nG << endl;
		out << "[nG_el] " << param.nG_el << endl;
		out << "[nG_ion] " << param.nG_ion << endl;
		out << "[nG_br] " << param.nG_br << endl;
		out << "[nG_br_tet] " << param.nG_br_tet << endl;
		out << "[nG_photo] " << param.nG_photo << endl;
		out << "[nG_para] " << param.nG_para << endl;
		out << "[nG_annig] " << param.nG_annig << endl;
		file.close();
	}
	
	param_init = param;
}

/////////////////////////////////////////////////////////////////////////////
// Сохраняем файл .ini
//
void Parameters::OnSaveAs()
{
	UpdateData(true);
	fParameterIni = QFileDialog::getSaveFileName(this, tr("Save File"), fParameterIni, tr("INI (*.ini)"));
	if (fParameterIni.size() == 0) return;
	QFile file(fParameterIni);
	QTextStream out(&file);
	if (file.open(QFile::WriteOnly | QFile::Text))
	{
		out << "[Emin] " << param.Emin << endl;
		out << "[Emax] " << param.Emax << endl;
		out << "[En] " << param.En << endl;
		out << "[nG] " << param.nG << endl;
		out << "[nG_el] " << param.nG_el << endl;
		out << "[nG_ion] " << param.nG_ion << endl;
		out << "[nG_br] " << param.nG_br << endl;
		out << "[nG_br_tet] " << param.nG_br_tet << endl;
		out << "[nG_photo] " << param.nG_photo << endl;
		out << "[nG_para] " << param.nG_para << endl;
		out << "[nG_annig] " << param.nG_annig << endl;
		file.close();
	}
	param_init = param;
}

/////////////////////////////////////////////////////////////////////////////
// Открываем файл с параметрами (*.ini)
//
void Parameters::OnOpen()
{
	QFileDialog  dialog;
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Parameteres file (*.ini)"));
	dialog.setViewMode(QFileDialog::Detail);
	if (dialog.exec() == QDialog::Accepted)
	{
		QString FileName = QFileInfo(dialog.selectedFiles()[0]).fileName();
		QString Path = QFileInfo(dialog.selectedFiles()[0]).path();
		fParameterIni = Path + "/" + FileName;
		readParametersIni();
		UpdateData(false);
	}
	else
	{
		return;
	}

}

/////////////////////////////////////////////////////////////////////////////
// Выход
void Parameters::OnExit()
{
	if (EditedCheck())
		this->close();
	else
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, " ", QString::fromLocal8Bit("Выйти без сохранения?"),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::No) return;
		else
			this->close();
	}

}

void Parameters::closeEvent(QCloseEvent* event)
{
	if (EditedCheck())
		this->close();
	else
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, " ", QString::fromLocal8Bit("Выйти без сохранения?"),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::No) event->ignore();
		else
			event->accept();
	}

}