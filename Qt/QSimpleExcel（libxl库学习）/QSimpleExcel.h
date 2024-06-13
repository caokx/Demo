#pragma once
#ifndef EXCEL_H
#define EXCEL_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include "libxl.h"
/***************************************
* 说明：简单excel操作
* 作者：caokexiang
* 时间：20240522
******************************************/
class QSimpleExcel{
public:
	QSimpleExcel(QString const& fileName, QString const& sheetName);//创建带有sheet的excel文件
	QSimpleExcel(QString const& fileName, uint sheetIndex=0); //打开excel文件,不带文件名后缀
public:
	/**********sheet相关方法************/
	bool addSheet(QString const& sheetName);	//添加一个sheet，并将当前工作sheet=新添加sheet
	bool insertSheet(uint index, QString const& sheetName); //插入一个sheet，并将当前工作sheet=插入sheet
	libxl::Sheet* setSheet(int index);		//将工作sheet设置为index
	bool deleteSheet(uint index);	//将sheet srcIndex 插入 sheet destIndex之前
public:
	/***********************************
	* 功能：向当前工作的sheet中写入数据
	* 参数：row：行（0开始）； col：列；item：待写入内容
	* 返回值：是否写入成功
	* 作者：caokexiang
	* 日期：20240526
	**********************************/
	bool write(uint row, uint col, QString item);
	bool writeRed(uint row, uint col, QString item); //字体颜色为红色
	bool writeRow(uint row, uint col, QStringList items); // (row, col)开始行写入
	bool writeCol(uint row, uint col, QStringList items); // （row， col）开始列写入
	int getRows(); //已使用的行数
	int getCols();

	QString read(uint row, uint col); //读取数字或者文本


private:
	QString bookName; //excel文件名
	libxl::Book* book;	//excel对象
	libxl::Sheet* sheet; //当前工作的sheet


};
#endif