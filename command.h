#pragma once
#include "Header.h"

/* --------- ������� ��� ������ � ������� */
// ������� �������� �����
class CreateFileCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string path) const override { return cmd_create_file(path); }
	void Help() const override {
		std::cout << "crf [�������� �����]\t" << " �������� �����\n";
	}
private:
	static bool cmd_create_file(std::string path) {
		try
		{
			if (_creat(path.c_str(), S_IREAD | _S_IWRITE) == -1) throw std::invalid_argument("�� ������� ������� ����, ��������, �� ��� ����������\n");
			return  _creat(path.c_str(), S_IREAD | _S_IWRITE);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}
};
// ������� �������������� �����
class RenameFileCommand
	: public IBinaryFileCommand
{
public:
	bool Execute(std::string old_name, std::string new_name) const override { return cmd_rename_file(old_name, new_name); }
	void Help() const override {
		std::cout << "rnf [������ �������� �����] [����� �������� �����] ������������� ����\n";
	}
private:
	static bool cmd_rename_file(std::string old_name, std::string new_name){
	try
	{
		if (rename(old_name.c_str(), new_name.c_str())) throw std::invalid_argument("�� ������� ������������� ����\n");
		return !rename(old_name.c_str(), new_name.c_str());
	}
	catch (const std::exception&e)
	{
		std::cerr << e.what();
	}
	}
};

// ������� �������� �����
class RemoveFileCommand
	: public IUnaryFileCommand
{
public:
	bool Execute(std::string path) const override { return cmd_remove_file(path); }
	void Help() const override {
		std::cout << "rmf [�������� �����]\t" << "������� ����\n";
	}
private:
	static bool cmd_remove_file(std::string path) {
	try
	{
		if (remove(path.c_str())) throw std::invalid_argument("�� ������� ������� ����\n");
		return !remove(path.c_str());
	}
	catch (const std::exception&e)
	{
		std::cerr << e.what();
	}
	}
};
//������� ����������� �����
class MoveFileCommand : public IBinaryFileCommand {
public:
	bool Execute(std::string from, std::string to) const override { return cmd_move_file(from, to); }
	void Help()const override {
		std::cout << "mvf [������ ���� � �����] [����� ���� � �����]\t" << "��������� ����\n";
	}
private:
	static bool cmd_move_file(std::string from, std::string to) {
	try
	{
		if (!MoveFileEx(from.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING)) throw std::invalid_argument("�� ������� ����������� ��������� ����\n");
		return MoveFileEx(from.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING);
	}
	catch (const std::exception&e)
	{
		std::cerr << e.what();
	}
	}
};
// ������� ����������� �����
class CopyFileCommand :public IBinaryFileCommand {
public:
	bool Execute(std::string from, std::string to) const override { return cmd_copy_file(from, to); }
	void Help() const override {
		std::cout << "�pyf [������ ���� � �����] [����� ���� � �����]\t" << "����������� ����\n";
	}
private:
	static bool cmd_copy_file(std::string from, std::string to) {
	try
	{
		if (!CopyFile(from.c_str(), to.c_str(), FALSE)) throw std::invalid_argument("�� ������� ����������� ��������� ����\n");
		return CopyFile(from.c_str(), to.c_str(), FALSE);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	}
};
// ������� ����
class OpenFileCommand : public IUnaryFileCommand {
public:
	bool Execute(std::string directory)const override { return cmd_open_file(directory); }
	void Help() const override {
		std::cout << "run [���� � �����]\t" << "������� ����";
	}
private:
	static bool cmd_open_file(std::string directory) {
		system(directory.c_str());
		return true;
	}
};
// ������������� ����
class EditFileCommand : public IUnaryFileCommand {
public:
	bool Execute(std::string path)const override { return cmd_edit_file(path); }
	void Help()const override {
		std::cout << "edit [�������� �����]\t" << "�������������� ������\n";
	}
private:
	static bool cmd_edit_file(std::string path) {
		try
		{
			if (path.substr(path.find_last_of(".") + 1) != "txt") throw std::invalid_argument("���� � ����������� �� .txt");
			std::ofstream txt_ostr;
			txt_ostr.open(path, std::ofstream::out | std::ofstream::trunc);
			try
			{
				if (!txt_ostr.is_open()) throw std::invalid_argument("������ �������� �����");

				std::cout << "������ ����: " << path << "." << std::endl;
				std::string text;
				std::cin >> text;
				std::cout << "���������� �������." << std::endl;

				txt_ostr << text << std::endl;

				std::cout << "�������� �����..." << std::endl;
				txt_ostr.close();

				std::cout << "������ ����: " << path << "." << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << e.what();
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
		return true;
	}
};
// ������� � �����
class ReadFileCommand : public IUnaryFileCommand {
public:
	bool Execute(std::string path) const override { return cmd_read_file(path); }
	void Help() const override {
		std::cout << "read [�������� �����]\t" << "���������� ������\n";
	}
private:
	static bool cmd_read_file(std::string path) {
		try
		{
			if (path.substr(path.find_last_of(".") + 1) != "txt") throw std::invalid_argument("���� ������ ����� ���������� txt\n");
			std::vector <std::string> txt_vector;
			std::ifstream txt_istr;
			txt_istr.open(path);
			try
			{
				if (!txt_istr.is_open()) throw std::invalid_argument("������ �������� �����\n");
				std::cout << "������ ����: " << path << "." << std::endl;
				std::cout << "������ ������..." << std::endl;

				std::string current_str;
				while (!txt_istr.eof())
				{
					current_str = "";
					std::getline(txt_istr, current_str);
					txt_vector.push_back(current_str);
				}
				txt_istr.close();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			std::cout << std::endl;
			for (auto& str : txt_vector)
				std::cout << str << "\n";
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
		return true;
	}
};

/* --------- ������� ��� ������ � ������������ */

// ������� ����������
class RemoveDirCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string path)const override { return cmd_dir_remove(path); }
	void Help() const override {
		std::cout << "rmd [�������� �����]\t" << "������� ����������\n\n";
	}
private:
	static bool cmd_dir_remove(std::string path) {
		try
		{
			if (_rmdir(path.c_str()) == -1) throw std::invalid_argument("�� ������� ������� ����������\n");
			return _rmdir(path.c_str()) != -1;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}
};
// ������� ����������
class CreateDirCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string path)const override { return cmd_create_dir(path); }
	void Help() const override {
		std::cout << "crd [�������� �����]\t" << "������� ����������\n";
	}
private:
	static bool cmd_create_dir(std::string path) {
		try
		{
			if (_mkdir(path.c_str()) == -1) throw std::invalid_argument("�� ������� ������� ����������\n");
			return _mkdir(path.c_str()) != -1;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	};
};
// ������������� ����������
class RenameDirCommand : public IBinaryFileCommand {
public:
	bool Execute(std::string old_name, std::string new_name) const override { return cmd_dir_rename(old_name, new_name); }
	void Help()const override {
		std::cout << "rnd [������ �������� ����������] [����� �������� ����������] ������������� ����������\n";
	}
private:
	static bool cmd_dir_rename(std::string old_name, std::string new_name) {
	try
	{
		if (rename(old_name.c_str(), new_name.c_str())) throw std::invalid_argument("�� ������� ������������� ����������\n");
		return !rename(old_name.c_str(), new_name.c_str());
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	}
};
//����������� ����������
class CopyDirCommand : public IBinaryFileCommand {
public:
	bool Execute(std::string old_dir, std::string new_dir)const override { return cmd_dir_copy(old_dir, new_dir); }
	void Help() const override {
		std::cout << "cpyd [������ ����������] [����� ����������] ���������� ����������\n";
	}
private:
	static bool cmd_dir_copy(std::string old_dir, std::string new_dir) {
		std::experimental::filesystem::copy(old_dir, new_dir);
		return true;
	}
};

//����������� ����������
class MoveDirCommand :public IBinaryFileCommand {
public:
	bool Execute(std::string old_dir, std::string new_dir)const override { return cmd_dir_move(old_dir, new_dir); }
	void Help() const override {
		std::cout << "mvd [������] [����] ����������� ����������\n";
	}
private:
	static bool cmd_dir_move(std::string old_dir, std::string new_dir) {
		std::experimental::filesystem::copy(old_dir, new_dir);
		std::experimental::filesystem::remove_all(old_dir);
		return true;
	}
};
//������� ������ �����������
class ShowDirCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string directory)const override { return cmd_show(directory); }
	void Help() const override {
		std::cout << "show [����]\t" << " ����� ����������� ������� ����������\n";
	}
private:
	static bool cmd_show(std::string directory) {
		setlocale(LC_ALL, "");

		_finddata_t* fileinfo = new _finddata_t;

		directory += "\\*";

		intptr_t done = _findfirst(directory.c_str(), fileinfo);
		intptr_t exit_flag = done;

		while (exit_flag != -1)
		{
			if (strcmp(fileinfo->name, ".") && strcmp(fileinfo->name, ".."))
				std::cout << "\t" << fileinfo->name << ": " << (fileinfo->attrib == _A_SUBDIR ? "DIRECTORY" : "FILE") << std::endl;
			exit_flag = _findnext(done, fileinfo);
		}

		_findclose(done);

		delete fileinfo;
		return true;
	}
};
// ������� ������ ����������� �� ����� ����������
class ShowTreeDirCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string directory)const override { return cmd_show_tree(directory); }
	void Help() const override {
		std::cout << "crf [�������� �����]\t" << " �������� �����\n";
	}
private:
	static bool cmd_show_tree(std::string directory) {
		while (directory.find("\\") != -1) {
			ShowDirCommand sd;
			std::cout << "\t";
			sd.Execute(directory);
			directory = directory.substr(0, directory.find_last_of("\\"));
			SetCurrentDirectory(directory.c_str());
			std::shared_ptr<char> b_ptr(strcpy(new char[directory.length() + 1], directory.c_str()));
			GetCurrentDirectory(directory.length(), b_ptr.get());
			cmd_show_tree(directory);
		}
		return true;
	}
};
// ������� ��� ����� ������� ����������
class ChangeDirCommand :public IUnaryFileCommand {
public:
	bool Execute(std::string directory)const override { return cmd_change_dir(directory); }
	void Help() const override {
		std::cout << "cd [���� ����� ����������]\t" << "����� ������� ����������\n";
	}
private:
	static bool cmd_change_dir(std::string directory) {
		setlocale(LC_ALL, "");
		/*DWORD dw = GetCurrentDirectory(0, NULL);
		TCHAR* _buffer = new TCHAR[dw];
		GetCurrentDirectory(dw, _buffer);
		size_t i = 0;
		for (auto it = directory.begin(); it != directory.end(); it++)
			_buffer[i++] = *it;
		_buffer[i] = '\0';*/
		try
		{
			if (!SetCurrentDirectory(directory.c_str())) throw std::invalid_argument("������, ������� �� ������� ����� ��������� ����, �������� ���� ����������\n");
			SetCurrentDirectory(directory.c_str());
		//	std::shared_ptr<char> b_ptr(strcpy(new char[directory.length() + 1], directory.c_str()));
		//	GetCurrentDirectory(directory.length(), b_ptr.get());
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what();
		}
		return true;
	}
};

/* --------- ������� ��� ������ � �������� */
// ������� �������
class ClearCommand :public INoneFileCommand {
public:
	bool Execute()const override { return cmd_clear(); }
private:
	static bool cmd_clear() { system("cls"); return true; }
};
//�����
class ExitCommand :public INoneFileCommand {
public:
	bool Execute()const override { return cmd_exit(); }
private:
	static bool cmd_exit() { exit(0); return true; }
};
//������� �������� ������
class HelpCommand : public INoneFileCommand {
public:
	bool Execute()const override { return cmd_help(); }
private:
	static bool cmd_help() {
		setlocale(LC_ALL, "Rus");
		std::cout << "crf  " << "�������� �����\n";
		std::cout << "rnf  " << "������������� ����\n";
		std::cout << "rmf  " << "������� ����\n";
		std::cout << "mvf  " << "��������� ����\n";
		std::cout << "�pyf " << "����������� ����\n";
		std::cout << "edit " << "��������������\n";
		std::cout << "run  " << "�������� �����\n";
		std::cout << "read " << "���������� ������\n\n";

		std::cout << "show " << "����� ����������� ������� ����������\n";
		std::cout << "tree " << "����� ����������� �� ����� ���������� ���������� ������� ����������\n";
		std::cout << "crd  " << "������� ����������\n";
		std::cout << "rnd  " << "������������� ����������\n";
		std::cout << "cpyd " << "���������� ����������\n";
		std::cout << "mvd  " << "����������� ����������\n";
		std::cout << "rmd  " << "������� ����������\n\n";

		std::cout << "cd   " << "����� ������� ����������\n";
		std::cout << "help " << "������� ���������� ���������� � ��������\n";
		std::cout << "exit " << "�����\n";
		std::cout << "clr  " << "������� �������\n";
		return true;
	}
};

class CreateVarCommand {
public:
private:

};