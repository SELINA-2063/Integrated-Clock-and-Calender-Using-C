//Integrated Clock and Calendar System in C
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include<unistd.h>
#include<stdlib.h>
#include<conio.h>

int leapyear(int year) {
    if((year % 400 == 0) || (year % 100 > 0 && year % 4 == 0))
        return 1;
    else
        return 0;
}

void clearScreen() {
    // Clearing screen based on OS (works for Unix/Linux and Windows)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void current_month_calendar();
void other_month_calendar();
void calendar_of_year();
void showCalendar(int month, int year);
void show2Calendar(int month1, int year1, int month2, int year2);
void Clock();
void watch();

int main()
{
    clearScreen();
    int value;
    printf("1:Clock\n");
    printf("2:Calender\n");
    printf("What do you want to see:");
    scanf("%d",&value);
    if(value==1)
        Clock();
     else
        current_month_calendar();
}

void showCalendar(int month, int year) {
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth[] = {31, 28 + leapyear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("     %s %d\n", months[month - 1], year);
    printf("|---------------------------|\n");
    printf("|Sun|Mon|Tue|Wed|Thu|Fri|Sat|\n");

    struct tm timeStruct = {0};
    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = 1;
    mktime(&timeStruct);

    int dayOfWeek = timeStruct.tm_wday;
    int maxDay = daysInMonth[month - 1];
    int day = 1;

    for (int i = 0; i < 6; i++) {
        printf("|---------------------------|\n");
        for (int j = 0; j < 7; j++) {
            if (i == 0 && j < dayOfWeek) {
                printf("|   ");
            } else if (day <= maxDay) {
                printf("|%3d", day);
                day++;
            } else {
                printf("|   ");
            }
        }
        printf("|\n");
    }
    printf("|---------------------------|\n\n");
}
void show2Calendar(int month1, int year1, int month2, int year2) {
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth[] = {31, 28 + leapyear(year1), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("        %s %d                %s %d\n", months[month1 - 1], year1, months[month2 - 1], year2);
    printf("|---------------------------||---------------------------|\n");
    printf("|Sun|Mon|Tue|Wed|Thu|Fri|Sat||Sun|Mon|Tue|Wed|Thu|Fri|Sat|\n");

    struct tm timeStruct1 = {0};
    timeStruct1.tm_year = year1 - 1900;
    timeStruct1.tm_mon = month1 - 1;
    timeStruct1.tm_mday = 1;
    mktime(&timeStruct1);

    struct tm timeStruct2 = {0};
    timeStruct2.tm_year = year2 - 1900;
    timeStruct2.tm_mon = month2 - 1;
    timeStruct2.tm_mday = 1;
    mktime(&timeStruct2);

    int dayOfWeek1 = timeStruct1.tm_wday;
    int maxDay1 = daysInMonth[month1 - 1];
    int day1 = 1;

    int dayOfWeek2 = timeStruct2.tm_wday;
    int maxDay2 = daysInMonth[month2 - 1];
    int day2 = 1;

    for (int i = 0; i < 6; i++) {
        printf("|---------------------------||---------------------------|\n");
        for (int j = 0; j < 7; j++) {
            if (i == 0 && j < dayOfWeek1) {
                printf("|   ");
            } else if (day1 <= maxDay1) {
                printf("|%3d", day1);
                day1++;
            } else {
                printf("|   ");
            }
        }

        printf("|");

        for (int j = 0; j < 7; j++) {
            if (i == 0 && j < dayOfWeek2) {
                printf("|   ");
            } else if (day2 <= maxDay2) {
                printf("|%3d", day2);
                day2++;
            } else {
                printf("|   ");
            }
        }
        printf("|\n");
    }
    printf("|---------------------------||---------------------------|\n\n");
}
void current_month_calendar() {
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    int date=localTime->tm_mday;
    clearScreen();
    printf("%d/%d/%d\n",date,month,year);
    showCalendar(month, year);
    printf("1. Show calendar of other month\n");
    printf("2. Show calendar of the year\n");
    printf("3. End program\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            other_month_calendar();
            break;
        case 2:
            calendar_of_year();
            break;
        case 3:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Exiting the program.\n");
    }
}

void other_month_calendar() {
    int month, year;
    clearScreen();
    printf("Enter month and year (MM YYYY): ");
    scanf("%d %d", &month, &year);

    if (month < 1 || month > 12 || year < 1) {
        printf("Invalid input. Exiting the program.\n");
        return;
    }

    showCalendar(month, year);

    printf("1. Show calendar of current month\n");
    printf("2. Show calendar of the year\n");
    printf("3. End program\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            current_month_calendar();
            break;
        case 2:
            calendar_of_year();
            break;
        case 3:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Exiting the program.\n");
    }
}

void calendar_of_year() {
    int year, currentYear;
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    currentYear = localTime->tm_year + 1900;
    clearScreen();
    printf("Do you want to see the calendar for the current year? (y/n): ");
    char choice;
    getchar();
    scanf("%c", &choice);
    if (choice=='y') {
        year = currentYear;
    } else if (choice=='n') {
        printf("Enter the year: ");
        scanf("%d", &year);
        if (year < 1) {
            printf("Invalid year entered.\n");
            return ;
        }
    } else {
        printf("Invalid choice.\n");
        return ;
    }
    for (int month = 1; month <= 12; month+=2) {
        show2Calendar(month, year,month+1,year);
    }
    printf("Press 'Enter' to end the process\n");
    getchar();
    getchar();
    main();
    return ;
}

void watch()
{
    system("cls");
            while (1)
            {
                SYSTEMTIME currentTime;
                // Get the current local time
                GetLocalTime(&currentTime);

                // Print the current time
                printf("\n\n\n                  ####################################\n\n");
                if(currentTime.wHour<=12)
                printf("                        Current Time: %02d:%02d:%02d\n\n", currentTime.wHour, currentTime.wMinute, currentTime.wSecond);
                else
                    printf("                        Current Time: %02d:%02d:%02d\n\n", currentTime.wHour-12, currentTime.wMinute, currentTime.wSecond);
                printf("                  ####################################");
                sleep(1);
                system("cls");
                fflush(stdout);
                // Flush the output buffer to update the console immediately
                // Sleep for 1 second (use _sleep(1000) for Windows)
            }
}


    void Clock()
{
    system("cls");
    int option;
    printf("1:Time\n");
    printf("2:Timer\n");
    printf("3.World Clock\n");
    printf("0.Main menu");
    scanf("%d",&option);
    if(option==1)
    {
        system("cls");
        printf("1.Enter 1 to  to see current time:\n");
        printf("2.Enter 2 to set current time:");
        int option;
        scanf("%d",&option);
        if(option==1)
            watch();
        else
        {
            system("cls");
            int hour,minute,second;
            printf("Enter current time:");
            scanf("%d %d %d",&hour,&minute,&second);
            while(1)
            {
                if(second==60)
                {
                    minute++;
                    second=0;
                }
                if(minute==60)
                {
                    hour++;
                    minute=0;
                }
                if(hour==12)
                    hour=0;
                printf("         ############ Current Time ##################\n");
                printf("                   %02d:%02d:%02d\n",hour,minute,second);
                printf("         ####################################\n");

                second++;
                sleep(1);
                system("cls");

            }
        }

    }
    else if(option==2)
    {
        system("cls");
        int hour,minute,second;
        printf("Enter hour,minute,second:");
        scanf("%d %d %d",&hour,&minute,&second);
        system("cls");
        while(hour!=0||minute!=0||second!=-1)
        {
            if(second==0&&minute!=0)
            {
                minute--;
                second=60;
            }
            if(minute==0&&hour!=0)
            {
                hour--;
                minute=60;
            }
            printf("\n\n            ################ Timer #############\n");
            printf("                         %02d:%02d:%02d\n",hour,minute,second);
            if(hour==0&&minute==0&&second==0)
                printf("                  Times up\n");
            printf("            ####################################\n");

            if(hour==0&&minute==0&&second==0)
                break;
            second--;
            sleep(1);
            system("cls");
        }
        printf("Press 'Enter' to end the process\n");
        getchar();
        getchar();
        Clock();
    }
    else if(option==3)
        {
            system("cls");
            while (1)
            {

                SYSTEMTIME currentTime;
                // Get the current local time
                GetLocalTime(&currentTime);

                // Print the current time
                    printf("     \n\n **************WORLD CLOCK*******************\n");

                int dhakahour;
                if(currentTime.wHour>12)
                     dhakahour=currentTime.wHour-12;
                else if(currentTime.wHour<=12)
                    dhakahour=currentTime.wHour;
                    if(dhakahour==0)
                        dhakahour=12;
                printf("            Dhaka: %02d:%02d:%02d\n\n", dhakahour, currentTime.wMinute, currentTime.wSecond);

                 if(dhakahour+1>12)
                printf("            New York: %02d:%02d:%02d\n\n", dhakahour+1-12, currentTime.wMinute, currentTime.wSecond);
                    else if(dhakahour+1<12)
                      printf("            New York: %02d:%02d:%02d\n\n", dhakahour+1, currentTime.wMinute, currentTime.wSecond);
                      else
                        printf("            New York: %02d:%02d:%02d\n\n", 12, currentTime.wMinute, currentTime.wSecond);

                if(dhakahour-6<0)
                printf("            London: %02d:%02d:%02d\n\n", dhakahour+12-6, currentTime.wMinute, currentTime.wSecond);
                else if(dhakahour-6>0)
                printf("            London: %02d:%02d:%02d\n\n", dhakahour-6, currentTime.wMinute, currentTime.wSecond);
                else
                    printf("            London: %02d:%02d:%02d\n\n", 12, currentTime.wMinute, currentTime.wSecond);
                if(dhakahour-5<0)
                printf("            Paris: %02d:%02d:%02d\n\n", dhakahour+12-5, currentTime.wMinute, currentTime.wSecond);
                else if(dhakahour-5>0)
                   printf("            Paris: %02d:%02d:%02d\n\n",dhakahour-5, currentTime.wMinute, currentTime.wSecond);
                else
                      printf("            Paris: %02d:%02d:%02d\n\n",12, currentTime.wMinute, currentTime.wSecond);
                   int delhihour,delhimin;
                  if(currentTime.wMinute+30>=60)
                  {
                      delhimin=currentTime.wMinute+30-60;
                      delhihour=dhakahour;
                  }
                  else
                  {
                      delhimin=currentTime.wMinute+30;
                      delhihour=dhakahour-1;

                  }
                  if(delhihour==0)
                    delhihour=12;

                printf("            Delhi: %02d:%02d:%02d\n\n", delhihour, delhimin, currentTime.wSecond);


                sleep(1);
                system("cls");
                fflush(stdout);
                // Flush the output buffer to update the console immediately
                // Sleep for 1 second (use _sleep(1000) for Windows)

            }

    }
    else
        main();

}
