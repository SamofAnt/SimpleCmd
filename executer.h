 #pragma once
#include "command.h"

#include <exception>
#include <map>

#define _BUFF_SIZE_ 1000

class Executer
{
public:
	Executer()
		: _command_line {""}, curr_directory{""}
	{
		// словари заполняются соответсиями
		// имя команды - объект команды
		this->_none_cmd_map =
		{
			{"clr", new ClearCommand},
			{"exit", new ExitCommand},
			{"help", new HelpCommand}
		};
		this->_un_cmd_map =
		{
			{"crf", new CreateFileCommand},
			{"rmf", new RemoveFileCommand},
			{"crd", new CreateDirCommand},
			{"rmd", new RemoveDirCommand},
			{"show", new ShowDirCommand},
			{"cd", new ChangeDirCommand},
			{"tree", new ShowTreeDirCommand},
			{"run", new OpenFileCommand},
			{"read", new ReadFileCommand},
			{"edit", new EditFileCommand}
		};
		this->_bin_cmd_map = {
			{"rnf", new RenameFileCommand},
			{"mvf", new MoveFileCommand},
			{"rnd", new RenameDirCommand},
			{"cpyf", new CopyFileCommand},
			{"cpyd", new CopyDirCommand},
			{"mvd", new MoveDirCommand}
		};
//		GetCurrentDirectory(sizeof(curr_directory), curr_directory.c_str());
	}
	
	~Executer()
	{
		for (auto el : _none_cmd_map)
			delete el.second;

		for (auto el : _un_cmd_map)
			delete el.second;

		for (auto el : _bin_cmd_map)
			delete el.second;
	}

	// сеттер
	void set_command(std::string line) { if (line.length()) this->_command_line = line; }

	/*	<summary> Обработка коммандной строки </summary>
		<returns></returns> */

	void Execute()
	{
		if (!_command_line.length()) throw std::invalid_argument(this->_class_name + ": пустая команда");

		// буферные переменные
		std::string cmd;
		std::string lha;
		std::string rha;

		// парсим строку
		Parse(this->_command_line, cmd, lha, rha);
			

		//std::shared_ptr<char> b_ptr(strcpy(new char[curr_directory.length() + 1], curr_directory.c_str()));
		//GetCurrentDirectory(curr_directory.length(), b_ptr.get());
		if ((cmd == "Help" || cmd == "help") && lha != "") {
			if (this->_un_cmd_map.find(lha) != this->_un_cmd_map.end())
				_un_cmd_map.at(lha)->Help();
			if (this->_bin_cmd_map.find(lha) != this->_bin_cmd_map.end())
				_bin_cmd_map.at(lha)->Help();
			return;
		}

		if (this->_none_cmd_map.find(cmd) != this->_none_cmd_map.end())
			_none_cmd_map.at(cmd)->Execute();
		// поиск комманды в словаре с унарными операциями 
		// и вызов комманды в случае наличия
		if (this->_un_cmd_map.find(cmd) != this->_un_cmd_map.end())
			_un_cmd_map.at(cmd)->Execute(lha);
		// поиск комманды в словаре с бинарными операциями 
		// и вызов комманды в случае наличия
		if (this->_bin_cmd_map.find(cmd) != this->_bin_cmd_map.end())
			_bin_cmd_map.at(cmd)->Execute(lha, rha);
	}

private:
	/*	<summary> Парсинг командной строки. </summary>

		<param name="line"> Непосредственно строка. </param>
		<param name="cmd"> Сюда будет записано имя комманды. </param>
		<param name="lha_p"> Сюда будет записан первый аргумент строки (при наличии). </param>
		<param name="rha_p"> Сюда будет записан второй аргумент строки (при наличии). </param>

		<returns></returns> */
	void Parse(std::string & line
		, std::string & cmd
		, std::string & lha_p
		, std::string & rha_p)
	{
		// возвращаемые посредством побочного эффекта значения
		// инициализируются значениями по умолчанию
		cmd = "";
		lha_p = "";
		rha_p = "";

		if (!line.length()) return;

		// split строки - разбиение ее на отдельные на слова
		std::vector <std::string> split_v;
		// костыль - перебрасываем строку в статический массив
		char buffer[_BUFF_SIZE_];
		int it = 0;
		for (auto & ch : line)
			buffer[it++] = ch;

		buffer[it] = '\0';

		// перебор в цикле по словам
		char * token = strtok(buffer, " ");
		while (token != NULL)
		{
			// слова помещаются в вектор
			split_v.push_back(token);
			token = strtok(NULL, " ");
		}
		
		// возврат значений
		size_t split_size = split_v.size();
		if (split_size > 0) cmd = split_v[0];
		if (split_size > 1) lha_p = split_v[1];
		if (split_size > 2) rha_p = split_v[2];
	}

private:

	std::map <std::string, IUnaryFileCommand *> _un_cmd_map;
	std::map <std::string, IBinaryFileCommand *> _bin_cmd_map;
	std::map <std::string, INoneFileCommand*> _none_cmd_map;
	std::string curr_directory;
	std::string _command_line;
	const std::string _class_name = "Executer";
};