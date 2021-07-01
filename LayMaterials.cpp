#include "LayMaterials.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QMessageBox.h"
#include "QDir.h"
#include "QFileDialog.h"
#include "Tables.h"
#include "REMP_OR_PERENOS.h"


/////////////////////////////////////////////////////////////////////////////
// �������� � ������ ������ �������, �������� ����� � ���-������
//
LayMaterials::LayMaterials(Tables* table, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	

	if (qApp->arguments().last().right(3) == "PRJ") // ���������� � ������
	{
		path = qApp->arguments().last();
		r_or_p = true; // ���������� ���� *.PRJ
	}
	else // ����������� ��� ������
	{
		REMP_OR_PERENOS dlg;
		dlg.exec();
		if (dlg.r_or_p)
		{
			r_or_p = true; // ���������� ���� *.PRJ
			QFileDialog  dialog;
			QString filename;
			dialog.setFileMode(QFileDialog::ExistingFile);
			dialog.setNameFilter(tr("Project files (*.prj)"));
			dialog.setViewMode(QFileDialog::Detail);
			if (dialog.exec() == QDialog::Accepted)
			{
				path = QFileInfo(dialog.selectedFiles()[0]).absoluteFilePath();

			}
			else
			{
				this->close();
				return;
			}
		}
		else
		{
			r_or_p = false; // ���������� ���� configuration
			QFileDialog  dialog;
			QString filename;
			dialog.setFileMode(QFileDialog::ExistingFile);
			dialog.setNameFilter(tr("Configuration file"));
			dialog.setViewMode(QFileDialog::Detail);
			if (dialog.exec() == QDialog::Accepted)
			{
				path = QFileInfo(dialog.selectedFiles()[0]).absoluteFilePath();
				ReadConfig();
			}
			else
			{
				this->close();
				return;
			}
		}


	}

	

	QString appPath = qApp->applicationDirPath();
	QDir appDir(appPath);
	appDir.cdUp();
	appPath = appDir.path();
	table->p.mat = appPath + "/share/scripts/mat_files";
	table->p.par = appPath + "/share/scripts/xrb_parameters.ini";
	table->p.home = appPath + "/share/scripts";
	table->p.rmp = path.replace("PRJ", "LTB");
	int k;
	k = path.lastIndexOf('/');
	path.remove(k, path.size() - k);
	table->p.proj = path;

	if (r_or_p)
		table->p.tab = path + "/materials";
	else if (materialsPath.contains('.'))
		table->p.tab = path + "/materials";
	else {
		QDir dir(path);
		dir.cdUp();
		table->p.tab = dir.path() + "/materials";
	}

	if(r_or_p)
		table->p.lay = path + "/layers";
	else
		table->p.lay = path + "/initials/layers";


	ReadLay(); // ������ ����� *.LAY
	readLayers(path); // �������� ������� � ������ ����� layers � temp/initials 
					  // ��� ��������� ������� ��������	



	checkMatFiles(); // ��������� ������� ��������������� ���-������

	
	// ��������� �������� ������
	fvDensity = vDensity; 
	fvExist = vExist;
	fvLayNumbers = vLayNumbers;
	fvNames = vNames;

	LayMatModel = new LayMaterialsModel(this);
	LayMatModel->populateData(vNames, vLayNumbers, vDensity, vExist);
	ui.matInfo_tv->setModel(LayMatModel);
	ui.matInfo_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.matInfo_tv->horizontalHeader()->setVisible(true);
	ui.matInfo_tv->horizontalHeader()->setStyleSheet(
		"QHeaderView::section{"
		"border-top:0px solid #D8D8D8;"
		"border-left:0px solid #D8D8D8;"
		"border-right:1px solid #D8D8D8;"
		"border-bottom: 1px solid #D8D8D8;"
		"background-color:white;"
		"padding:4px;"
		"}"
		"QTableCornerButton::section{"
		"border-top:0px solid #D8D8D8;"
		"border-left:0px solid #D8D8D8;"
		"border-right:1px solid #D8D8D8;"
		"border-bottom: 1px solid #D8D8D8;"
		"background-color:white;"
		"}");
	

	connect(ui.matInfo_tv, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnMaterialSelected()));
	connect(ui.matInfo_tv, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), this, SLOT(OnEditCell()));
	connect(ui.deleteMat_pb, SIGNAL(clicked()), this, SLOT(OnDelete()));
	connect(ui.save_pb, SIGNAL(clicked()), this, SLOT(OnSave()));
	connect(ui.exit_pb, SIGNAL(clicked()), this, SLOT(OnExit()));
	connect(ui.addMat_pb, SIGNAL(clicked()), this, SLOT(OnAdd()));

}


/////////////////////////////////////////////////////////////////////////////
// �������������� ����� layers
//
LayMaterials::LayMaterials(QString PRJfile, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	path = PRJfile;
	readLayers(PRJfile); // �������� ������� � ������ ����� layers � temp/initials 
					  // ��� ��������� ������� ��������	

	checkMatFiles(); // ��������� ������� ��������������� ���-������


	// ��������� �������� ������
	fvDensity = vDensity;
	fvExist = vExist;
	fvLayNumbers = vLayNumbers;
	fvNames = vNames;

	LayMatModel = new LayMaterialsModel(this);
	LayMatModel->populateData(vNames, vLayNumbers, vDensity, vExist);
	ui.matInfo_tv->setModel(LayMatModel);
	ui.matInfo_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.matInfo_tv->horizontalHeader()->setVisible(true);
	ui.matInfo_tv->horizontalHeader()->setStyleSheet(
		"QHeaderView::section{"
		"border-top:0px solid #D8D8D8;"
		"border-left:0px solid #D8D8D8;"
		"border-right:1px solid #D8D8D8;"
		"border-bottom: 1px solid #D8D8D8;"
		"background-color:white;"
		"padding:4px;"
		"}"
		"QTableCornerButton::section{"
		"border-top:0px solid #D8D8D8;"
		"border-left:0px solid #D8D8D8;"
		"border-right:1px solid #D8D8D8;"
		"border-bottom: 1px solid #D8D8D8;"
		"background-color:white;"
		"}");


	connect(ui.matInfo_tv, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnMaterialSelected()));
	connect(ui.matInfo_tv, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), this, SLOT(OnEditCell()));
	connect(ui.deleteMat_pb, SIGNAL(clicked()), this, SLOT(OnDelete()));
	connect(ui.save_pb, SIGNAL(clicked()), this, SLOT(OnSave()));
	connect(ui.exit_pb, SIGNAL(clicked()), this, SLOT(OnExit()));
	connect(ui.addMat_pb, SIGNAL(clicked()), this, SLOT(OnAdd()));

}

LayMaterials::~LayMaterials()
{
}

/////////////////////////////////////////////////////////////////////////////
// ������ ���� layers(����� ����, �������� ���������, ���������) 
//
int LayMaterials::readLayers(QString path)
{

	QString filename;
	if (r_or_p)
		filename = path + "/layers";
	else
		filename = path + "/initials/layers";

	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {  // ����� layers �� ����������
		// ������� ����������� ����������
		QDir().setCurrent(path);
		QDir().mkdir("materials");

		for (int i = 0; i < nLayer; i++)
		{
			vDensity.append(Layers[i].density);
			vLayNumbers.append(Layers[i].layNum);
			vNames.append(Layers[i].name);
			vExist.append(Layers[i].exist);
		}
		WriteFile(); // ������� ���� layers
		return 0;
	}
	QTextStream in(&file);

	while (!in.atEnd())
	{
		Material bufMat;
		in >> bufMat.layNum;
		in >> bufMat.name;
		in >> bufMat.density;
		if (bufMat.name == "")
			break;
		vMat.append(bufMat);
	}

	for each (Material mat in vMat)
	{
		vDensity.append(mat.density);
		vLayNumbers.append(mat.layNum);
		vNames.append(mat.name);
		vExist.append(mat.exist);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ��������� ������� ����������� ��� - ������
//
void LayMaterials::checkMatFiles()
{
	QString appPath = qApp->applicationDirPath();
	int index = appPath.lastIndexOf("/");
	appPath.remove(index + 1, appPath.size() + 1);

	const QString matFilesFolder = appPath + "share/scripts/mat_files";

	QDir matFiles(matFilesFolder);
	QStringList matFileList = matFiles.entryList(QStringList() << "*.mrat" << "*.MRAT", QDir::Files);

	for (int i = 0; i < vNames.size(); i++)
	{
		for each (QString matfile in matFileList)
		{
			if (matfile.contains(vNames[i].toLower() + ".mrat"))
				vExist[i] = 1;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// ������ ���������� �� ������(�������)
//
void LayMaterials::UpdateData()
{
	if (fvDensity.size() != LayMatModel->lm_density.size())
		edited = true;
	else
	{
		for (int  i = 0; i < vDensity.size(); i++)
		{
			if (fvDensity[i] != LayMatModel->lm_density[i])
				edited = true;
			if (fvExist[i] != LayMatModel->lm_exist[i])
				edited = true;
			if (fvLayNumbers[i] != LayMatModel->lm_layNumber[i])
				edited = true;
			if (fvNames[i] != LayMatModel->lm_name[i])
				edited = true;
		}
	}

	vDensity.clear();
	vExist.clear();
	vLayNumbers.clear();
	vNames.clear();

	for (int i = 0; i < LayMatModel->lm_density.size(); i++)
	{
		vDensity.append(LayMatModel->lm_density[i]);
		vExist.append(LayMatModel->lm_exist[i]);
		vLayNumbers.append(LayMatModel->lm_layNumber[i]);
		vNames.append(LayMatModel->lm_name[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
// ������ ���. � ���������� � ���� layers
//
int LayMaterials::WriteFile()
{
	
	QFile file(path + "/layers");
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);

	for (int i = 0; i < vNames.size(); i++)
	{
		out << vLayNumbers[i] << " " << vNames[i] << " " << vDensity[i] << endl;
	}
	file.close();
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// ������ ����� *.LAY
//
void LayMaterials::ReadLay()
{
	int addOpt; //�������������� ��������� ��� ���� (1- ����, 0 - ���)
	QString buff;
	QDir PRJ(path);
	QStringList LAYfile = PRJ.entryList(QStringList() << "*.lay" << "*.LAY", QDir::Files);

	QFile file(path + "/" + LAYfile[0]);
	file.open(QFile::ReadOnly | QFile::Text);
	QTextStream in(&file);

	in.readLine(); // ������ ������-����������� � �����
	in.readLine(); //������� ������
	in >> nLayer; in.readLine();

	Layers = new Material[nLayer];

	for (int i = 0; i < nLayer; i++)
	{
		in.readLine(); //������� ������
		in.readLine(); //������� ������
		in >> Layers[i].layNum;
		in >> Layers[i].name;
		in.readLine(); //�� ����� ������
		in.readLine(); //������� ������
		in >> buff >> buff >> buff >> buff >> addOpt; in.readLine();
		in.readLine(); //������� ������
		in >> buff >> Layers[i].density;
		in.readLine(); //�� ����� ������
		if (addOpt) //������� 2 ����� ��� ������� ���. ����������
		{
			in.readLine(); //������� ������
			in.readLine(); //������� ������
		}
	}

	file.close();
}


/////////////////////////////////////////////////////////////////////////////
// ������ ����� configuration
//
void LayMaterials::ReadConfig()
{
	QFile file(path + "/configuration");
	QString bufQStr;
	QTextStream in_configfile(&file);
	const char *bufc;
	char key_word[256], element[256];
	char s[128];
	char value[64];
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		bufQStr = in_configfile.readLine();
		QByteArray bufa = bufQStr.toLocal8Bit();
		bufc = bufa.data();
		while (bufQStr != NULL) {
			sscanf(bufc, "%[^=]%*c%s", key_word, value);
			if (!strcmp(key_word, "MATERIALS_PATH")) {
				materialsPath = value;
			}
			bufQStr = in_configfile.readLine();
			bufa = bufQStr.toLocal8Bit();
			bufc = bufa.data();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// ����� �������� �� �������
//
void LayMaterials::OnMaterialSelected() {
	if (userChange)
	{
		
		int row; // ������
		int column; // �������
		int k;
		row = ui.matInfo_tv->currentIndex().row();
		column = ui.matInfo_tv->currentIndex().column();
		if (column != 0)
			return;
		UpdateData();
		QFileDialog  dialog;
		dialog.setDirectory("C:/Program Files/REMP/share/scripts/mat_files");
		QString matfilename;
		dialog.setFileMode(QFileDialog::ExistingFile);
		dialog.setNameFilter(tr("Mat-files (*.mrat)"));
		dialog.setViewMode(QFileDialog::Detail);
		if (dialog.exec() == QDialog::Accepted)
		{
			matfilename = QFileInfo(dialog.selectedFiles()[0]).fileName();
		}
		else
		{
			return;
		}
		k = matfilename.indexOf(".");

		vNames[row] = matfilename.remove(k, matfilename.size() + 1);
		vExist[row] = true;
		LayMatModel->populateData(vNames, vLayNumbers, vDensity, vExist);
	}
}

/////////////////////////////////////////////////////////////////////////////
// �������������� � ������� �������
//
void LayMaterials::OnEditCell() 
{
	if (userChange)
	{
		int row; // ������
		int column; // �������
		int k;
		row = ui.matInfo_tv->currentIndex().row();
		column = ui.matInfo_tv->currentIndex().column();
		if (column == 0)
			return;
		QModelIndex index = ui.matInfo_tv->model()->index(row, column);
		ui.matInfo_tv->setCurrentIndex(index);
		
		ui.matInfo_tv->edit(index);

	}
}

/////////////////////////////////////////////////////////////////////////////
// �������� ���������
//
void LayMaterials::OnDelete()
{
	UpdateData();
	int i = ui.matInfo_tv->currentIndex().row();
	vDensity.remove(i);
	vLayNumbers.remove(i);
	vNames.remove(i);
	vExist.remove(i);
	LayMatModel->populateData(vNames, vLayNumbers, vDensity, vExist);
	LayMatModel->refreshList();
	edited = true;
}

/////////////////////////////////////////////////////////////////////////////
// ���������� ������ ���������
//
void LayMaterials::OnAdd()
{
	UpdateData();
	int k;
	QFileDialog  dialog;
	dialog.setDirectory("C:/Program Files/REMP/share/scripts/mat_files");
	QString matfilename;
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Mat-files (*.mrat)"));
	dialog.setViewMode(QFileDialog::Detail);
	if (dialog.exec() == QDialog::Accepted)
	{
		matfilename = QFileInfo(dialog.selectedFiles()[0]).fileName();
	}
	else
	{
		return;
	}
	k = matfilename.indexOf(".");
	matfilename = matfilename.remove(k, matfilename.size() + 1);
	vNames.append(matfilename);
	vDensity.append(0);
	vLayNumbers.append(0);
	vExist.append(true);
	LayMatModel->populateData(vNames, vLayNumbers, vDensity, vExist);
	LayMatModel->addRow();
}

/////////////////////////////////////////////////////////////////////////////
// ���������� ����� layers
//
void LayMaterials::OnSave()
{
	UpdateData(); // ���������� ������ � ������
				  // �������� ������ ���� � ���������
	for (int i = 0; i < vDensity.size(); i++)
	{
		if ((vDensity[i] < 0) || (vLayNumbers[i] < 0))
		{
			QMessageBox::information(this, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("��������� � ����� ���� �� ����� ���� ��������������!"), QMessageBox::Ok); return ;
		}
	}

	for (int i = 0; i < vDensity.size(); i++)
	{
		if (!vExist[i])
		{
			QMessageBox::information(this, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("������� �� ��� ��� �����!"), QMessageBox::Ok); return;
		}
	}

	saved = true;

	WriteFile();
	
}

/////////////////////////////////////////////////////////////////////////////
// ����� �� ���������
//
void LayMaterials::OnExit()
{
	if (saved)
	{
		this->close();
		return;
	}
	UpdateData();
	if (edited)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, " ", QString::fromLocal8Bit("��������� ���������?"),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			OnSave();
			if(saved)
				this->close();
			return;
		}
		else
			this->close();
	}
	else
	{
		this->close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// ������� ��� ������ � model/view
//
LayMaterialsModel::LayMaterialsModel(QObject *parent) : QAbstractTableModel(parent)
{
}

/////////////////////////////////////////////////////////////////////////////
// ���������� ���. � ���. ���������� � ������
//
void LayMaterialsModel::populateData(const QVector<QString> &name, const QVector<int> &layNumber, const QVector<double> &density, const QVector<bool> &exist)
{
	lm_name.clear();
	lm_layNumber.clear();
	lm_density.clear();
	lm_exist.clear();

	lm_name = name;
	lm_layNumber = layNumber;
	lm_density = density;
	lm_exist = exist;

	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(this->rowCount(), this->columnCount());
	emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole, Qt::EditRole, Qt::BackgroundColorRole });

	return;
}

void LayMaterialsModel::addRow()
{
	beginInsertRows(index(rowCount(), 0), rowCount(), rowCount());
	endInsertRows();
}

void LayMaterialsModel::deleteRow()
{
	beginRemoveRows(index(rowCount(), 0), rowCount(), rowCount());
	endRemoveRows();
}

void LayMaterialsModel::refreshList()
{
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(this->rowCount(), this->columnCount());
	emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole, Qt::EditRole, Qt::BackgroundColorRole });
}

int LayMaterialsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return lm_density.size();
}

int LayMaterialsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 3;
}

QVariant LayMaterialsModel::data(const QModelIndex &index, int role) const
{
	switch (role)
	{
	case Qt::DisplayRole:
		if (index.column() == 0) {
			return (QString("%1").arg(lm_name[index.row()]));
		}
		else if (index.column() == 1) {
			return (QString("%1").arg(lm_density[index.row()]));
		}
		else if (index.column() == 2) {
			return (QString("%1").arg(lm_layNumber[index.row()]));
		}
	case Qt::EditRole:
		if (index.column() == 0) {
			return (QString("%1").arg(lm_name[index.row()]));
		}
		else if (index.column() == 1) {
			return (QString("%1").arg(lm_density[index.row()]));
		}
		else if (index.column() == 2) {
			return (QString("%1").arg(lm_layNumber[index.row()]));
		}
	case Qt::BackgroundRole:
		if(index.column() == 0 && lm_exist[index.row()])
			return QBrush(Qt::green);
		if (index.column() == 0 && !lm_exist[index.row()])
			return QBrush(Qt::red);
		break;
		
	}
	return QVariant();
}

QVariant LayMaterialsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		if (section == 0) {
			return QString::fromLocal8Bit("��������");
		}
		else if (section == 1) {
			return  QString::fromLocal8Bit("��������� �/��3");
		}
		else if (section == 2) {
			return QString::fromLocal8Bit("����� ����");
		}
	}
	return QVariant();
}

Qt::ItemFlags LayMaterialsModel::flags(const QModelIndex &index) const
{
	if (!index.isValid() || index.column() == 0)
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool LayMaterialsModel::setData(const QModelIndex &index,
	const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole && index.column() == 1) {

		lm_density.replace(index.row(), value.toDouble());
		emit dataChanged(index, index);
		return true;
	}
	if (index.isValid() && role == Qt::EditRole && index.column() == 2) {

		lm_layNumber.replace(index.row(), value.toInt());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}