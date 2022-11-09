#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<windows.h>


void Obliczenia(float MbKBones,float MbKKidney,float remainder,float valueVolumBones,float valueVolumKidney,float valueVolumResult,float valueRadiatinsBones,float valueRadiatinsKidney,float valueVolume,float MBK){
         //ilosc ml na 1 research po kosciam
        valueVolumBones = valueVolume * MbKBones/MBK;
         //ilosc ml na 1 research po nerkam
        valueVolumKidney = valueVolume *MbKKidney/MBK;
         //ilosc ostatka w ml
        valueVolumResult = valueVolume * remainder/MBK;
        //effective dose nZv na 1 research po kosciam
        valueRadiatinsBones = MbKBones * 0.0057;
        //effective dose nZv na 1 research po nerkam
        valueRadiatinsKidney = MbKKidney*0.0049;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
        printf("Remainder mBk : %.3f", remainder);
        printf("\nNumber of mBk per 1 bone research : %.3f", MbKBones);
        printf("\nNumber of mBk per 1 kidney research : %.3f", MbKKidney);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        printf("\n\n\nNumber of ml per 1 bone research : %.3f", valueVolumBones);
        printf("\nNumber of ml per 1 kidney research : %.3f", valueVolumKidney);
        printf("\nRemainder ml : %.3f", valueVolumResult);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
        printf("\n\n\nEffective dose 'mSv' per 1 bone research : %f", valueRadiatinsBones);
        printf("\nEffective dose 'mSv' per 1 kidney research : %f", valueRadiatinsKidney);
}

int main()
{
    //Исходные данные
    float MBK;                              //łączna kwota MBK
    float MbKBones = 370;
    float MbKBonesmax = 570;
    float MbKKidney = 100;
    float MbKKidneymax = 200;
    float valueBones;                       //ilosc badan po kosciam
    float valueKidney;                      //ilosc badan po nerkam
    float resultMBK;
    float remainder;
    float valueVolumBones;                  //ilosc ml na 1 research po kosciam
    float valueVolumKidney;                 //ilosc ml na 1 research po nerkam
    float valueVolumResult;                 //ilosc ostatka w ml
    float valueRadiatinsBones;              //effective dose nZv na 1 research po kosciam
    float valueRadiatinsKidney;             //effective dose nZv na 1 research po nerkam
    float valueVolume;                      //objętość cieczy
    float activnost;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    printf("\nEnter volume of liquid : ");
    scanf("%f", &valueVolume);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
    printf("\nEnter the amount of mBk in liquid : ");
    scanf("%f", &MBK);

    //Если общей радиации меньше чем миним значение по костям то кол-во исследований по костям = 0
    if(MBK<MbKBones){
        valueBones = 0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        printf("\nNumber of bone research : 0\n");
    }else if(MBK>MbKBones){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        printf("\nEnter the number of bone research : ");
        scanf("%f", &valueBones);
        while((valueBones*MbKBones)>MBK ){
            printf("You entered an invalid number of research, please enter the correct number of research to calculate.\n");
            printf("Enter the number of bone research : ");
            scanf("%f", &valueBones);
        }
    }

    if(MBK<MbKKidney){
        valueKidney = 0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        printf("\nNumber of kidney research : %.3f\n", valueKidney);
    }else if(MBK>MbKKidney){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        printf("\nEnter the number of kidney research : ");
        scanf("%f", &valueKidney);
        while(((valueKidney*MbKKidney)+(valueBones*MbKBones))>MBK){
            printf("You entered an invalid number of research, please enter the correct number of research to calculate.\n");
            printf("Enter the number of bone research : ");
            scanf("%f", &valueKidney);
        }
    }

    if(valueBones==0 && valueKidney==0){
        printf("It is impossible to make calculations with this amount of mBk in liquid");
//Если число исследований по почкам =0 тогда рассчитываем только кости
    }else if(valueKidney==0){
        MbKKidney = 0;
        resultMBK = MBK-valueBones*MbKBones;
        remainder = resultMBK/valueBones;
        MbKBones+= remainder;
        remainder = 0;
        while(MbKBones>MbKBonesmax){
            MbKBones--;
            remainder+=valueBones;
        }
        Obliczenia(MbKBones,MbKKidney,remainder,valueVolumBones,valueVolumKidney,valueVolumResult,valueRadiatinsBones,valueRadiatinsKidney,valueVolume,MBK);

                            //Если число исследований по костям =0 тогда рассчитываем только почки
    }else if(valueBones==0){
        MbKBones = 0;
        resultMBK = MBK-valueKidney*MbKKidney;
        remainder = resultMBK/valueKidney;
        MbKKidney+= remainder;
        remainder = 0;
        while(MbKKidney>MbKKidneymax){
            MbKKidney--;
            remainder+=valueKidney;
        }
       Obliczenia(MbKBones,MbKKidney,remainder,valueVolumBones,valueVolumKidney,valueVolumResult,valueRadiatinsBones,valueRadiatinsKidney,valueVolume,MBK);

        }else{
            resultMBK = MBK - (valueBones*MbKBones+valueKidney*MbKKidney);
            if(resultMBK == 0){
                remainder = 0;
                Obliczenia(MbKBones,MbKKidney,remainder,valueVolumBones,valueVolumKidney,valueVolumResult,valueRadiatinsBones,valueRadiatinsKidney,valueVolume,MBK);
            }else{
                remainder = resultMBK/valueBones;
                MbKBones+=remainder;

                 while(MbKBones>MbKBonesmax){
                    MbKBones--;
                }
                resultMBK = MBK - (valueBones*MbKBones+valueKidney*MbKKidney);
                remainder = resultMBK/valueKidney;
                MbKKidney+=remainder;
                remainder = 0;
                while(MbKKidney>MbKKidneymax){
                    MbKKidney--;
                    remainder+=valueKidney;
                }
                Obliczenia(MbKBones,MbKKidney,remainder,valueVolumBones,valueVolumKidney,valueVolumResult,valueRadiatinsBones,valueRadiatinsKidney,valueVolume,MBK);
            }
        }
   //objętość cieczy
    activnost = MBK/valueVolume;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
    printf("\nSpecific activity per 1 ml : %f", activnost);
    getch();
    system("cls");
    getch();
    printf("Thank you for using our company product JakobsonCorp.");
    getch();
    system("cls");
    printf("End of program!");
    getch();
    return 0;
}
