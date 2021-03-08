#pragma once
#include "executer.h"

class Client {
	Executer* _executer;
	TCHAR *_dir;
	DWORD size;
	void Menu(std::string line) {
		
	}
public:
	Client() :_executer{ new Executer }, size{ GetCurrentDirectory(0, NULL) }, _dir{ new TCHAR[size] } {}
	~Client() {
		delete _executer; delete[] _dir;
	}
	void Run() {
		setlocale(LC_ALL, "");
	/*	std::string cmd_line = "";
		std::shared_ptr<char> b_ptr(strcpy(new char[_dir.length() + 1], _dir.c_str()));
		GetCurrentDirectory(sizeof(_dir), b_ptr.get());

		while (cmd_line != "exit") {
			GetCurrentDirectory(sizeof(_dir), b_ptr.get());
			std::cout << _dir << '>';
			std::getline(std::cin, cmd_line);
			if (cmd_line.size()) {
				_executer->set_command(cmd_line);
				_executer->Execute();
			}
		}*/
		std::string cmd_line = "";
		strcpy(_dir, "C:\\Users");
		SetCurrentDirectory(_dir);
		while (cmd_line != "exit") {
			GetCurrentDirectory(size, _dir);
			std::cout << _dir << '>';
			std::getline(std::cin, cmd_line);
			if (cmd_line.size()) {
				_executer->set_command(cmd_line);
				_executer->Execute();
			}
		}

	}
};