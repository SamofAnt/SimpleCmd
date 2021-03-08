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
		// ������� ����������� ������������
		// ��� ������� - ������ �������
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

	// ������
	void set_command(std::string line) { if (line.length()) this->_command_line = line; }

	/*	<summary> ��������� ���������� ������ </summary>
		<returns></returns> */

	void Execute()
	{
		if (!_command_line.length()) throw std::invalid_argument(this->_class_name + ": ������ �������");

		// �������� ����������
		std::string cmd;
		std::string lha;
		std::string rha;

		// ������ ������
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
		// ����� �������� � ������� � �������� ���������� 
		// � ����� �������� � ������ �������
		if (this->_un_cmd_map.find(cmd) != this->_un_cmd_map.end())
			_un_cmd_map.at(cmd)->Execute(lha);
		// ����� �������� � ������� � ��������� ���������� 
		// � ����� �������� � ������ �������
		if (this->_bin_cmd_map.find(cmd) != this->_bin_cmd_map.end())
			_bin_cmd_map.at(cmd)->Execute(lha, rha);
	}

private:
	/*	<summary> ������� ��������� ������. </summary>

		<param name="line"> ��������������� ������. </param>
		<param name="cmd"> ���� ����� �������� ��� ��������. </param>
		<param name="lha_p"> ���� ����� ������� ������ �������� ������ (��� �������). </param>
		<param name="rha_p"> ���� ����� ������� ������ �������� ������ (��� �������). </param>

		<returns></returns> */
	void Parse(std::string & line
		, std::string & cmd
		, std::string & lha_p
		, std::string & rha_p)
	{
		// ������������ ����������� ��������� ������� ��������
		// ���������������� ���������� �� ���������
		cmd = "";
		lha_p = "";
		rha_p = "";

		if (!line.length()) return;

		// split ������ - ��������� �� �� ��������� �� �����
		std::vector <std::string> split_v;
		// ������� - ������������� ������ � ����������� ������
		char buffer[_BUFF_SIZE_];
		int it = 0;
		for (auto & ch : line)
			buffer[it++] = ch;

		buffer[it] = '\0';

		// ������� � ����� �� ������
		char * token = strtok(buffer, " ");
		while (token != NULL)
		{
			// ����� ���������� � ������
			split_v.push_back(token);
			token = strtok(NULL, " ");
		}
		
		// ������� ��������
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