//
//  main.cpp
//  PgAndC
//
//  Created by Diego Cristobal Navia Fuentes on 11-11-13.
//  Copyright (c) 2013 Diego Cristobal Navia Fuentes. All rights reserved.
//


/*   Se debe instalar la libreria lidpq */
//Agregar al proyecto la liberaria libpq.5.5.dylib , se encuentra en la carpeta del proyecto PgAndC


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


    
    if (PQstatus(conn) != CONNECTION_BAD)    //Verifica la conexion con la Base datos
    {
        res = PQexec(conn, "select * from cursos"); //funcion que contiene la conexion y consulta a la BD
        
        if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res))  //PQresultStatus() retornaa el resultado de la consulta
        {
            for (i = PQntuples(res)-1; i >= 0; i--)
            {
                for (j = PQnfields(res)-1; j >= 0; j--)
                    cout<<PQgetvalue(res,i,j)<<endl;
                c++;
                
                printf("\n");
            }
            PQclear(res);
        }
    }
    
    cout<<"Cantidad :"<<c<<endl;
    
    PQfinish(conn);
    return 0;
}

