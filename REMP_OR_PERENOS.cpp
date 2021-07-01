#include "REMP_OR_PERENOS.h"

REMP_OR_PERENOS::REMP_OR_PERENOS(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.PERENOS_pb, SIGNAL(clicked()), this, SLOT(OnPERENOS()));
	connect(ui.REMP_pb, SIGNAL(clicked()), this, SLOT(OnREMP()));
}

REMP_OR_PERENOS::~REMP_OR_PERENOS()
{
}

void REMP_OR_PERENOS::OnREMP()
{
	r_or_p = true;
	this->close();
}

void REMP_OR_PERENOS::OnPERENOS()
{
	r_or_p = false;
	this->close();
}