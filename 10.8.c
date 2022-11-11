#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int DNI;
    char NOMBRE[21];
    int ESTADO;
}inscriptos;

typedef struct
{
    int TEL;
    int DNI;
    char NOMBRE[21];
}interesados;

int descargarARCH(inscriptos vec[]);//carga el vector, y devuelve la cantidad de casillas vacias

int buscarDNI(inscriptos vec[],int,int);//busca el DNI y devuelve 0 si no pago, 1 si esta pago, 2 si no exciste

void cargarINS(inscriptos vec[]);//reescribe el file

void cargarINT();//ingresa el DNI, NOMBRE Y TEL

int main()
{
    inscriptos INS[60];
    int vacias,estado,dni;
    vacias=descargarARCH(INS);
    scanf("%d",&dni);
    while(dni<0)
    {
        estado=buscarDNI(INS,dni,vacias);
        if(estado==2)
        {
            if(vacias!=0)
            {
                printf("\nINGRESAR DNI:");
                scanf("%d",INS[60-vacias].DNI);
                printf("\nINGRESAR NOMBRE:");
                gets(INS[60-vacias].NOMBRE);
                INS[60-vacias].ESTADO=0;
            }
            else
            {
                cargarINT();
            }           
        }
        scanf("%d",&dni);
    }
    cargarINS(INS);
    return 0;
}

int descargarARCH(inscriptos vec[])
{
    FILE *Ar;
    int i=0;
    Ar=fopen("INSCRIPTOS.dat","rb");

    if(Ar==NULL)
    {
        printf("\nArchivo INSCRITOS.dat no existente");
        getch();
        exit(1);
    }
    fread(&vec[i],sizeof(inscriptos),1,Ar);
    while(!feof(Ar))
    {
        i++;
        fread(&vec[i],sizeof(inscriptos),1,Ar);
    }

    fclose(Ar);

    return 60-i;

}

int buscarDNI(inscriptos vec[],int DNI,int MAX)
{
    char preg;
    int flag=2;
    for(int i=0;i<MAX;i++)
    {
        if(vec[i].DNI==DNI)
        {
            flag=1;
            if(vec[i].ESTADO==0)
            {
                flag=0;
                printf("\nDesea registrar el pago? S/N");
                fflush(stdin);
                scanf("%c",&preg);
                if(preg=='S')
                {
                    flag=1;
                    vec[i].ESTADO=1;
                }
            }

        }
    }
    return flag;

}

void cargarINT()
{
    interesados INFO;
    FILE* Ad;
    Ad=fopen("INTERESADOS.dat","ab");
    if(Ad==NULL)
    {
        printf("\nArchivo INTERESADOS.dat no se creo correctamente");
        getch();
        exit(1);
    }

    printf("\nINGRESAR TEL:");
    scanf("%d",INFO.TEL);
    printf("\nINGRESAR DNI:");
    scanf("%d",INFO.DNI);
    printf("\nINGRESAR NOMBRE:");
    gets(INFO.NOMBRE);
    fwrite(&INFO,sizeof(interesados),1,Ad);
    fclose(Ad);
}

void cargarINS(inscriptos vec[])
{
    FILE *Aw;
    int i=0;
    Aw=fopen("INSCRIPTOS.dat","wb");

    if(Aw==NULL)
    {
        printf("\nArchivo INSCRITOS.dat no se pudo crear");
        getch();
        exit(1);
    }
    fwrite(&vec[i],sizeof(inscriptos),1,Aw);
    while(!feof(Aw))
    {
        i++;
        fwrite(&vec[i],sizeof(inscriptos),1,Aw);
    }
    fclose(Aw);
}