
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h> 
#include "hafta11.c"

//SYSTEM SPESIFIK TANIMLAMALAR--------------------------------------------------------//
#if defined(__linux__) //LINUX kisminda hata var burayi duzelt
// https://linux.die.net/man/3/malloc_usable_size
#include <malloc.h>
size_t MSIZE(const void *p) {
    return malloc_usable_size((void*)p);
}
#elif defined(__APPLE__)
// https://www.unix.com/man-page/osx/3/malloc_size/
#include <malloc/malloc.h>
size_t MSIZE(const void *p) {
    return malloc_size(p);
}
#elif defined(_WIN32)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/msize
#include <malloc.h>
size_t MSIZE(const void *p) {
    return _msize((void *)p);
}
#else
#error "Unknown System"
#endif
//-----------------------------------------------------------------------------------//

//Lab icin hafta8_fonksiyon prototipleri
void hafta11_fonksiyon(int *frequencyList, char *FileName, int *mostFrequentLetter, char **InStrPtr);


/*
Fonksiyon icerisinde yapilacak islemler
    STRING ISLEMLERI VE DOSYA OKUMA
    1-  TR: Karakter dizisi (string) olarak verilen dosyayi oku (input.txt)
        ENG: Read file given as a string (input.txt)
    2-  TR: Verilen dosyadaki icerige gore hafizada yer ayir
        ENG: Allocate memory space to hold the contents in the input.txt file
    3-  TR: Her harfin frekansini hesapla ve diziye ata (kucuk harflere donusturerek ata)
        ENG: Find frequencies of each letter and assign to the array (convert to lower case letters and assign)
    4-  TR: En cok tekrarlanan harfi yazdir ve geri dondur (kucuk harf olarak)
        ENG: Print and return most frequent letter with its frequency (as a lower case letter)

    Not:    Hafizada olusturdugunuz alan unitTest icerisinde islemler bittikten sonra hafizaya geri verilecektir. 
            Fonksiyon icerisinde free fonksiyonunu kullanmayiniz.
*/

int main()
{
    FILE *fp;
    fp = fopen("not.txt", "w");
    int dogrutestsayisi=0;

    //create a .txt file
    if (fp == NULL) {
        printf("File Pointer Null. Dosya acilamadi.\n");
        return -1;
    }

    //Degiskenler
    int expFreq[26]={12,0,2,3,0,1,0,1,6,0,1,3,1,5,2,2,0,3,1,2,0,0,0,0,2,1};
    char filename[]="input.txt";
    int frequencyList[26]={0};
    int mostFrequentLetter[2]={-1,-1};
    char *inputString=NULL;
    char **InStrPtr;
    InStrPtr=&inputString;

 
    printf("\n");

    //Fonksiyon Cagirma
    hafta11_fonksiyon(frequencyList, filename, mostFrequentLetter, InStrPtr);


    printf("\n");
    printf("Fonksiyon Sonrasi Degerler:\n");
    int i=0;
    for(i=0; i<26; i++)
    {
        printf("frequencyList[%c]=%d \n",i+97,frequencyList[i]);
    }
    printf("En cok gecen harf: %c - Frekansi: %d \n",  mostFrequentLetter[1]+97, mostFrequentLetter[0]);

    printf("TXT dosyasi string boyutu: %d", (int)strlen(inputString));

    printf("\n");

    //Temel Kontrol
    if(inputString == NULL)
    {
        printf("HATA - FONKSIYON DONUSUNDE PTRler hala NULL Getiriyor.\n");
        //Dosya isaretcisi ile dosya yazma islemi kapatilmasi
        fclose(fp);
        return 0;
    }

    //TEST - 1:
    printf("\nTEST - 1\n");
    printf("Hafizadan yer ayrilma kontrolu: \n");

    if((int)strlen(inputString)==55)
    {
        printf("DOGRU\n");
        dogrutestsayisi++;
    }else{printf("YANLIS\n");}


    //TEST - 2:
    printf("\nTEST - 2\n");
    printf("Frekans kontrol: \n");
    int frekansKontrol=1;
    for(i=0; i<26; i++)
    {
        if(expFreq[i]!=frequencyList[i])
        {
            frekansKontrol=0;
        }
    }
    if(frekansKontrol==1)
    {
        printf("DOGRU\n");
        dogrutestsayisi+=2;
    }else{printf("YANLIS\n");}

    //TEST - 3:
    printf("\nTEST - 3\n");
    printf("En cok gecen harf tespiti: \n");

    if(mostFrequentLetter[1]+97=='a')
    {
        printf("DOGRU\n");
        dogrutestsayisi++;
    }else{printf("YANLIS\n");}

    //TEST - 4:
    printf("\nTEST - 4\n");
    printf("En cok gecen harf frekansi: \n");

    if(mostFrequentLetter[0]==12)
    {
        printf("DOGRU\n");
        dogrutestsayisi++;
    }else{printf("YANLIS\n");}

    printf("\n");

    //Puan Hesaplama
    int puan=dogrutestsayisi*20;
    printf("Puan: %d", puan);
    fprintf(fp, "Puan: %d", puan);

    //Alinan hafiza bolgesinin iade edilmesi
    free(inputString);

    //Dosya isaretcisi ile dosya yazma islemi kapatilmasi
    fclose(fp);

    return 0;
}
