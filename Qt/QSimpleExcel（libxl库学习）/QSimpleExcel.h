#pragma once
#ifndef EXCEL_H
#define EXCEL_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include "libxl.h"
/***************************************
* ˵������excel����
* ���ߣ�caokexiang
* ʱ�䣺20240522
******************************************/
class QSimpleExcel{
public:
	QSimpleExcel(QString const& fileName, QString const& sheetName);//��������sheet��excel�ļ�
	QSimpleExcel(QString const& fileName, uint sheetIndex=0); //��excel�ļ�,�����ļ�����׺
public:
	/**********sheet��ط���************/
	bool addSheet(QString const& sheetName);	//���һ��sheet��������ǰ����sheet=�����sheet
	bool insertSheet(uint index, QString const& sheetName); //����һ��sheet��������ǰ����sheet=����sheet
	libxl::Sheet* setSheet(int index);		//������sheet����Ϊindex
	bool deleteSheet(uint index);	//��sheet srcIndex ���� sheet destIndex֮ǰ
public:
	/***********************************
	* ���ܣ���ǰ������sheet��д������
	* ������row���У�0��ʼ���� col���У�item����д������
	* ����ֵ���Ƿ�д��ɹ�
	* ���ߣ�caokexiang
	* ���ڣ�20240526
	**********************************/
	bool write(uint row, uint col, QString item);
	bool writeRed(uint row, uint col, QString item); //������ɫΪ��ɫ
	bool writeRow(uint row, uint col, QStringList items); // (row, col)��ʼ��д��
	bool writeCol(uint row, uint col, QStringList items); // ��row�� col����ʼ��д��
	int getRows(); //��ʹ�õ�����
	int getCols();

	QString read(uint row, uint col); //��ȡ���ֻ����ı�


private:
	QString bookName; //excel�ļ���
	libxl::Book* book;	//excel����
	libxl::Sheet* sheet; //��ǰ������sheet


};
#endif