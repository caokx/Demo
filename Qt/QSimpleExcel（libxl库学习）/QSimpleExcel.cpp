#include "QSimpleExcel.h"

QSimpleExcel::QSimpleExcel(QString const& bookName, QString const& sheetName){
	//QString转到wchar_t const*
	this->bookName = bookName + ".xls";
	std::wstring name1 = this->bookName.toStdWString();
	const wchar_t* bookName_ = name1.c_str();
	std::wstring name2 = sheetName.toStdWString();
	const wchar_t* sheetName_ = name2.c_str();
	//创建excel文件
	book = xlCreateBook();		//book对象
	sheet = book->addSheet(sheetName_); //不添加表单excel文件无法打开
	book->save(bookName_);	//保存excel文件
	//book->release();	//释放资源，删除对象
	//book = nullptr;
}
QSimpleExcel::QSimpleExcel(QString const& bookName, uint sheetIndex) {
	//QString转到wchar_t const*
	this->bookName = bookName + ".xls";
	std::wstring name = this->bookName.toStdWString();
	const wchar_t* fileName_ = name.c_str();
	book = xlCreateBook();
	if (!book->load(fileName_)) {
		qDebug() << QString::fromLocal8Bit("加载Excel文件失败");
	}
	else {
		sheet = book->getSheet(sheetIndex);
	}
	//book->release();	//释放资源，删除对象
	//book = nullptr;
}
bool QSimpleExcel::addSheet(QString const& sheetName) {
	bool flag = false;
	std::wstring name1 = this->bookName.toStdWString();
	const wchar_t* fileName_ = name1.c_str();
	std::wstring name2 = sheetName.toStdWString();
	const wchar_t* sheetName_ = name2.c_str();


	sheet = book->addSheet(sheetName_);
	if (sheet) {
		flag = true;
		book->save(fileName_);
	}
	return flag;
}
bool QSimpleExcel::insertSheet(uint index, QString const& sheetName) {
	bool flag = false;
	std::wstring name1 = this->bookName.toStdWString();
	const wchar_t* fileName_ = name1.c_str();
	std::wstring name2 = sheetName.toStdWString();
	const wchar_t* sheetName_ = name2.c_str();

	sheet = book->insertSheet(index, sheetName_);

	if (flag) {
		flag = true;
		book->save(fileName_);
	}
	return flag;
}
libxl::Sheet* QSimpleExcel::setSheet(int index) {
	return book->getSheet(index);
}
bool QSimpleExcel::deleteSheet(uint index) {
	bool flag = book->delSheet(index);
	if (flag) {
		std::wstring name1 = this->bookName.toStdWString();
		const wchar_t* fileName_ = name1.c_str();
		book->save(fileName_);
	}
	return flag;
}

bool QSimpleExcel::write(uint row, uint col, QString item) {
	std::wstring tmp = item.toStdWString();
	const wchar_t* item_ = tmp.c_str();
	bool flag = sheet->writeStr(row, col, item_);
	if (flag) {
		std::wstring name1 = this->bookName.toStdWString();
		const wchar_t* fileName_ = name1.c_str();
		book->save(fileName_);
	}
	return flag;
}
bool QSimpleExcel::writeRed(uint row, uint col, QString item) {
	std::wstring tmp = item.toStdWString();
	const wchar_t* item_ = tmp.c_str();
	bool flag = sheet->writeStr(row, col, item_);
	if (true) {
		libxl::Format* formatRed = book->addFormat();
		libxl::Font* fontRed = book->addFont();
		fontRed->setColor(libxl::COLOR_RED);
		formatRed->setFont(fontRed);
		sheet->setCellFormat(row, col, formatRed);

		std::wstring name1 = this->bookName.toStdWString();
		const wchar_t* fileName_ = name1.c_str();
		book->save(fileName_);
	}
	return flag;
}
bool QSimpleExcel::writeRow(uint row, uint col, QStringList items) {
	for (int i = 0; i < items.size(); i++) {
		std::wstring tmp = items[i].toStdWString();
		const wchar_t* item_ = tmp.c_str();
		if (sheet->writeStr(row, col+i, item_)) {
			continue;
		}
		else {
			return false;
		}
	}
	std::wstring name1 = this->bookName.toStdWString();
	const wchar_t* fileName_ = name1.c_str();
	book->save(fileName_);
	return true;
}
bool QSimpleExcel::writeCol(uint row, uint col, QStringList items) {
	for (int i = 0; i < items.size(); i++) {
		std::wstring tmp = items[i].toStdWString();
		const wchar_t* item_ = tmp.c_str();
		if (sheet->writeStr(row+i, col, item_)) {
			continue;
		}
		else {
			return false;
		}
	}
	std::wstring name1 = this->bookName.toStdWString();
	const wchar_t* fileName_ = name1.c_str();
	book->save(fileName_);
	return true;
}
int QSimpleExcel::getRows() {
	return sheet->lastRow();
}
int QSimpleExcel::getCols() {
	return sheet->lastCol();
}
QString QSimpleExcel::read(uint row, uint col) {
	QString qs;
	libxl::CellType type = sheet->cellType(row, col);
	switch (type) {
	case libxl::CELLTYPE_NUMBER: {
		double itemNum = sheet->readNum(row, col);
		qs = QString::number(itemNum);
		break;
	}
	case libxl::CELLTYPE_STRING: {
		const wchar_t* itemStr = sheet->readStr(row, col);
		qs = QString::fromWCharArray(itemStr);
		break;
	}
	default: //blank、error、empty
		qs = "";
	}
	return qs;
}


