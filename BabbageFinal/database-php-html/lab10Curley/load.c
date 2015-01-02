#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

int main(int argc, char** argv)
{
	//makes sure user inputs correct number of inputs
  if(argc != 4)
    {
      fprintf(stderr, "USAGE: %s <database file> <table name> <CSV file>\n", argv[0]);
      return 1;
    }
	//Open database and exit if failed
	sqlite3 *db;
	int rc;
	rc = sqlite3_open(argv[1], &db);
	if(rc) {
			printf("Failed to open database: %s", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
	}
	
	//Perform precurser delete
	sqlite3_stmt *sqlstate;
	char query[500] = "DELETE FROM ";
	strcat(query, argv[2]);
	strcat(query, ";");
	//prepare the query and execute if prepared without error
	if (sqlite3_prepare_v2(db, query, -1, &sqlstate, 0) == SQLITE_OK) {
		sqlite3_step(sqlstate);
	}
	else{
		printf("Failed: %s\n", sqlite3_errmsg(db));
	}
	//Open file and use fgets to read in whole line from csv file
	FILE *f_point = fopen(argv[3], "r");
	int num, i, scan_suc;
	char tempStr[500];
	while(fgets(tempStr, 500, f_point) != NULL){
		//For each line, use insert query to insert info
		char query2[500] = "INSERT INTO ";
		strcat(query2, argv[2]);
		strcat(query2, " VALUES(");
		strcat(query2, tempStr);
		strcat(query2, ");");
		//If prepare statement is valid, use step to execute query on table
		if (sqlite3_prepare_v2(db, query2, -1, &sqlstate, 0) == SQLITE_OK) {
			sqlite3_step(sqlstate);
		}
		else{
			printf("Failed: %s\n", sqlite3_errmsg(db));
		}
	}
	
	sqlite3_finalize(sqlstate);
	fclose(f_point);
	sqlite3_close(db);

  return 0;
}
