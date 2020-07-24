#include <stdio.h>
#include <sqlite3.h> 

int createAndPopulateTable(sqlite3 *db);
int createTableFriends(sqlite3 *db);
void getCarById(sqlite3 *db);

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   //sqlite3_close(db);

   //createAndPopulateTable(db);
   //createTableFriends(db);
   getCarById(db);
}

int createAndPopulateTable(sqlite3 *db) {
    
    char *err_msg = 0;

    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    char *sql = "DROP TABLE IF EXISTS Cars;" 
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    // sqlite3_close(db);
    
    return 0;
}

int createTableFriends(sqlite3 *db) {
    char *err_msg = 0;
    
    int rc;
    //int rc = sqlite3_open(":memory:", &db);
    
    char *sql = "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);"
    "INSERT INTO Friends(Name) VALUES ('Tom');"
    "INSERT INTO Friends(Name) VALUES ('Rebecca');"
    "INSERT INTO Friends(Name) VALUES ('Jim');"
    "INSERT INTO Friends(Name) VALUES ('Roger');"
    "INSERT INTO Friends(Name) VALUES ('Robert');";
        
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        
    } else {
        
        fprintf(stdout, "Table Friends created successfully\n");
    }
    
    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);

    sqlite3_close(db);
    
    return 0;
}

void getCarById(sqlite3 *db) {
   char *err_msg = 0;
   sqlite3_stmt *res;
   
   int rc;
   
   char *sql = "SELECT Id, Name FROM Cars WHERE Id = ?";
      
   rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
   
   if (rc == SQLITE_OK) {
      
      sqlite3_bind_int(res, 1, 3);
   } else {
      
      fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
   }
   
   int step = sqlite3_step(res);
   
   if (step == SQLITE_ROW) {
      
      printf("%s: ", sqlite3_column_text(res, 0));
      printf("%s\n", sqlite3_column_text(res, 1));
      
   } 

   sqlite3_finalize(res);
   sqlite3_close(db);
   
}
