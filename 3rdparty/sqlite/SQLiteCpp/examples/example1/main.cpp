/**
 * @file  main.cpp
 * @brief A few short examples in a row.
 *
 *  Demonstrate how-to use the SQLite++ wrapper
 *
 * Copyright (c) 2012-2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <windows.h>

#include "../../src/SQLiteC++.h"


static const char* filename_db3 = "acu100.db3";

const std::string currentDateTime(time_t nTime) {
    time_t     now = nTime;
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

    return buf;
}

int main (void)
{
    try
    {
		SQLite::Database    db(filename_db3, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);  
		db.exec("CREATE TABLE DATA_COUNTER (ID INTEGER PRIMARY KEY, TIME_START DATE, \
TIME_END DATE, DEVICE INTEGER, IN_ INTEGER, OUT INTEGER)");
    }
    catch (std::exception& e)
    {
		std::cout << "SQLite exception: " << e.what() << std::endl;
    }
        
	char bufferInsert[2048];
	int i = 0;
	// Open a database file in readonly mode
	SQLite::Database    db(filename_db3, SQLITE_OPEN_READWRITE);  
	std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

        // Test if the 'test' table exists

		while(1){
			std::string strLastTime = currentDateTime(time(NULL) - 60 * 5);
			std::string strCurrentTime = currentDateTime(time(NULL));
			printf("Time Start %s End %s\n", strLastTime.c_str(), strCurrentTime.c_str());
			for (int j = 1; j <= 4; j ++)
			{
				sprintf(bufferInsert, "INSERT INTO DATA_COUNTER VALUES (NULL, \
					\"%s\", \"%s\", %d, %d, %d)", strLastTime.c_str(), strCurrentTime.c_str(), 
					j, i, i);
again:
				try
				{
					db.exec(bufferInsert);
				}
				catch (std::exception& e)
				{
					std::cout << "SQLite exception: " << e.what() << std::endl;
					Sleep(40);
					goto again;
				}
			}
			
			i ++;



			Sleep(1000 * 60 * 5);
		}
	

    return 0;
}
