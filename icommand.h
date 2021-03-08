#pragma once

#include <string>

/* ��������� ��� ������ � ����� ���������� (���������) */

struct IUnaryFileCommand
{
	virtual bool Execute(std::string) const = 0;
	virtual void Help() const = 0;
	virtual ~IUnaryFileCommand() = default;
};

/* ��������� ��� ������ � ����� ����������� */

struct IBinaryFileCommand
{
	virtual bool Execute(std::string, std::string) const = 0;
	virtual void Help() const = 0;
	virtual ~IBinaryFileCommand() = default;
};
/* ��������� ��� ������ ��� ���������� */
struct INoneFileCommand {
	virtual bool Execute() const = 0;
	virtual ~INoneFileCommand() = default;

};