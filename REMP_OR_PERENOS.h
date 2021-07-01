#pragma once

#include <QDialog>
#include "ui_REMP_OR_PERENOS.h"

class REMP_OR_PERENOS : public QDialog
{
	Q_OBJECT

public:
	REMP_OR_PERENOS(QWidget *parent = Q_NULLPTR);
	~REMP_OR_PERENOS();
public:
	bool r_or_p; // РЕМП или перенос (true - REMP, false - Перенос)
private slots:
	void OnREMP();
	void OnPERENOS();
private:
	Ui::REMP_OR_PERENOS ui;
};
