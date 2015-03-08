#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int parti_isimleri(int);
void il_bilgi_al();
void parti_ve_oy_sayisinin_siralanmasi(int [],char [],int);
void mil_kontenjanin_partilere_dagilimi(int [],char [],int ,int ,int []);
void Turkiye_genelini_yazdir(int ,int ,int ,int [],int [],int [],int []);
void illeri_yazdir(int,char [],int [],int ,int []);
void birinci_sifirinci_il_bul(int ,char [],int [],int [],int []);

int main()
{
    il_bilgi_al();

    return 0;
}
//-----------------------------------------------------------------------------------------
void il_bilgi_al()
{
    int parti_say,plaka_kodu,kontenjan,oy_say,i,toplam_oy=0,kontenjan_say=0,gecerli_oy=0,a;

    printf("Secime katilan parti sayisini giriniz: ");
    scanf("%d",&parti_say);
    while(parti_say>20){
    printf("En cok 20 parti katilabilecektir!!! \nSecime katilan parti sayisini giriniz: ");
    scanf("%d",&parti_say);
    }

    char karakter[parti_say-1],karakter_2[parti_say-1] ,max_birincilik,max_ikincilik;
    int kontenjan_dizi[parti_say-1],oy_dizisi[parti_say-1],parti_toplam_oy[parti_say-1];
    int toplam_parti_kontenjan[parti_say-1],birincilik_say[parti_say-1],sifirinci_il_say[parti_say-1];

    for(i=0; i<parti_say; i++)//ilkleme yapilarak sifir atanir...
    {
        parti_toplam_oy[i]=0;
        toplam_parti_kontenjan[i]=0;
        birincilik_say[i]=0;
        sifirinci_il_say[i]=0;
    }
    do
    {
        toplam_oy=0;

        printf("Ilin plaka kodunu giriniz: ");
        scanf("%d",&plaka_kodu);
        if(plaka_kodu>0)
        {
            printf("Ilin milletvekili kontenjanini giriniz: ");
            scanf("%d",&kontenjan);
            kontenjan_say+=kontenjan;

            for(i=0; i<parti_say; i++)
            {
                karakter[i]=parti_isimleri(i+1);
                printf("%c Partisi'nin oy sayisini giriniz: ",karakter[i]);
                scanf("%d",&oy_say);
                oy_dizisi[i]=oy_say;
                toplam_oy+=oy_say;
                parti_toplam_oy[i]+=oy_dizisi[i];
                gecerli_oy+=oy_say;
            }
            printf("Il Plaka Kodu: %d\n",plaka_kodu);
            printf("Milletvekili Kontenjani: %d\n",kontenjan);
            printf("Gecerli Oy Sayisi:  %d\n",toplam_oy);

            parti_ve_oy_sayisinin_siralanmasi(oy_dizisi,karakter,parti_say);
            mil_kontenjanin_partilere_dagilimi(oy_dizisi,karakter,parti_say,kontenjan,kontenjan_dizi);
            illeri_yazdir(parti_say,karakter,oy_dizisi,toplam_oy,kontenjan_dizi);
            birinci_sifirinci_il_bul(parti_say,karakter,birincilik_say,sifirinci_il_say,kontenjan_dizi);
            for(i=0; i<parti_say; i++)
            {
                for(a=0; a<parti_say; a++)
                {
                    karakter_2[a]=parti_isimleri(a+1);
                    if(karakter_2[a]==karakter[i])
                    {
                        toplam_parti_kontenjan[a]+=kontenjan_dizi[i];
                        if(birincilik_say[a]>birincilik_say[a+1])
                        {
                            max_birincilik=karakter_2[a];//iktidar partiyi atar...
                            max_ikincilik=karakter_2[a+1];//ana muhalefet partiyi atar...
                        }
                    }
                }
            }
        }
    }
    while(plaka_kodu!=0);//veri girisinin bittigini belirtmek icin plaka kodunu sifir giriniz...

    Turkiye_genelini_yazdir(parti_say,kontenjan_say,gecerli_oy, parti_toplam_oy,toplam_parti_kontenjan,birincilik_say,sifirinci_il_say);

    printf("Iktidar Partisi: %c Partisi\n",max_birincilik);
    printf("Ana Muhalefet partisi: %c Partisi",max_ikincilik);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------

void illeri_yazdir(int parti_say,char karakter[],int dizi[],int toplam_oy,int kont_dizi[]) //illerin istatistiksel bilgilerini yazdirir...
{
    int i;
    printf("\t Oy Say   Oy Yuzde   MV Say\n");
    printf("\t  ------  --------   -------\n");

    for(i=0; i<parti_say; i++)
    {
        printf("%c Partisi  %5d   %5.2f %7d\n",karakter[i],dizi[i],(float)dizi[i]*100/toplam_oy,kont_dizi[i]);
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
void Turkiye_genelini_yazdir(int parti_say,int kontenjan_say,int gecerli_oy,int parti_toplam_oy[],int toplam_kontenjan[],int birinci[],int sifirinci[])
{
    //Turkiye genelindeki istatistiksel bilgileri yazdirir.....
    char karakter[parti_say-1];
    int a;

    printf("***TURKIYE  GENELI***\n");
    printf("Milletvekili Kontenjani: %d\n",kontenjan_say);
    printf("Gecerli Oy Sayisi: %d\n",gecerli_oy);
    printf("\t Oy Say   Oy Yuzde   MV Say  MV Yuzde  Il 1.lik Say  0 MV Il Say\n");
    printf("\t  ------  --------   ------- --------  ------------  -----------\n");

    for(a=0; a<parti_say; a++)
    {
        karakter[a]=parti_isimleri(a+1);
        printf("%c Partisi %4d  %7.2f %10d %8.2f%10d%13d\n",karakter[a],parti_toplam_oy[a],(float)parti_toplam_oy[a]*100/gecerli_oy,toplam_kontenjan[a],(float)toplam_kontenjan[a]*100/kontenjan_say,birinci[a],sifirinci[a]);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
void birinci_sifirinci_il_bul(int parti_say,char karakter[],int birinci[],int sifirinci[],int kont_dizi[])
{
    int i,a;
    char karakter_2[parti_say-1] ;
    for(i=0; i<parti_say; i++)
    {
        for(a=0; a<parti_say; a++)
        {
            karakter_2[a]=parti_isimleri(a+1);
            if(karakter_2[a]==karakter[i])
            {
                if(karakter_2[a]==karakter[0])
                    birinci[a]++;//birinci parti olduklari il sayilarini saydirir...
                if(kont_dizi[i]==0)
                    sifirinci[a]++;//partilerin hic milletvekili cikarmadikleri il sayilarini saydirir...
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void parti_ve_oy_sayisinin_siralanmasi(int dizi[],char dizi2[],int boyut)
{
    int gecis_say=0,yer_degisti,i,gecici,gecici_2;
    do
    {
        yer_degisti=0;
        gecis_say++;
        for(i=0; i<boyut-gecis_say; i++)
        {
            if(dizi[i]<dizi[i+1])
            {
                gecici=dizi[i];//partilerin oy sayilarini buyukten kucuge siralar...
                dizi[i]=dizi[i+1];
                dizi[i+1]=gecici;

                gecici_2=dizi2[i];//oylari siralarken parti adlarininde degismesini,siralanmasini saglar...
                dizi2[i]=dizi2[i+1];
                dizi2[i+1]=gecici_2;
                yer_degisti=1;
            }
        }
    }
    while(yer_degisti==1);
}
//-------------------------------------------------------------------------------------------------
void mil_kontenjanin_partilere_dagilimi(int dizi[],char dizi2[],int boyut,int kont,int kont_dizi[])
{
    //milletvekili kontenjanlarinin partilere dagitilmasini saglayan fonksiyon...
    int MV_say,i,min_indeks=0,j,gecici_dizi[boyut-1];
    parti_ve_oy_sayisinin_siralanmasi(dizi,dizi2,boyut);
    for(i=0; i<boyut; i++)
    {
        kont_dizi[i]=0;
        gecici_dizi[i]=dizi[i];
    }
    while(kont!=0)
    {
        MV_say = floor(sqrt(kont));
        gecici_dizi[min_indeks]=(float)gecici_dizi[min_indeks]/2;
        kont_dizi[min_indeks]+=MV_say;

        for(j=0; j<boyut; j++)
        {
            if(gecici_dizi[min_indeks]<=gecici_dizi[j])
                min_indeks=j;
        }
        kont=kont-MV_say;
    }
}
//-------------------------------------------------------------------------------------------------
int parti_isimleri(int sayi)//parti isimlerinin adlarini donduren fonksiyon...
{
    switch(sayi)
    {
    case 1:
        return 'A';
        break;
    case 2:
        return 'B';
        break;
    case 3:
        return 'C';
        break;
    case 4:
        return 'D';
        break;
    case 5:
        return 'E';
        break;
    case 6:
        return 'F';
        break;
    case 7:
        return 'G';
        break;
    case 8:
        return 'H';
        break;
    case 9:
        return 'I';
        break;
    case 10:
        return 'J';
        break;
    case 11:
        return 'K';
        break;
    case 12:
        return 'L';
        break;
    case 13:
        return 'M';
        break;
    case 14:
        return 'N';
        break;
    case 15:
        return 'O';
        break;
    case 16:
        return 'P';
        break;
    case 17:
        return 'Q';
        break;
    case 18:
        return 'R';
        break;
    case 19:
        return 'S';
        break;
    case 20:
        return 'T';
        break;

    }
    return 0;
}
//bitti...
