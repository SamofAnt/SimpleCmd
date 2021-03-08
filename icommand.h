#pragma once

#include <string>

/* хмрептеия дкъ йнлюмд я ндмхл юцпслемрнл (ноепюмднл) */

struct IUnaryFileCommand
{
	virtual bool Execute(std::string) const = 0;
	virtual void Help() const = 0;
	virtual ~IUnaryFileCommand() = default;
};

/* хмрептеия дкъ йнлюмд я дбслъ юцпслемрюлх */

struct IBinaryFileCommand
{
	virtual bool Execute(std::string, std::string) const = 0;
	virtual void Help() const = 0;
	virtual ~IBinaryFileCommand() = default;
};
/* хмрептеия дкъ йнлюмд аег юпцслемрнб */
struct INoneFileCommand {
	virtual bool Execute() const = 0;
	virtual ~INoneFileCommand() = default;

};