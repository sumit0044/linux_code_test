#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main() {
  MYSQL my_connection;
  MYSQL_RES *res_ptr;
  MYSQL_ROW sqlrow;
  int res, i;
  
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection,
						 "localhost",
						 "proxy",
						 NULL,
						 "LETENO_DB",
						 0,
						 NULL,
						 0)){
	printf("Connection success\n");

	res = mysql_query(&my_connection,
					  "INSERT INTO student (sname, age) values ('new', 17)");
	if (!res) {
	  printf("Inserted %lu rows\n",
			 (unsigned long)mysql_affected_rows(&my_connection));
	} else {
	  fprintf(stderr, "Insert error %d: %s\n",
			  mysql_errno(&my_connection),
			  mysql_error(&my_connection));
	}
	
  } else {
	fprintf(stderr, "Connection failed\n");
	if (mysql_errno(&my_connection)){
	  fprintf(stderr, "Connection error %d: %s\n",
			  mysql_errno(&my_connection),
			  mysql_error(&my_connection));
	}
  }

  res = mysql_query(&my_connection, "SELECT LAST_INSERT_ID()");
  printf("res is %d\n", res);
  if (res) {
	printf ("SELECT error: %s\n",mysql_error(&my_connection));
  } else {
	res_ptr = mysql_use_result(&my_connection);
	if (res_ptr) {
	  while((sqlrow = mysql_fetch_row(res_ptr))) {
		printf("We inserted childno %s\n", sqlrow[0]);
	  }
	  mysql_free_result(res_ptr);
	}
  }
  mysql_close(&my_connection);
  
  return EXIT_SUCCESS;
}
