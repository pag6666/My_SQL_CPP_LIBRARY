#include "library/sqlite3.h"
#include <string>

#include <vector>
#include<iostream>

class SQLConnection
{
private:
	sqlite3* _database;
	bool is_open;
	bool is_execute;
	sqlite3_stmt* _stmt;
	char* errMessage;
public:
	SQLConnection()
	{

	}
	SQLConnection(const char* nameDataBase)
	{
		int rc = sqlite3_open(nameDataBase, &_database);
		if (rc)
		{
			is_open = false;
		}
		else
		{
			is_open = true;
		}
	}
	void Open(const char* nameDataBase)
	{
		int rc = sqlite3_open(nameDataBase, &_database);
		if (rc)
		{
			is_open = false;
		}
		else
		{
			is_open = true;
		}
	}
	void Execute(const char* command)
	{
		int rc = sqlite3_exec(SQLConnection::_database, command, NULL, NULL, &errMessage);
		if (rc == SQLITE_OK)
		{
			is_execute = true;
		}
		else
		{
			is_execute = false;
		}
	}
	
	std::string GetColumnName(int column)
	{
		
		return sqlite3_column_name(_stmt, column);
	}
	std::vector<int> ExecuteReadInt(const char* command, int column)
	{
		std::vector<int> result;
		sqlite3_prepare_v2(_database, command, -1, &_stmt, 0);
		while (sqlite3_step(_stmt) != SQLITE_DONE) {
			result.push_back(sqlite3_column_int(_stmt, column));
		}
		return result;
	}
	std::vector<double> ExecuteReadDouble(const char* command, int column)
	{
		std::vector<double> result;
		sqlite3_prepare_v2(_database, command, -1, &_stmt, 0);
		while (sqlite3_step(_stmt) != SQLITE_DONE) {
			result.push_back(sqlite3_column_int(_stmt, column));
		}
		return result;
	}
	std::vector<std::string> ExecuteReadText(const char* command, int column)
	{
		std::vector<std::string> result;
		sqlite3_prepare_v2(_database, command, -1, &_stmt, 0);
		while (sqlite3_step(_stmt) != SQLITE_DONE) {
			std::string text("null");
			text = (const char *)sqlite3_column_text(_stmt, column);
			result.push_back(text);
			
		}
		
		return result;
	}
	
	~SQLConnection()
	{
		sqlite3_close(_database);
	}
};
