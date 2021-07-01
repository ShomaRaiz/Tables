#pragma once

#include <QWidget>
#include <QDialog>

#include "ui_LayMaterials.h"
class Tables;
class LayMaterialsModel : public QAbstractTableModel // модель для представления информации о материалах в таблице
{
	Q_OBJECT

public:
	LayMaterialsModel(QObject *parent = 0);

	void populateData(const QVector<QString> &name, const QVector<int> &layNumber, const QVector<double> &density, const QVector<bool> &exist);
	void addRow();
	void deleteRow();
	void refreshList();
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole);
public:
	QVector<QString> lm_name;
	QVector<int> lm_layNumber;
	QVector<double> lm_density;
	QVector<bool> lm_exist;
};

struct Material  // стркутура материал
{
	QString name; // имя материала 
	double density; // плотность
	int layNum; // номер слоя
	int exist = 0; //наличие мат-файла в папке mat_files
};

class LayMaterials : public QDialog, Ui::LayMaterials
{
	Q_OBJECT

public:
	LayMaterials(Tables* table, QWidget *parent = Q_NULLPTR);
	LayMaterials(QString PRJfile, QWidget* parent = Q_NULLPTR);
	~LayMaterials();
public:
	bool r_or_p;  // РЕМП или перенос (true - REMP, false - Перенос)
	bool userChange = true; // изменения вводятся пользователем (true - Да, fasle - Нет)
	bool saved = false; // сохранены данные или нет
	bool edited = false; // изменены данные или нет
	int nLayer;  // число слоев
	Material *Layers; // Список слоев из файла *.LAY
	QString path; // путь к папке проекта
	QString materialsPath; // Путь к папке materials
	QVector<QString> vNames; // Имена материалов
	QVector<int> vLayNumbers; // Номера слоев материалов
	QVector<double> vDensity; // Плотность материалов
	QVector<bool> vExist; // Наличие мат-файлов для материалов

	// Исходные данные
	QVector<QString> fvNames;
	QVector<int> fvLayNumbers;
	QVector<double> fvDensity;
	QVector<bool> fvExist;
	
	QVector<Material> vMat; //  вектор материалов

	LayMaterialsModel *LayMatModel; // модель для связи данных о слоях с таблицой
public:
	int readLayers(QString path);  // Читаем файл layers (номер слоя, название материала, плотность)
	void checkMatFiles(); // Проверяем наличие необходимых мат-файлов
	void UpdateData();  // Запись информации из модели(таблицы)
	int WriteFile();  // Запись инф. о материалах в файл layers
	void ReadLay();  // Чтение файла с инф. о слоях *.LAY
	void ReadConfig(); // Чтение файла configuration

private slots:
	void OnMaterialSelected();
	void OnEditCell();
	void OnDelete();
	void OnSave();
	void OnExit();
	void OnAdd();
private:
	Ui::LayMaterials ui;
};
