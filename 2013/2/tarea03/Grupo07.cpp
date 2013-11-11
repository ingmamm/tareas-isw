 

 * Author: Juan C Perez y Carla Arteaga
 *
 * Created on 11 de noviembre de 2013, 06:10 PM
 */

#include <iostream>
#include "libpq-fe.h"  //Libreria de conexion -> Linkear donde se encuentran instaladas antes de importar(include)

#include <stdio.h>      

using namespace std;

int main(int argc, const char * argv[])
{

    PGconn *conn;
    PGresult *res;
    int i,j;
    int c=0;
   
    
    conn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");// Esta funcion contiene la conexion con los parametros Ingresar(NombreHost,Puerto,NULL,NULL,NombreBasedatos,Usuario,Contraseña)

    if (PQstatus(conn) != CONNECTION_BAD) {
        cout << "Estamos conectados a PostgreSQL!" << endl;
        
        
        res = PQexec(conn, "select distinct A.estudiante_id,A.nota,B.asignatura from isw.asignaturas_cursadas A,isw.cursos B  where estudiante_id = 'argv[1]'");
        if (res != NULL) {
            int tuplas = PQntuples(res);
            int campos = PQnfields(res);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Campos:" << campos << endl;
            cout << "Los nombres de los campos son:" << endl;
            for (i=0; i<campos; i++) {
                cout << PQfname(res,i) << " | ";
            }
            cout << endl << "Contenido de la tabla" << endl;
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(res,i,j) << " | ";
                }
                cout << endl;
            }
        }
        // Ahora nos toca liberar la memoria
        PQclear(res);
    } else {
        cout << "Error de conexion" << endl;
        return 0 ;
    }
    PQfinish(conn);
    return 0;
}
