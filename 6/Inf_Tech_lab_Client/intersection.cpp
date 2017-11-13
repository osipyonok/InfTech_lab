#include "intersection.h"
#include "ui_intersection.h"
#include <QHBoxLayout>


Intersection::Intersection(QTableWidget *_table , vector<QString> possible , QString _curTable , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Intersection)
{
    this->table = _table;
    this->curTable = _curTable;
    ui->setupUi(this);
    //auto table = this->db->getDataTable(curTable);
    ui->possibleTables->insertColumn(0);
    ui->possibleTables->insertColumn(1);
    ui->possibleTables->setHorizontalHeaderItem(0 , new QTableWidgetItem("Назва"));
    ui->possibleTables->setHorizontalHeaderItem(1 , new QTableWidgetItem("Вибiр"));
    for(auto &name : possible){
        ui->possibleTables->insertRow(ui->possibleTables->rowCount());

        auto lab = new QLabel(ui->possibleTables);
        lab->setText(name);
        ui->possibleTables->setCellWidget(ui->possibleTables->rowCount() - 1 , 0 , lab);

        QWidget *cbWidget = new QWidget();
        auto cBox = new QCheckBox();
        QHBoxLayout *layoutCheckBox = new QHBoxLayout(cbWidget);
        layoutCheckBox->addWidget(cBox);
        layoutCheckBox->setAlignment(Qt::AlignCenter);
        layoutCheckBox->setContentsMargins(0 , 0 , 0 , 0);

        ui->possibleTables->setCellWidget(ui->possibleTables->rowCount() - 1 , 1 , cbWidget);
    }


  //  ui->possibleTables->resizeRowsToContents();
  //  ui->possibleTables->resizeColumnsToContents();

}

Intersection::~Intersection()
{
    delete ui;
}

void Intersection::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text() == "OK"){
        vector<QString> v = {this->curTable};
        for(int i = 0 ; i < ui->possibleTables->rowCount() ; ++i){
            if(qobject_cast<QCheckBox *>(ui->possibleTables->cellWidget(i , 1)->
                                         layout()->itemAt(0)->widget())->checkState() == Qt::Checked){
                v.push_back(qobject_cast<QLabel *>(ui->possibleTables->cellWidget(i , 0))->text());
            }
        }
        this->result_tables = v;
        this->result = true;
    }else{
        this->result = false;
    }
}

vector<QString> Intersection::getResultTables()const{
    return this->result_tables;
}

bool Intersection::getResult()const{
    return this->result;
}
