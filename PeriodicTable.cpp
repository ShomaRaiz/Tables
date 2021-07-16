#include "PeriodicTable.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QMessageBox.h"
#include "Paths.h"
#include "QDir.h"

PeriodicTable::PeriodicTable(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	PeriodTableM = new PeriodicTableModel(this); // ������� ������ 
	ui.periodicTable_tv->setModel(PeriodTableM);//�������� QTableView � �������
	ui.periodicTable_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.periodicTable_tv->horizontalHeader()->setVisible(false); //�������� �����

	if (readElements() == -1) { // ������ ��� � ����������� � ���. ��������� (������ � �����)
		this->close();
		return;
	}
	PeriodTableM->populateData(name, number); // ��������� ������� � ������

	connect(ui.periodicTable_tv->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(OnElementSelected()));

}

PeriodicTable::~PeriodicTable()
{
}

/////////////////////////////////////////////////////////////////////////////
// ������� ����������� ���� � ���. � ���. ���������
//
int PeriodicTable::readElements()
{
	QString appPath = qApp->applicationDirPath();
	QDir dir(appPath);
	dir.cdUp();
	QString elements_f = dir.path() + "/share/scripts/elements";
	QFile file(elements_f);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Manager"),
			QString("�� ������� ��������� ���� %1:\n%2.")
			.arg("PeriodTable.txt")
			.arg(file.errorString()));
		return -1;
	}
	QTextStream in(&file);

	while (true) // ���������� ���������� �� ����� � ������� (��� � �����)
	{
		int a;
		QString b;
		in >> b;
		in >> a;
		number.append(a);
		name.append(b);
		in.readLine();
		if (in.atEnd())
			break;
	}
	number.append(0); number.append(0); number.append(0);
	name.append(0); name.append(0); name.append(0);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ����� �������� �� �������
//
void PeriodicTable::OnElementSelected() {
	if (userChange)
	{
		int row; // ������
		int column; // �������
		int vnumber; // ����� � �������

		row = ui.periodicTable_tv->currentIndex().row();
		column = ui.periodicTable_tv->currentIndex().column();

		vnumber = row*5 + column;
		element = QString("%1").arg(name[vnumber]);
		this->close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// ������� ��� ������ � model/view
//
PeriodicTableModel::PeriodicTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

/////////////////////////////////////////////////////////////////////////////
// ���������� ���. � ���. ���������� � ������
//
void PeriodicTableModel::populateData(const QVector<QString> &Name, const QVector<int>  &Number)
{
	lm_Name.clear();
	lm_Number.clear();

	lm_Name = Name;
	lm_Number = Number;

	return;
}

/////////////////////////////////////////////////////////////////////////////
//���-�� �����
//
int PeriodicTableModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 26;
}

/////////////////////////////////////////////////////////////////////////////
// ���-�� ��������
//
int PeriodicTableModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 5;
}

QVariant PeriodicTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole) {
		return QVariant();
	}
	if (index.column() == 0) {
		return (QString("%1:%2").arg(lm_Number[index.row()*5]).arg(lm_Name[index.row() * 5]));
	}
	else if (index.column() == 1) {
		return QString("%1:%2").arg(lm_Number[index.row() * 5 + 1]).arg(lm_Name[index.row() * 5 + 1]);
	}
	else if (index.column() == 2) {
		return QString("%1:%2").arg(lm_Number[index.row() * 5 + 2]).arg(lm_Name[index.row() * 5 + 2]);
	}
	else if (index.column() == 3) {
		return QString("%1:%2").arg(lm_Number[index.row() * 5 + 3]).arg(lm_Name[index.row() * 5 + 3]);
	}
	else if (index.column() == 4) {
		return QString("%1:%2").arg(lm_Number[index.row() * 5 + 4]).arg(lm_Name[index.row() * 5 + 4]);
	}
	return QVariant();
}

QVariant PeriodicTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
	}
	return QVariant();
}
