#include "main_window.h"
#include "ui_main_window.h"
#include <QFileDialog>
#include <filesystem>
#include <iostream>
#include "libyanbt/nbtfile.h"
#include "libyanbt/nbtread.h"
#include "libyanbt/nbttag.h"

main_window::main_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::main_window){
	ui->setupUi(this);
}

main_window::~main_window(){
	delete ui;
}

void main_window::open_file(){
	std::filesystem::path fpath = QFileDialog::getOpenFileName(this).toStdString();
	std::cout << fpath << std::endl;
	nbtfile nbtf = read_nbt(fpath);
	std::cout << nbtf << std::endl;
}
